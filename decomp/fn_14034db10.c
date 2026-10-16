// FUN_14034db10

undefined8 FUN_14034db10(undefined8 *param_1,undefined4 param_2,longlong *param_3)

{
  byte bVar1;
  undefined1 auVar2 [16];
  int iVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  wchar_t *pwVar6;
  ulonglong uVar7;
  uint uVar8;
  uint uVar9;
  longlong *plVar10;
  bool bVar11;
  double dVar12;
  undefined8 extraout_XMM0_Qa;
  
  switch(param_2) {
  case 0x2c:
    uVar4 = *(undefined8 *)*param_3;
    bVar11 = ((undefined8 *)*param_3)[1] != 0;
    *(bool *)((longlong)param_1 + 9) = bVar11;
    if ((uint)uVar4 < 0xf) {
      iVar3 = FUN_14034d240(param_1,3,
                            (uint)*(byte *)(param_1 + 1) +
                            ((uint)bVar11 << ((char)uVar4 + 1U & 0x1f)) & 0xffff);
      if (iVar3 == 0) {
        return 0;
      }
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,3);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    _wassert(L"index >= 0 && index < 15",L"..\\..\\..\\hal\\awg\\awg.cpp",0x54);
    goto LAB_14034fbdf;
  case 0x2d:
    uVar7 = *(ulonglong *)*param_3;
    *(int *)((longlong)param_1 + 0xc) = (int)((ulonglong *)*param_3)[1];
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,1,*(undefined2 *)((longlong)param_1 + 0xc));
      if (iVar3 == 0) {
        if ((*(int *)((longlong)param_1 + 0xc) == 2) &&
           (iVar3 = FUN_14034d2d0(param_1,uVar7 & 0xffffffff,0x412e848000000000), iVar3 != 0)) {
          return 0xffffffff;
        }
        iVar3 = FUN_14034d240(param_1,2,0);
        if (iVar3 == 0) {
          return 0;
        }
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,2);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
      else {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,1);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    break;
  case 0x2e:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0,uVar7 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x2f:
    uVar7 = *(ulonglong *)*param_3;
    dVar12 = (double)((ulonglong *)*param_3)[1] / 1000000.0;
    param_1[2] = dVar12;
    *(int *)(param_1 + 3) = (int)(longlong)(dVar12 * 40.0);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,4,*(undefined2 *)(param_1 + 3));
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,4);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,5,*(undefined2 *)((longlong)param_1 + 0x1a));
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = 5;
      goto LAB_14034ea58;
    }
    if ((*(int *)((longlong)param_1 + 0xc) != 2) &&
       (iVar3 = FUN_14034d2d0(param_1,uVar7 & 0xffffffff,param_1[2]), iVar3 != 0)) {
      return 0xffffffff;
    }
    goto LAB_14034ea38;
  case 0x30:
    uVar7 = (ulonglong)(((double)(*(ulonglong *)(*param_3 + 8) / 1000000) / 360.0) * 4000000000.0);
    iVar3 = FUN_14034d240(param_1,6,uVar7 & 0xffff);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,7,uVar7 >> 0x10 & 0xffff);
      if (iVar3 == 0) {
        return 0;
      }
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,7);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,6);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    break;
  case 0x31:
    uVar7 = (ulonglong)*(uint *)*param_3;
    param_1[6] = ((double)*(ulonglong *)((uint *)*param_3 + 2) * 0.91525) / 1000000.0;
    goto LAB_14034de38;
  case 0x32:
    uVar7 = (ulonglong)*(uint *)*param_3;
    param_1[7] = (double)*(ulonglong *)((uint *)*param_3 + 2) / 6000000.0;
    goto LAB_14034de38;
  case 0x33:
    uVar7 = (ulonglong)*(uint *)*param_3;
    param_1[8] = (double)*(ulonglong *)((uint *)*param_3 + 2) / 6000000.0;
LAB_14034de38:
    uVar4 = FUN_14034d9a0(param_1,uVar7);
    return uVar4;
  case 0x34:
    uVar7 = (ulonglong)((((double)*(ulonglong *)(*param_3 + 8) / 1000000.0) / 100.0) * 4000000000.0)
    ;
    iVar3 = FUN_14034d240(param_1,10,uVar7 & 0xffff);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,0xb,uVar7 >> 0x10 & 0xffff);
      if (iVar3 == 0) {
        iVar3 = FUN_14034d240(param_1,0xc,
                              (int)(65472.0 / (double)((uint)(uVar7 >> 0x16) & 0x3ff)) & 0xffff);
        if (iVar3 == 0) {
          iVar3 = FUN_14034d240(param_1,0xd,
                                (int)(65472.0 / (double)(4000000000 - (uVar7 & 0xffffffff) >> 0x16))
                                & 0xffff);
          if (iVar3 == 0) {
            return 0;
          }
          plVar10 = (longlong *)*param_1;
          uVar4 = 0xd;
          goto LAB_14034ea58;
        }
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0xc);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
      else {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0xb);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,10);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    break;
  default:
    return 0xfffffff8;
  case 0x37:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    *(int *)(param_1 + 9) = (int)uVar7;
    iVar3 = FUN_14034d240(param_1,0x1a,uVar7 & 0xffff);
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x1a);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x38:
    iVar3 = FUN_14034d240(param_1,0x1b,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x1b);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x39:
    iVar3 = FUN_14034d240(param_1,0x1c,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x1c);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x3a:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    uVar7 = (ulonglong)(((double)uVar7 / 1000000.0) * 40.0);
    iVar3 = FUN_14034d240(param_1,0x1d,uVar7 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x1d);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x1e,uVar7 >> 0x10 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x1e);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x3b:
    uVar7 = *(ulonglong *)*param_3;
    dVar12 = (double)((ulonglong *)*param_3)[1] / 1000000.0;
    param_1[10] = dVar12;
    if (*(int *)(param_1 + 9) == 6) {
      uVar9 = 0x803;
      uVar8 = 0x10000;
    }
    else {
      iVar3 = (int)((2.0 - dVar12 / 100.0) * 512.0 + 512.0);
      uVar9 = iVar3 * 4;
      if (100.0 < dVar12) {
        auVar2._8_8_ = 0;
        auVar2._0_8_ = (longlong)iVar3;
        uVar9 = uVar9 + 2 & 0xffff;
        uVar8 = (uint)(longlong)(double)SUB168((ZEXT816(0) << 0x40 | ZEXT816(0x2000000)) / auVar2,0)
        ;
      }
      else {
        uVar9 = uVar9 & 0xffff;
        uVar8 = (uint)(longlong)(((dVar12 * 33554432.0) / 100.0) / 1023.0);
      }
    }
    iVar3 = FUN_14034d240(param_1,0x1f,uVar9);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,0x20,(short)uVar8);
      if (iVar3 == 0) {
        iVar3 = FUN_14034d240(param_1,0x21,uVar8 >> 0x10);
        if (iVar3 == 0) {
          uVar7 = uVar7 & 0xffffffff;
          goto LAB_14034de38;
        }
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0x21);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
      else {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0x20);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x1f);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    break;
  case 0x3c:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    uVar7 = (ulonglong)(((double)uVar7 / 1000000.0) * 40.0 * 0.5);
    iVar3 = FUN_14034d240(param_1,0x22,uVar7 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x22);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x23,uVar7 >> 0x10 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x23);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x3d:
    uVar7 = (ulonglong)(((double)(*(ulonglong *)(*param_3 + 8) / 1000000) / 360.0) * 40.0 * 0.5);
    iVar3 = FUN_14034d240(param_1,0x24,uVar7 & 0xffff);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,0x25,uVar7 >> 0x10 & 0xffff);
      if (iVar3 == 0) {
        return 0;
      }
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x25);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x24);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    break;
  case 0x3e:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    uVar7 = (ulonglong)(((double)uVar7 / 1000000.0) * 40.0);
    iVar3 = FUN_14034d240(param_1,0x26,uVar7 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x26);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x27,uVar7 >> 0x10 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x27);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x3f:
    iVar3 = FUN_14034d240(param_1,0x28,*(longlong *)(*param_3 + 8) != 0);
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x28);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x40:
    uVar7 = *(ulonglong *)*param_3;
    *(int *)(param_1 + 0xb) = (int)((ulonglong *)*param_3)[1];
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d4f0(param_1,uVar7 & 0xffffffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x49);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x3a,*(undefined2 *)(param_1 + 0xb));
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x3a);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x41:
    uVar7 = *(ulonglong *)*param_3;
    *(bool *)((longlong)param_1 + 0x5c) = ((ulonglong *)*param_3)[1] == 1;
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d4f0(param_1,uVar7 & 0xffffffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x49);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x3b,*(undefined1 *)((longlong)param_1 + 0x5c));
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x3b);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x42:
    uVar7 = *(ulonglong *)*param_3;
    dVar12 = ((double)((ulonglong *)*param_3)[1] / 1000000.0) * 40.0;
    if (9.223372036854776e+18 <= dVar12) {
      uVar5 = (longlong)(dVar12 - 9.223372036854776e+18) ^ 0x8000000000000000;
    }
    else {
      uVar5 = (ulonglong)dVar12;
    }
    param_1[0xc] = uVar5;
    if (uVar5 != 0) {
      iVar3 = FUN_14034d240(param_1,2,1);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,2);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      iVar3 = FUN_14034d3f0(param_1,uVar7 & 0xffffffff);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0x3e);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      goto LAB_14034ea38;
    }
    goto LAB_14034fc13;
  case 0x43:
    dVar12 = ((double)*(ulonglong *)(*param_3 + 8) / 1000000.0) * 40.0;
    if (9.223372036854776e+18 <= dVar12) {
      uVar7 = (longlong)(dVar12 - 9.223372036854776e+18) ^ 0x8000000000000000;
    }
    else {
      uVar7 = (ulonglong)dVar12;
    }
    param_1[0xd] = uVar7;
    if (uVar7 != 0) {
      iVar3 = FUN_14034d240(param_1,2,1);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,2);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      iVar3 = FUN_14034d240(param_1,0x41,*(undefined2 *)(param_1 + 0xd));
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0x41);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      iVar3 = FUN_14034d240(param_1,0x42,*(undefined2 *)((longlong)param_1 + 0x6a));
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,0x42);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      goto LAB_14034ea38;
    }
LAB_14034fbdf:
    _wassert(L"m_sweep_end != 0",L"..\\..\\..\\hal\\awg\\awg.cpp",0x17b);
LAB_14034fbf9:
    _wassert(L"period != 0",L"..\\..\\..\\hal\\awg\\awg.cpp",0x1cd);
LAB_14034fc13:
    pwVar6 = L"m_sweep_start != 0";
    _wassert(L"m_sweep_start != 0",L"..\\..\\..\\hal\\awg\\awg.cpp",0x16d);
    bVar1 = *(byte *)((longlong)pwVar6 + 9);
    *(undefined1 *)(pwVar6 + 4) = 1;
    iVar3 = FUN_14034d240(extraout_XMM0_Qa,2,1);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(pwVar6,3,bVar1 + 1 + (uint)bVar1);
      if (iVar3 != 0) {
        plVar10 = *(longlong **)pwVar6;
        uVar4 = 1;
        goto LAB_14034fc98;
      }
      uVar4 = FUN_14034d240(pwVar6,2,0);
      if ((int)uVar4 == 0) {
        return uVar4;
      }
    }
    plVar10 = *(longlong **)pwVar6;
    uVar4 = 2;
LAB_14034fc98:
    uVar4 = FUN_14034cf70(pwVar6,uVar4);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","Start",uVar4);
    return 0xffffffff;
  case 0x44:
    uVar7 = *(ulonglong *)*param_3;
    param_1[0xe] = ((ulonglong *)*param_3)[1];
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d4f0(param_1,uVar7 & 0xffffffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x49);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    goto LAB_14034ea38;
  case 0x45:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    iVar3 = FUN_14034d240(param_1,2,1);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,2);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    uVar7 = (ulonglong)(((double)uVar7 / 1000000.0) * 42.94967296);
    iVar3 = FUN_14034d240(param_1,0x47,uVar7 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x47);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
    iVar3 = FUN_14034d240(param_1,0x48,uVar7 >> 0x10 & 0xffff);
    if (iVar3 != 0) {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x48);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
      break;
    }
LAB_14034ea38:
    iVar3 = FUN_14034d240(param_1,2,0);
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = 2;
LAB_14034ea58:
    uVar4 = FUN_14034cf70(param_1,uVar4);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","ScpiWrite",uVar4);
    return 0xffffffff;
  case 0x46:
    iVar3 = FUN_14034d240(param_1,0x51,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x51);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x47:
    iVar3 = FUN_14034d240(param_1,0x52,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x52);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x48:
    iVar3 = FUN_14034d240(param_1,0x53,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x53);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x49:
    iVar3 = FUN_14034d240(param_1,0x54,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x54);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x4a:
    iVar3 = FUN_14034d240(param_1,0x55,*(longlong *)(*param_3 + 8) != 0);
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x55);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x4b:
    uVar7 = *(ulonglong *)(*param_3 + 8);
    if (uVar7 != 0) {
      iVar3 = FUN_14034d240(param_1,2,1);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,2);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      uVar7 = (ulonglong)((1000000000000.0 / (double)uVar7) * 42.94967296);
      iVar3 = FUN_14034d240(param_1,99,uVar7 & 0xffff);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,99);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      iVar3 = FUN_14034d240(param_1,100,uVar7 >> 0x10 & 0xffff);
      if (iVar3 != 0) {
        plVar10 = (longlong *)*param_1;
        uVar4 = FUN_14034cf70(param_1,100);
        if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
          *(undefined1 *)(plVar10 + 7) = 0;
        }
        else {
          (**(code **)(*plVar10 + 0x38))(plVar10,0);
        }
        break;
      }
      goto LAB_14034ea38;
    }
    goto LAB_14034fbf9;
  case 0x4c:
    iVar3 = FUN_14034d240(param_1,0x60,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x60);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x4d:
    iVar3 = FUN_14034d240(param_1,0x61,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x61);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x4e:
    iVar3 = FUN_14034d240(param_1,0x62,*(undefined2 *)(*param_3 + 8));
    if (iVar3 == 0) {
      return 0;
    }
    plVar10 = (longlong *)*param_1;
    uVar4 = FUN_14034cf70(param_1,0x62);
    if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
      *(undefined1 *)(plVar10 + 7) = 0;
    }
    else {
      (**(code **)(*plVar10 + 0x38))(plVar10,0);
    }
    break;
  case 0x4f:
    uVar7 = *(ulonglong *)(*param_3 + 8) >> 3;
    iVar3 = FUN_14034d240(param_1,0x65,uVar7 / 0x7d & 0xffff);
    if (iVar3 == 0) {
      iVar3 = FUN_14034d240(param_1,0x66,uVar7 / 0x7d0000 & 0xffff);
      if (iVar3 == 0) {
        return 0;
      }
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x66);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
    else {
      plVar10 = (longlong *)*param_1;
      uVar4 = FUN_14034cf70(param_1,0x65);
      if (*(code **)(*plVar10 + 0x38) == FUN_1405c1fb0) {
        *(undefined1 *)(plVar10 + 7) = 0;
      }
      else {
        (**(code **)(*plVar10 + 0x38))(plVar10,0);
      }
    }
  }
  FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","ScpiWrite",uVar4);
  return 0xffffffff;
}

