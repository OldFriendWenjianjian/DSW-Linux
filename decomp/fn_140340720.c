// FUN_140340720

ulonglong FUN_140340720(longlong param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  short *psVar5;
  wchar_t *pwVar6;
  short asStack_90 [12];
  longlong lStack_78;
  
  if (*(longlong *)(param_1 + 0x18) != 0) {
    uVar1 = FUN_1403bad60();
    *(undefined1 *)(param_1 + 0x10) = uVar1;
    uVar1 = FUN_1403bad90(*(undefined8 *)(param_1 + 0x18));
    *(undefined1 *)(param_1 + 0x11) = uVar1;
    FUN_140028850(DAT_1411d8da0,"Opening device(%p)",*(undefined8 *)(param_1 + 0x18));
    uVar4 = FUN_1403bb4d0(*(undefined8 *)(param_1 + 0x18),param_1 + 0x20);
    if ((int)uVar4 != 0) {
      FUN_1403bd030(uVar4 & 0xffffffff);
      FUN_140028670(DAT_1411d8da0,"%s:%d, Failed to open usb device (%p): %s",&DAT_140c45155,0x3f);
      uVar4 = 0xffffffff;
    }
    return uVar4;
  }
  pwVar6 = L"m_libusb";
  _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0x36);
  asStack_90[0] = 0;
  asStack_90[1] = 0;
  asStack_90[2] = 0;
  asStack_90[3] = 0;
  asStack_90[4] = 0;
  asStack_90[5] = 0;
  asStack_90[6] = 0;
  asStack_90[7] = 0;
  lStack_78 = param_1;
  iVar2 = (**(code **)(*(longlong *)pwVar6 + 0x1a0))();
  if (iVar2 == 0) {
    psVar5 = asStack_90;
    do {
      uVar4 = 0;
      if (*psVar5 != -1) {
        uVar3 = (**(code **)(*(longlong *)pwVar6 + 0x198))(pwVar6,asStack_90,8);
        if (uVar3 == 0) {
          return 0;
        }
        goto LAB_14034087c;
      }
      psVar5 = psVar5 + 1;
    } while (psVar5 != asStack_90 + 8);
    uVar3 = (**(code **)(*(longlong *)pwVar6 + 0x198))(pwVar6,asStack_90,8);
    psVar5 = asStack_90;
    if (uVar3 != 0) {
LAB_14034087c:
      FUN_140028670(DAT_1411d8da0,"BSP: Failed to security check of usb device (%s)",
                    *(undefined8 *)(*(longlong *)(pwVar6 + 0x14) + 8));
      return (ulonglong)uVar3;
    }
    do {
      if (*psVar5 != -1) {
        iVar2 = (**(code **)(*(longlong *)pwVar6 + 0x1a8))(pwVar6,asStack_90,8);
        if (iVar2 == 0) {
          return 0;
        }
        FUN_140028670(DAT_1411d8da0,"BSP: Failed to set new security key.");
        goto LAB_1403408f2;
      }
      psVar5 = psVar5 + 1;
    } while (psVar5 != asStack_90 + 8);
  }
  else {
    FUN_140028670(DAT_1411d8da0,"BSP: Failed to get security key.");
LAB_1403408f2:
    uVar4 = 0xfffffffc;
  }
  return uVar4;
}

