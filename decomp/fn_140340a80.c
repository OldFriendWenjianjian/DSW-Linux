// FUN_140340a80

undefined * FUN_140340a80(longlong param_1)

{
  longlong *plVar1;
  char cVar2;
  undefined1 uVar3;
  wchar_t wVar4;
  undefined *puVar5;
  wchar_t *pwVar6;
  longlong *plVar7;
  wchar_t *pwVar8;
  uint uVar9;
  int iVar10;
  wchar_t *pwVar11;
  wchar_t wVar12;
  bool bVar13;
  
  if (*(longlong *)(param_1 + 0x18) != 0) {
    if (*(longlong *)(param_1 + 0x20) == 0) {
      FUN_140028670(DAT_1411d8da0,"%s:%d, Failed to close: libusb_device_handle is null.","Close",
                    0x7d);
      puVar5 = (undefined *)0xfffffffb;
    }
    else {
      FUN_140028850(DAT_1411d8da0,"Closing device(%p)");
      if (*(longlong *)(param_1 + 0x20) != 0) {
        FUN_1403bbba0(*(longlong *)(param_1 + 0x20),0);
        FUN_1403bb620(*(undefined8 *)(param_1 + 0x20));
      }
      *(undefined8 *)(param_1 + 0x20) = 0;
      puVar5 = (undefined *)0x0;
    }
    return puVar5;
  }
  pwVar8 = L"..\\..\\..\\hal\\usb\\usbbsp.cpp";
  iVar10 = 0x7a;
  pwVar6 = L"m_libusb";
  _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x7a);
  if (iVar10 < 1) {
    _wassert(L"len > 0",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e8);
  }
  else if (iVar10 < 9) {
    (**(code **)(*(longlong *)pwVar6 + 0x1b0))();
    cVar2 = (**(code **)(*(longlong *)pwVar6 + 0x1c8))(pwVar6);
    if (cVar2 == '\0') {
      uVar9 = iVar10 - 1;
      (**(code **)(*(longlong *)pwVar6 + 0x1b8))(pwVar6,0x513,0);
      pwVar11 = pwVar8 + (int)uVar9;
      iVar10 = 8;
      do {
        cVar2 = (**(code **)(*(longlong *)pwVar6 + 0x1c8))(pwVar6);
        if (cVar2 != '\0') goto LAB_140340c4b;
        while (cVar2 = (**(code **)(*(longlong *)pwVar6 + 0x1c0))(pwVar6), cVar2 == '\0') {
          bVar13 = iVar10 == 0;
          iVar10 = iVar10 + -1;
          if (bVar13) {
            FUN_140028670(DAT_1411d8da0,"%s:%d, Security is NOT ready.","DoSecurity",0x1f6);
            goto LAB_140340c4b;
          }
        }
        wVar4 = (**(code **)(*(longlong *)pwVar6 + 0x1d0))(pwVar6);
        wVar12 = *pwVar11;
        if ((wVar4 != L'\0') && (wVar12 == L'\xffff')) {
          *pwVar11 = wVar4;
          wVar12 = wVar4;
        }
        pwVar11 = pwVar11 + -1;
        (**(code **)(*(longlong *)pwVar6 + 0x1b8))(pwVar6,0x219,wVar12);
      } while (pwVar11 != pwVar8 + (longlong)(int)uVar9 + (-1 - (ulonglong)uVar9));
      uVar3 = (**(code **)(*(longlong *)pwVar6 + 0x1c8))(pwVar6);
      FUN_140028940(DAT_1411d8da0,"BSP: Security check result: %d",uVar3);
      puVar5 = (undefined *)0x0;
    }
    else {
LAB_140340c4b:
      puVar5 = (undefined *)0xfffffffc;
    }
    return puVar5;
  }
  pwVar6 = L"len <= SEC_STEPS";
  _wassert(L"len <= SEC_STEPS",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e9);
  if (*(longlong *)(pwVar6 + 0xc) == 0) {
    _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0xb3);
    puVar5 = &DAT_1411dd8b8;
    do {
      plVar7 = *(longlong **)(puVar5 + 8);
      plVar1 = *(longlong **)(puVar5 + 0x10);
      if (plVar1 != plVar7) {
        do {
          if ((longlong *)*plVar7 != plVar7 + 2) {
            thunk_FUN_1407a45e0((longlong *)*plVar7,plVar7[2] + 1);
          }
          plVar7 = plVar7 + 4;
        } while (plVar1 != plVar7);
        plVar7 = *(longlong **)(puVar5 + 8);
      }
      if (plVar7 != (longlong *)0x0) {
        thunk_FUN_1407a45e0(plVar7,*(longlong *)(puVar5 + 0x18) - (longlong)plVar7);
      }
      bVar13 = puVar5 != &DAT_1411dcc60;
      puVar5 = puVar5 + -0x28;
    } while (bVar13);
    return &DAT_1411dcc38;
  }
  puVar5 = (undefined *)FUN_1403bada0();
  if (4 < (int)puVar5 - 1U) {
    FUN_140028670(DAT_1411d8da0,"%s:%d, Unknown USB speed: %d","GetSpeed",0xc1,(int)puVar5);
    return (undefined *)0x0;
  }
  return puVar5;
}

