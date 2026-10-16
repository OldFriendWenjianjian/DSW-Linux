// FUN_14034c3b0

undefined4 FUN_14034c3b0(longlong *param_1,undefined8 param_2,undefined8 param_3,ulonglong param_4)

{
  code *pcVar1;
  undefined1 auVar2 [16];
  char cVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  longlong lVar8;
  char *in_stack_ffffffffffffff68;
  ushort local_7a;
  undefined8 local_78;
  undefined4 local_70;
  undefined1 local_68 [16];
  longlong local_58;
  
  FUN_140028850(DAT_1411d8da0,"BSP: Start FPGA configure: %d bytes.",param_4);
  if (*(code **)(*param_1 + 0x120) == FUN_1405c2330) {
    iVar4 = FUN_140349e30(param_1,0xfe,0xfffe,"PROG_B=0");
  }
  else {
    in_stack_ffffffffffffff68 = "PROG_B=0";
    iVar4 = (**(code **)(*param_1 + 0x120))(param_1,0xfe,0xfffffffffffffffe,2,"PROG_B=0");
  }
  if (iVar4 == 0) {
    local_68._8_4_ = 1000000;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = local_68._8_8_;
    local_68 = auVar2 << 0x40;
    do {
      iVar4 = FUN_1403b9980(local_68,local_68);
      if (iVar4 != -1) {
        pcVar1 = *(code **)(*param_1 + 0x120);
        goto joined_r0x00014034c5e9;
      }
      piVar6 = _errno();
    } while (*piVar6 == 4);
    pcVar1 = *(code **)(*param_1 + 0x120);
joined_r0x00014034c5e9:
    if (pcVar1 == FUN_1405c2330) {
      iVar4 = FUN_140349e30(param_1,0xfe,1,"PROG_B=1");
    }
    else {
      in_stack_ffffffffffffff68 = "PROG_B=1";
      iVar4 = (*pcVar1)(param_1,0xfe,1,2,"PROG_B=1");
    }
    if (iVar4 == 0) {
      local_58 = 0;
      local_68 = (undefined1  [16])0x0;
      lVar8 = 0;
      if (param_4 != 0) {
        FUN_140737bc0(local_68,param_4);
        lVar8 = local_68._0_8_;
      }
      iVar4 = FUN_14035c020(param_2,param_3,lVar8,param_4);
      if (iVar4 == 0) {
        iVar4 = 0xb;
        local_7a = 0;
        do {
          in_stack_ffffffffffffff68 =
               (char *)((ulonglong)in_stack_ffffffffffffff68 & 0xffffffff00000000);
          iVar5 = (**(code **)(*param_1 + 0x138))
                            (param_1,0xff,&local_7a,2,in_stack_ffffffffffffff68,"HW_STATUS");
          if (iVar5 != 0) goto LAB_14034c59a;
          if ((local_7a & 2) != 0) goto LAB_14034c531;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        FUN_140028670(DAT_1411d8da0,"BSP Error: Wait FPGA INIT_B timeout.");
LAB_14034c531:
        if (*(code **)(*param_1 + 0x120) == FUN_1405c2330) {
          iVar4 = FUN_140349e30(param_1,0xfc,param_4 & 0xffff,"SET_BULK_SIZE_LOW");
        }
        else {
          iVar4 = (**(code **)(*param_1 + 0x120))
                            (param_1,0xfc,param_4 & 0xffff,2,"SET_BULK_SIZE_LOW");
        }
        if (iVar4 == 0) {
          if (*(code **)(*param_1 + 0x120) == FUN_1405c2330) {
            iVar4 = FUN_140349e30(param_1,0xfd,param_4 >> 0x10 & 0xffff,"SET_BULK_SIZE_HIGH");
          }
          else {
            iVar4 = (**(code **)(*param_1 + 0x120))
                              (param_1,0xfd,param_4 >> 0x10,2,"SET_BULK_SIZE_HIGH");
          }
          if ((iVar4 == 0) &&
             (iVar4 = FUN_140341270(param_1,lVar8,param_4,"FPGA_CONFIG"), iVar4 == 0)) {
            iVar4 = 0xb;
            do {
              cVar3 = (**(code **)(*param_1 + 0x50))(param_1);
              if (cVar3 != '\0') {
                FUN_140028850(DAT_1411d8da0,"BSP: FPGA configure done: %d bytes.",param_4);
                uVar7 = 0;
                goto LAB_14034c5a0;
              }
              local_78 = 0;
              local_70 = 50000000;
              do {
                iVar5 = FUN_1403b9980(&local_78,&local_78);
                if (iVar5 != -1) break;
                piVar6 = _errno();
              } while (*piVar6 == 4);
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
            FUN_140028670(DAT_1411d8da0,"BSP Error: FPGA configure timeout.");
          }
        }
LAB_14034c59a:
        uVar7 = 0xffffffff;
      }
      else {
        FUN_140028670(DAT_1411d8da0,"BSP: Invalid FPGA bin file.");
        uVar7 = 0xfffffffa;
      }
LAB_14034c5a0:
      if (lVar8 == 0) {
        return uVar7;
      }
      thunk_FUN_1407a45e0(lVar8,local_58 - lVar8);
      return uVar7;
    }
  }
  return 0xffffffff;
}

