// FUN_140340ca0

undefined * FUN_140340ca0(longlong param_1)

{
  longlong *plVar1;
  undefined *puVar2;
  longlong *plVar3;
  bool bVar4;
  
  if (*(longlong *)(param_1 + 0x18) == 0) {
    _wassert(L"m_libusb",L"..\\..\\..\\hal\\usb\\usbbsp.cpp",0xb3);
    puVar2 = &DAT_1411dd8b8;
    do {
      plVar3 = *(longlong **)(puVar2 + 8);
      plVar1 = *(longlong **)(puVar2 + 0x10);
      if (plVar1 != plVar3) {
        do {
          if ((longlong *)*plVar3 != plVar3 + 2) {
            thunk_FUN_1407a45e0((longlong *)*plVar3,plVar3[2] + 1);
          }
          plVar3 = plVar3 + 4;
        } while (plVar1 != plVar3);
        plVar3 = *(longlong **)(puVar2 + 8);
      }
      if (plVar3 != (longlong *)0x0) {
        thunk_FUN_1407a45e0(plVar3,*(longlong *)(puVar2 + 0x18) - (longlong)plVar3);
      }
      bVar4 = puVar2 != &DAT_1411dcc60;
      puVar2 = puVar2 + -0x28;
    } while (bVar4);
    return &DAT_1411dcc38;
  }
  puVar2 = (undefined *)FUN_1403bada0();
  if (4 < (int)puVar2 - 1U) {
    FUN_140028670(DAT_1411d8da0,"%s:%d, Unknown USB speed: %d","GetSpeed",0xc1,(int)puVar2);
    return (undefined *)0x0;
  }
  return puVar2;
}

