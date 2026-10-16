import frida, json, sys, time, subprocess

OUT = r"C:\Users\Administrator\Documents\dswave_re\capture\winusb_trace.jsonl"
EXE = r"C:\Program Files\DSWave\DSWave.exe"
DUR = 90

def main():
    session_log = open(OUT, "w", encoding="utf-8")
    dev = frida.get_local_device()
    pid = dev.spawn([EXE], cwd=r"C:\Program Files\DSWave")
    print("spawned pid", pid, flush=True)
    session = dev.attach(pid)
    script_src = open(r"C:\Users\Administrator\Documents\dswave_re\hook_winusb.js", "r", encoding="utf-8").read()
    script = session.create_script(script_src)

    def on_message(message, data):
        if message.get("type") == "send":
            session_log.write(json.dumps(message["payload"], ensure_ascii=False) + "\n")
            session_log.flush()
        elif message.get("type") == "error":
            print("[script-error]", message.get("description"), flush=True)

    script.on("message", on_message)
    script.load()
    dev.resume(pid)
    t0 = time.time()
    try:
        while time.time() - t0 < DUR:
            time.sleep(1)
    finally:
        try:
            session.detach()
        except Exception:
            pass
        subprocess.run(["taskkill", "/F", "/PID", str(pid)], capture_output=True)
        session_log.close()
        print("trace done", flush=True)

if __name__ == "__main__":
    main()
