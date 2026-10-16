'use strict';
// Hook winusb usage of DSWave: intercept GetProcAddress resolutions of WinUsb_*
// and log every transfer (api, endpoint, bytes, direction, timestamp).

function ts() { return Date.now(); }

function hd(ptr, len, cap) {
    if (ptr.isNull()) return '';
    cap = (cap === undefined) ? 512 : cap;
    var n = Math.min(len, cap);
    try { var ab = ptr.readByteArray(n); return ab === null ? '' : hx(ab); } catch (e) { return 'ERR:' + e.message; }
}
function hx(ab) {
    var u8 = new Uint8Array(ab); var s = '';
    for (var i = 0; i < u8.length; i++) { s += ('0' + u8[i].toString(16)).slice(-2); }
    return s;
}

function send2(obj) { send(obj); }

// pending overlapped reads: OVERLAPPED* -> {api, buf, len}
var pending = {};

var hookedFns = {};

function hookWinUsb(name, addr) {
    if (hookedFns[name]) return;
    hookedFns[name] = true;
    var impl = {
        WinUsb_ControlTransfer: function (args) {
            var raw = ('0000000000000000' + args[1].toString(16)).slice(-16);
            var sp = raw.match(/../g).reverse().join('');
            var r = { setup: sp, len: args[3].toInt32() };
            r.dir = ((parseInt(sp.slice(0, 2), 16) & 0x80) !== 0) ? 'in' : 'out';
            if (r.dir === 'out') r.data = hd(args[2], r.len);
            r.bufPtr = args[2].toString();
            r.xferPtr = args[4].toString();
            if (!args[5].isNull() && r.dir === 'in') pending[args[5].toString()] = { api: 'WinUsb_ControlTransfer', ep: 'ep0', buf: args[2].toString(), len: r.len };
            return r;
        },
        WinUsb_WritePipe: function (args) {
            // (iface, pipeID, buf, len, transferred*, overlapped*)
            return { ep: '0x' + args[1].toInt32().toString(16), data: hd(args[2], args[3].toInt32()), len: args[3].toInt32(), dir: 'out' };
        },
        WinUsb_ReadPipe: function (args) {
            var r = { ep: '0x' + args[1].toInt32().toString(16), buf: args[2].toString(), len: args[3].toInt32(), dir: 'in' };
            if (!args[5].isNull()) { pending[args[5].toString()] = r; r.async = true; }
            return r;
        },
        WinUsb_QueryPipeEx: function (args) {
            return { infoPtr: args[3].toString(), pipeIdx: args[2].toInt32(), dumpOnLeave: true };
        },
        WinUsb_SetPipePolicy: function (args) {
            return { ep: '0x' + args[1].toInt32().toString(16), policyType: args[2].toInt32(), value: hd(args[3], args[4].toInt32(), 8), len: args[4].toInt32() };
        },
        WinUsb_SetCurrentAlternateSetting: function (args) {
            return { setting: args[1].toInt32() };
        }
    }[name];

    Interceptor.attach(addr, {
        onEnter: function (args) {
            this.meta = impl ? impl(args) : { args: [args[0].toString()] };
            this.meta.api = name;
            this.meta.t = ts();
            this.meta.thr = this.threadId;
        },
        onLeave: function (retval) {
            this.meta.status = retval.toInt32();
            if (this.meta.dumpOnLeave && this.meta.infoPtr) {
                this.meta.info = hd(ptr(this.meta.infoPtr), 32, 32);
                delete this.meta.infoPtr;
            }
            if (this.meta.api === 'WinUsb_ControlTransfer' && this.meta.dir === 'in' && this.meta.status !== 0) {
                this.meta.note = 'async-or-fail';
            } else if (this.meta.api === 'WinUsb_ControlTransfer' && this.meta.dir === 'in') {
                try {
                    var xfer = ptr(this.meta.xferPtr).readU32();
                    this.meta.rxlen = xfer;
                    this.meta.data = hd(ptr(this.meta.bufPtr), xfer);
                } catch (e) { this.meta.rxerr = '' + e; }
            }
            if (this.meta.api === 'WinUsb_ReadPipe' && this.meta.status !== 0) {
                // synchronous failure or pending async: nothing to dump; overlapped path handled via GetOverlappedResult
                delete this.meta.buf;
            } else if (this.meta.api === 'WinUsb_ReadPipe') {
                // sync success: dump buffer
                this.meta.data = hd(ptr(this.meta.buf), this.meta.len);
                delete this.meta.buf;
            }
            delete this.meta.bufPtr; delete this.meta.xferPtr; delete this.meta.dumpOnLeave;
            send2(this.meta);
        }
    });
}

// Intercept GetProcAddress to catch dynamic WinUsb resolution
var gpa = Process.getModuleByName('kernel32.dll').findExportByName('GetProcAddress');
Interceptor.attach(gpa, {
    onEnter: function (args) { this.name = args[1].readAnsiString(); },
    onLeave: function (retval) {
        if (this.name && this.name.indexOf('WinUsb_') === 0 && !retval.isNull()) {
            send2({ api: 'GetProcAddress', name: this.name, addr: retval.toString(), t: ts() });
            hookWinUsb(this.name, retval);
        }
    }
});

// Catch winusb load via LoadLibrary to hook exports never resolved through GetProcAddress
['LoadLibraryW', 'LoadLibraryExW'].forEach(function (ln) {
    var f = Process.getModuleByName('kernel32.dll').findExportByName(ln);
    if (!f) return;
    Interceptor.attach(f, {
        onEnter: function (args) { try { this.n = args[0].readUtf16String(); } catch (e) { this.n = ''; } },
        onLeave: function (retval) {
            if (this.n && this.n.toLowerCase().indexOf('winusb') >= 0) {
                ['WinUsb_Initialize', 'WinUsb_ControlTransfer', 'WinUsb_WritePipe', 'WinUsb_ReadPipe',
                 'WinUsb_QueryPipeEx', 'WinUsb_SetPipePolicy', 'WinUsb_SetCurrentAlternateSetting'].forEach(function (n) {
                    var a = Process.getModuleByName('winusb.dll').findExportByName(n);
                    if (a) hookWinUsb(n, a);
                });
            }
        }
    });
});

// overlapped completion for async reads
var gor = Process.getModuleByName('kernel32.dll').findExportByName('GetOverlappedResult');
if (gor) {
    Interceptor.attach(gor, {
        onEnter: function (args) { this.ov = args[1].toString(); this.xfer = args[2]; },
        onLeave: function (retval) {
            var p = pending[this.ov];
            if (p) {
                var n = this.xfer.readU32();
                send2({ api: p.api + ':overlapped', ep: p.ep, len: n, data: hd(ptr(p.buf), n), status: retval.toInt32(), t: ts() });
                delete pending[this.ov];
            }
        }
    });
}
// record async read requests into pending map
var origReadHook = hookedFns; // noop

// SetupAPI enumeration GUID
['SetupDiGetClassDevsW'].forEach(function (n) {
    var f = null; try { f = Process.getModuleByName('setupapi.dll').findExportByName(n); } catch (e) {}
    if (f) Interceptor.attach(f, {
        onEnter: function (args) { this.guid = hd(args[0], 16, 16); },
        onLeave: function (retval) { send2({ api: n, guid: this.guid, ret: retval.toString(), t: ts() }); }
    });
});

send2({ api: 'hook_ready', t: ts() });
