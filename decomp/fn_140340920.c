// FUN_140340920

undefined * FUN_140340920(longlong *param_1)

{
  longlong *plVar1;
  char cVar2;
  undefined1 uVar3;
  wchar_t wVar4;
  int iVar5;
  undefined *puVar6;
  undefined8 uVar7;
  wchar_t *pwVar8;
  longlong *plVar9;
  wchar_t *pwVar10;
  uint uVar11;
  wchar_t *pwVar12;
  wchar_t wVar13;
  bool bVar14;
  
  if (param_1[4] == 0) {
    pwVar8 = L"m_usb_handle";
    _wassert(L"m_usb_handle",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x4a);
    if (*(longlong *)(pwVar8 + 0xc) != 0) {
      if (*(longlong *)(pwVar8 + 0x10) == 0) {
        FUN_140028670(DAT_1411d8da0,"%s:%d, Failed to close: libusb_device_handle is null.","Close",
                      0x7d,param_1);
        puVar6 = (undefined *)0xfffffffb;
      }
      else {
        FUN_140028850(DAT_1411d8da0,"Closing device(%p)");
        if (*(longlong *)(pwVar8 + 0x10) != 0) {
          FUN_1403bbba0(*(longlong *)(pwVar8 + 0x10),0);
          FUN_1403bb620(*(undefined8 *)(pwVar8 + 0x10));
        }
        pwVar8[0x10] = L'\0';
        pwVar8[0x11] = L'\0';
        pwVar8[0x12] = L'\0';
        pwVar8[0x13] = L'\0';
        puVar6 = (undefined *)0x0;
      }
      return puVar6;
    }
    pwVar10 = L"..\\..\\..\\hal\\usb\\usbbsp.cpp";
    iVar5 = 0x7a;
    pwVar8 = L"m_libusb";
    _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x7a);
    if (iVar5 < 1) {
      _wassert(L"len > 0",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e8);
    }
    else if (iVar5 < 9) {
      (**(code **)(*(longlong *)pwVar8 + 0x1b0))();
      cVar2 = (**(code **)(*(longlong *)pwVar8 + 0x1c8))(pwVar8);
      if (cVar2 == '\0') {
        uVar11 = iVar5 - 1;
        (**(code **)(*(longlong *)pwVar8 + 0x1b8))(pwVar8,0x513,0);
        pwVar12 = pwVar10 + (int)uVar11;
        iVar5 = 8;
        do {
          cVar2 = (**(code **)(*(longlong *)pwVar8 + 0x1c8))(pwVar8);
          if (cVar2 != '\0') goto LAB_140340c4b;
          while (cVar2 = (**(code **)(*(longlong *)pwVar8 + 0x1c0))(pwVar8), cVar2 == '\0') {
            bVar14 = iVar5 == 0;
            iVar5 = iVar5 + -1;
            if (bVar14) {
              FUN_140028670(DAT_1411d8da0,"%s:%d, Security is NOT ready.","DoSecurity",0x1f6);
              goto LAB_140340c4b;
            }
          }
          wVar4 = (**(code **)(*(longlong *)pwVar8 + 0x1d0))(pwVar8);
          wVar13 = *pwVar12;
          if ((wVar4 != L'\0') && (wVar13 == L'\xffff')) {
            *pwVar12 = wVar4;
            wVar13 = wVar4;
          }
          pwVar12 = pwVar12 + -1;
          (**(code **)(*(longlong *)pwVar8 + 0x1b8))(pwVar8,0x219,wVar13);
        } while (pwVar12 != pwVar10 + (longlong)(int)uVar11 + (-1 - (ulonglong)uVar11));
        uVar3 = (**(code **)(*(longlong *)pwVar8 + 0x1c8))(pwVar8);
        FUN_140028940(DAT_1411d8da0,"BSP: Security check result: %d",uVar3);
        puVar6 = (undefined *)0x0;
      }
      else {
LAB_140340c4b:
        puVar6 = (undefined *)0xfffffffc;
      }
      return puVar6;
    }
    pwVar8 = L"len <= SEC_STEPS";
    _wassert(L"len <= SEC_STEPS",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e9);
    if (*(longlong *)(pwVar8 + 0xc) == 0) {
      _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0xb3);
      puVar6 = &DAT_1411dd8b8;
      do {
        plVar9 = *(longlong **)(puVar6 + 8);
        plVar1 = *(longlong **)(puVar6 + 0x10);
        if (plVar1 != plVar9) {
          do {
            if ((longlong *)*plVar9 != plVar9 + 2) {
              thunk_FUN_1407a45e0((longlong *)*plVar9,plVar9[2] + 1);
            }
            plVar9 = plVar9 + 4;
          } while (plVar1 != plVar9);
          plVar9 = *(longlong **)(puVar6 + 8);
        }
        if (plVar9 != (longlong *)0x0) {
          thunk_FUN_1407a45e0(plVar9,*(longlong *)(puVar6 + 0x18) - (longlong)plVar9);
        }
        bVar14 = puVar6 != &DAT_1411dcc60;
        puVar6 = puVar6 + -0x28;
      } while (bVar14);
      return &DAT_1411dcc38;
    }
    puVar6 = (undefined *)FUN_1403bada0();
    if (4 < (int)puVar6 - 1U) {
      FUN_140028670(DAT_1411d8da0,"%s:%d, Unknown USB speed: %d","GetSpeed",0xc1,(int)puVar6);
      return (undefined *)0x0;
    }
    return puVar6;
  }
  iVar5 = FUN_1403bbae0(param_1[4],0);
  if (iVar5 == 0) {
LAB_140340990:
    puVar6 = (undefined *)0x0;
  }
  else {
    if (iVar5 == -5) {
      FUN_140028670(DAT_1411d8da0,
                    "%s:%d: Unable to claim interface (LIBUSB_ERROR_NOT_FOUND), try again.","Claim",
                    0x5c);
      iVar5 = FUN_1403bbae0(param_1[4],0);
      if (iVar5 == 0) goto LAB_140340990;
      uVar7 = FUN_1403bd030(iVar5);
      FUN_140028670(DAT_1411d8da0,"%s:%d: Unable to claim interface secondly: %s.","Claim",0x6a,
                    uVar7);
    }
    else if (iVar5 == -4) {
      FUN_140028670(DAT_1411d8da0,"%s:%d: Device has been disconnected.","Claim",0x57);
    }
    else if (iVar5 == -6) {
      FUN_140028670(DAT_1411d8da0,
                    "%s:%d: Unable to claim USB interface. Another program or driver has already claimed it."
                    ,"Claim",0x52);
    }
    else {
      uVar7 = FUN_1403bd030(iVar5);
      FUN_140028670(DAT_1411d8da0,"%s:%d: Unable to claim interface: %s.","Claim",99,uVar7);
    }
    (**(code **)(*param_1 + 0x20))(param_1);
    puVar6 = (undefined *)0xfffffffb;
  }
  return puVar6;
}

