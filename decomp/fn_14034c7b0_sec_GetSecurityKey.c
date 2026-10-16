
undefined4 FUN_14034c7b0(longlong *param_1,longlong param_2,int param_3)

{
  code *pcVar1;
  code *pcVar2;
  undefined2 uVar3;
  int iVar4;
  undefined8 extraout_RAX;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  undefined4 uVar8;
  undefined1 local_68 [16];
  longlong local_58;
  
  if (0x7f < param_3) {
    _wassert(L"len < (1 << (8 - 1))",L"..\\..\\..\\hal\\usb\\usbbsp3x.cpp",0x379);
    FUN_1407380a0();
                    /* WARNING: Subroutine does not return */
    FUN_14059a180(extraout_RAX);
  }
  local_58 = 0;
  lVar7 = (longlong)(param_3 * 2);
  local_68 = (undefined1  [16])0x0;
  lVar6 = 0;
  if (lVar7 != 0) {
    FUN_140737bc0(local_68,lVar7);
    lVar6 = local_68._0_8_;
  }
  uVar3 = 0x1000;
  pcVar1 = *(code **)(*param_1 + 0x148);
  pcVar2 = *(code **)(*param_1 + 0x118);
  if (pcVar2 != FUN_1405c2500) {
    uVar3 = (*pcVar2)(param_1);
  }
  iVar4 = (*pcVar1)(param_1,uVar3,param_3 * 2 & 0xff,lVar6);
  if (iVar4 == 0) {
    uVar8 = 0;
    if (0 < param_3) {
      lVar5 = 0;
      do {
        *(ushort *)(param_2 + lVar5) =
             CONCAT11(*(undefined1 *)(lVar6 + 1 + lVar5),*(undefined1 *)(lVar6 + lVar5));
        lVar5 = lVar5 + 2;
      } while (lVar7 != lVar5);
      goto LAB_14034c86d;
    }
  }
  else {
    uVar8 = 0xffffffff;
  }
  if (lVar6 == 0) {
    return uVar8;
  }
LAB_14034c86d:
  thunk_FUN_1407a45e0(lVar6,local_58 - lVar6);
  return uVar8;
}

