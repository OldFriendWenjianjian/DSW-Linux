
undefined * FUN_140340b20(longlong *param_1,longlong param_2,int param_3)

{
  longlong *plVar1;
  longlong lVar2;
  char cVar3;
  undefined1 uVar4;
  short sVar5;
  undefined *puVar6;
  wchar_t *pwVar7;
  longlong *plVar8;
  int iVar9;
  short *psVar10;
  short sVar11;
  bool bVar12;
  
  if (param_3 < 1) {
    _wassert(L"len > 0",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e8);
  }
  else if (param_3 < 9) {
    (**(code **)(*param_1 + 0x1b0))();
    cVar3 = (**(code **)(*param_1 + 0x1c8))(param_1);
    if (cVar3 == '\0') {
      (**(code **)(*param_1 + 0x1b8))(param_1,0x513,0);
      lVar2 = (longlong)(int)(param_3 - 1U) * 2;
      psVar10 = (short *)(param_2 + lVar2);
      iVar9 = 8;
      do {
        cVar3 = (**(code **)(*param_1 + 0x1c8))(param_1);
        if (cVar3 != '\0') goto LAB_140340c4b;
        while (cVar3 = (**(code **)(*param_1 + 0x1c0))(param_1), cVar3 == '\0') {
          bVar12 = iVar9 == 0;
          iVar9 = iVar9 + -1;
          if (bVar12) {
            FUN_140028670(DAT_1411d8da0,"%s:%d, Security is NOT ready.","DoSecurity",0x1f6);
            goto LAB_140340c4b;
          }
        }
        sVar5 = (**(code **)(*param_1 + 0x1d0))(param_1);
        sVar11 = *psVar10;
        if ((sVar5 != 0) && (sVar11 == -1)) {
          *psVar10 = sVar5;
          sVar11 = sVar5;
        }
        psVar10 = psVar10 + -1;
        (**(code **)(*param_1 + 0x1b8))(param_1,0x219,sVar11);
      } while (psVar10 != (short *)(param_2 + -2 + lVar2 + (ulonglong)(param_3 - 1U) * -2));
      uVar4 = (**(code **)(*param_1 + 0x1c8))(param_1);
      FUN_140028940(DAT_1411d8da0,"BSP: Security check result: %d",uVar4);
      puVar6 = (undefined *)0x0;
    }
    else {
LAB_140340c4b:
      puVar6 = (undefined *)0xfffffffc;
    }
    return puVar6;
  }
  pwVar7 = L"len <= SEC_STEPS";
  _wassert(L"len <= SEC_STEPS",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x1e9);
  if (*(longlong *)(pwVar7 + 0xc) == 0) {
    _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0xb3);
    puVar6 = &DAT_1411dd8b8;
    do {
      plVar8 = *(longlong **)(puVar6 + 8);
      plVar1 = *(longlong **)(puVar6 + 0x10);
      if (plVar1 != plVar8) {
        do {
          if ((longlong *)*plVar8 != plVar8 + 2) {
            thunk_FUN_1407a45e0((longlong *)*plVar8,plVar8[2] + 1);
          }
          plVar8 = plVar8 + 4;
        } while (plVar1 != plVar8);
        plVar8 = *(longlong **)(puVar6 + 8);
      }
      if (plVar8 != (longlong *)0x0) {
        thunk_FUN_1407a45e0(plVar8,*(longlong *)(puVar6 + 0x18) - (longlong)plVar8);
      }
      bVar12 = puVar6 != &DAT_1411dcc60;
      puVar6 = puVar6 + -0x28;
    } while (bVar12);
    return &DAT_1411dcc38;
  }
  puVar6 = (undefined *)FUN_1403bada0();
  if (4 < (int)puVar6 - 1U) {
    FUN_140028670(DAT_1411d8da0,"%s:%d, Unknown USB speed: %d","GetSpeed",0xc1,(int)puVar6);
    return (undefined *)0x0;
  }
  return puVar6;
}

