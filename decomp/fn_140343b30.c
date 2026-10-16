// FUN_140343b30

undefined4 FUN_140343b30(longlong *param_1,undefined8 param_2,undefined8 param_3,longlong param_4)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  code *pcVar4;
  longlong lVar5;
  undefined4 uVar6;
  char *pcVar7;
  byte local_69;
  undefined1 local_68 [16];
  undefined1 *local_58;
  
  FUN_140028850(DAT_1411d8da0,"Start FPGA configure: %d bytes.",param_4);
  if (*(code **)(*param_1 + 0x120) == FUN_1405c1fe0) {
    iVar1 = FUN_140342ed0(param_1,3,0,1,0xfffffffffffffffb,"PROG_B=0");
  }
  else {
    iVar1 = (**(code **)(*param_1 + 0x120))(param_1,3,0xfffffffffffffffb,1,"PROG_B=0");
  }
  lVar5 = *param_1;
  if (iVar1 == 0) {
    if (*(code **)(lVar5 + 0x120) == FUN_1405c1fe0) {
      iVar1 = FUN_140342ed0(param_1,5,0,1,0xfffffffffffffffc,"LED=00");
    }
    else {
      iVar1 = (**(code **)(lVar5 + 0x120))(param_1,5,0xfffffffffffffffc,1,"LED=00");
    }
    lVar5 = *param_1;
    if (iVar1 != 0) goto LAB_140343c90;
    if (*(code **)(lVar5 + 0x120) == FUN_1405c1fe0) {
      pcVar7 = (char *)0x0;
      iVar1 = FUN_140342ed0(param_1,3,0,1,4,"PROG_B=1");
    }
    else {
      pcVar7 = "PROG_B=1";
      iVar1 = (**(code **)(lVar5 + 0x120))(param_1,3,4,1,"PROG_B=1");
    }
    if (iVar1 == 0) {
      local_58 = (undefined1 *)0x0;
      puVar3 = (undefined1 *)0x0;
      local_68 = (undefined1  [16])0x0;
      if (param_4 != 0) {
        if (param_4 < 0) {
                    /* WARNING: Subroutine does not return */
          FUN_140ba4ce0("vector::_M_default_append");
        }
        puVar3 = (undefined1 *)FUN_1407a4630(param_4);
        *puVar3 = 0;
        if (param_4 != 1) {
          memset(puVar3 + 1,0,param_4 - 1);
        }
        local_58 = puVar3 + param_4;
        local_68._8_8_ = local_58;
        local_68._0_8_ = puVar3;
      }
      iVar1 = FUN_14035c020(param_2,param_3,puVar3,param_4);
      if (iVar1 != 0) {
        FUN_140028670(DAT_1411d8da0,"BSP: Invalid FPGA bin file.");
        uVar6 = 0xfffffffa;
        goto LAB_140343ebe;
      }
      local_69 = 0;
      iVar1 = 0xb;
      do {
        pcVar7 = (char *)((ulonglong)pcVar7 & 0xffffffff00000000);
        iVar2 = (**(code **)(*param_1 + 0x138))(param_1,2,&local_69,1,pcVar7,"HW_STATUS");
        if (iVar2 != 0) goto LAB_140343e80;
        if ((local_69 & 0x20) != 0) goto LAB_140343d4b;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      FUN_140028670(DAT_1411d8da0,"BSP Error: Wait FPGA INIT_B timeout.");
LAB_140343d4b:
      if (*(code **)(*param_1 + 0x120) == FUN_1405c1fe0) {
        iVar1 = FUN_140342ed0(param_1,6,0,1,0xffffffffffffff7f,"INTRDY=0");
      }
      else {
        iVar1 = (**(code **)(*param_1 + 0x120))(param_1,6,0xffffffffffffff7f,1,"INTRDY=0");
      }
      lVar5 = *param_1;
      if (iVar1 != 0) goto LAB_140343f70;
      if (*(code **)(lVar5 + 0x120) == FUN_1405c1fe0) {
        iVar1 = FUN_140342ed0(param_1,10,0,3,param_4,"SET_BULK_WRITE_SIZE");
      }
      else {
        iVar1 = (**(code **)(lVar5 + 0x120))(param_1,10,param_4,3,"SET_BULK_WRITE_SIZE");
      }
      if (iVar1 == 0) {
        iVar1 = FUN_140341270(param_1,puVar3,param_4,"FPGA_CONFIG");
        lVar5 = *param_1;
        if (iVar1 != 0) {
LAB_140343f70:
          pcVar4 = *(code **)(lVar5 + 0x38);
          goto joined_r0x000140343f7e;
        }
        if (*(code **)(lVar5 + 0x120) == FUN_1405c1fe0) {
          pcVar7 = (char *)0x0;
          iVar1 = FUN_140342ed0(param_1,6,0,1,0x80,"INTRDY=1");
        }
        else {
          pcVar7 = "INTRDY=1";
          iVar1 = (**(code **)(lVar5 + 0x120))(param_1,6,0x80,1,"INTRDY=1");
        }
        lVar5 = *param_1;
        if (iVar1 != 0) goto LAB_140343f70;
        local_69 = 0;
        do {
          pcVar7 = (char *)((ulonglong)pcVar7 & 0xffffffff00000000);
          iVar1 = (**(code **)(*param_1 + 0x138))(param_1,2,&local_69,1,pcVar7,"HW_STATUS");
          if (iVar1 != 0) goto LAB_140343e80;
        } while (-1 < (char)local_69);
        if (*(code **)(*param_1 + 0x120) == FUN_1405c1fe0) {
          pcVar7 = (char *)0xffffffffffffff7f;
          iVar1 = FUN_140342ed0(param_1,6,0,1,0xffffffffffffff7f,"INTRDY=0");
        }
        else {
          pcVar7 = "INTRDY=0";
          iVar1 = (**(code **)(*param_1 + 0x120))(param_1,6,0xffffffffffffff7f,1,"INTRDY=0");
        }
        lVar5 = *param_1;
        if (iVar1 != 0) goto LAB_140343f70;
        local_69 = 0;
        iVar1 = 0xb;
        do {
          pcVar7 = (char *)((ulonglong)pcVar7 & 0xffffffff00000000);
          iVar2 = (**(code **)(*param_1 + 0x138))(param_1,2,&local_69,1,pcVar7,"HW_STATUS");
          if (iVar2 != 0) goto LAB_140343e80;
          if ((local_69 & 0x40) != 0) {
            if (*(code **)(*param_1 + 0x120) == FUN_1405c1fe0) {
              iVar1 = FUN_140342ed0(param_1,5,0,1,1,"LED=10");
            }
            else {
              iVar1 = (**(code **)(*param_1 + 0x120))(param_1,5,1,1,"LED=10");
            }
            if (iVar1 == 0) {
              iVar1 = (**(code **)(*param_1 + 0x120))(param_1,7,1,1,"GPIF_WORDWIDE=1");
              if (iVar1 == 0) {
                FUN_140028850(DAT_1411d8da0,"BSP: FPGA configure done: %d bytes.",param_4);
                uVar6 = 0;
                goto LAB_140343ebe;
              }
              pcVar4 = *(code **)(*param_1 + 0x38);
              if (pcVar4 != FUN_1405c1fb0) goto LAB_1403441f4;
LAB_1403441bd:
              *(undefined1 *)(param_1 + 7) = 0;
            }
            else {
              pcVar4 = *(code **)(*param_1 + 0x38);
              if (pcVar4 == FUN_1405c1fb0) goto LAB_1403441bd;
LAB_1403441f4:
              (*pcVar4)(param_1,0);
            }
            FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","FpgaConfig","config FPGA");
            goto LAB_140343eb9;
          }
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
        FUN_140028670(DAT_1411d8da0,"BSP Error: FPGA configure timeout.");
      }
      else {
LAB_140343e80:
        pcVar4 = *(code **)(*param_1 + 0x38);
joined_r0x000140343f7e:
        if (pcVar4 == FUN_1405c1fb0) {
          *(undefined1 *)(param_1 + 7) = 0;
        }
        else {
          (*pcVar4)(param_1,0);
        }
        FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","FpgaConfig","config FPGA");
      }
LAB_140343eb9:
      uVar6 = 0xffffffff;
LAB_140343ebe:
      if (puVar3 == (undefined1 *)0x0) {
        return uVar6;
      }
      thunk_FUN_1407a45e0(puVar3,(longlong)local_58 - (longlong)puVar3);
      return uVar6;
    }
    pcVar4 = *(code **)(*param_1 + 0x38);
    if (pcVar4 != FUN_1405c1fb0) goto LAB_140343ca0;
  }
  else {
LAB_140343c90:
    pcVar4 = *(code **)(lVar5 + 0x38);
    if (pcVar4 != FUN_1405c1fb0) {
LAB_140343ca0:
      (*pcVar4)(param_1,0);
      goto LAB_140343c52;
    }
  }
  *(undefined1 *)(param_1 + 7) = 0;
LAB_140343c52:
  FUN_140028670(DAT_1411d8da0,"%s: Failed to %s.","FpgaConfig","config FPGA");
  return 0xffffffff;
}

