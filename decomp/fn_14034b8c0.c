// FUN_14034b8c0

void FUN_14034b8c0(longlong param_1)

{
  ulonglong uVar1;
  undefined1 *_Src;
  longlong lVar2;
  ulonglong *puVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int iVar11;
  undefined1 *puVar12;
  longlong lVar13;
  longlong lVar14;
  undefined8 uVar15;
  undefined4 uStack_b4;
  ulonglong uStack_b0;
  longlong lStack_a8;
  char cStack_a0;
  undefined8 uStack_98;
  ulonglong *puStack_90;
  ulonglong uStack_88;
  ulonglong uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  
  while( true ) {
    uStack_b4 = 0;
    cStack_a0 = 0;
    lStack_a8 = *(longlong *)(param_1 + 8) + 0x48;
    iVar11 = FUN_1403b6360();
    if (iVar11 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_140ba5010(iVar11);
    }
    lVar14 = *(longlong *)(param_1 + 8);
    cStack_a0 = '\x01';
    while ((*(longlong *)(lVar14 + 0x80) == *(longlong *)(lVar14 + 0x60) &&
           (*(char *)(lVar14 + 0x3c) == '\0'))) {
      FUN_1406fcd70(lVar14 + 0xa0,&lStack_a8);
    }
    lVar14 = *(longlong *)(param_1 + 8);
    if ((*(longlong *)(lVar14 + 0x80) == *(longlong *)(lVar14 + 0x60)) &&
       (*(char *)(lVar14 + 0x3c) != '\0')) {
      *(undefined1 *)(lVar14 + 0x33) = 0;
      goto LAB_14034beb7;
    }
    FUN_140028940(DAT_1411d8da0,"BSP: Queue thread running, queue size: %d",
                  (*(longlong *)(lVar14 + 0x80) - *(longlong *)(lVar14 + 0x88) >> 3) *
                  -0x3333333333333333 +
                  ((*(longlong *)(lVar14 + 0x98) - *(longlong *)(lVar14 + 0x78) >> 3) + -1 +
                  (ulonglong)(*(longlong *)(lVar14 + 0x98) == 0)) * 0xc +
                  (*(longlong *)(lVar14 + 0x70) - *(longlong *)(lVar14 + 0x60) >> 3) *
                  -0x3333333333333333);
    if (cStack_a0 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_140ba5010(1);
    }
    if (lStack_a8 != 0) {
      FUN_1403b6650();
      cStack_a0 = '\0';
    }
    iVar11 = FUN_14034ae50(*(undefined8 *)(param_1 + 8),&uStack_b4);
    if (iVar11 != 0) break;
    iVar11 = FUN_14034ae50(*(undefined8 *)(param_1 + 8),&uStack_b4);
    if (iVar11 != 0) {
      FUN_140028670(DAT_1411d8da0,"BSP: Queue handshake (Wait Ready) failed.");
      goto LAB_14034bd40;
    }
    if (lStack_a8 == 0) {
                    /* WARNING: Subroutine does not return */
      FUN_140ba5010(1);
    }
    if (cStack_a0 != '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_140ba5010(0x24);
    }
    iVar11 = FUN_1403b6360();
    if (iVar11 != 0) {
                    /* WARNING: Subroutine does not return */
      FUN_140ba5010(iVar11);
    }
    lVar14 = *(longlong *)(param_1 + 8);
    cStack_a0 = '\x01';
    puVar12 = *(undefined1 **)(lVar14 + 0x60);
    if (*(undefined1 **)(lVar14 + 0x80) != puVar12) {
      do {
        uStack_98 = CONCAT71(uStack_98._1_7_,*puVar12);
        uVar1 = *(ulonglong *)(puVar12 + 0x10);
        _Src = *(undefined1 **)(puVar12 + 8);
        uStack_98 = CONCAT44(*(undefined4 *)(puVar12 + 4),
                             CONCAT22(*(undefined2 *)(puVar12 + 2),(undefined2)uStack_98));
        puStack_90 = &uStack_80;
        uStack_b0 = uVar1;
        if (uVar1 < 0x10) {
          if (uVar1 == 1) {
            uStack_80 = CONCAT71(uStack_80._1_7_,*_Src);
          }
          else if (uVar1 != 0) goto LAB_14034bc12;
        }
        else {
          puStack_90 = (ulonglong *)FUN_14073da20(&puStack_90,&uStack_b0,0);
          uStack_80 = uStack_b0;
LAB_14034bc12:
          memcpy(puStack_90,_Src,uVar1);
        }
        *(undefined1 *)((longlong)puStack_90 + uStack_b0) = 0;
        lVar14 = *(longlong *)(param_1 + 8);
        lVar13 = *(longlong *)(lVar14 + 0x60);
        lVar2 = *(longlong *)(lVar13 + 8);
        uStack_88 = uStack_b0;
        if (lVar13 == *(longlong *)(lVar14 + 0x70) + -0x28) {
          if (lVar2 != *(longlong *)(lVar14 + 0x70) + -0x10) {
            thunk_FUN_1407a45e0(lVar2,*(longlong *)(lVar13 + 0x18) + 1);
          }
          thunk_FUN_1407a45e0(*(undefined8 *)(lVar14 + 0x68),0x1e0);
          lVar13 = *(longlong *)(*(longlong *)(lVar14 + 0x78) + 8);
          *(longlong *)(lVar14 + 0x78) = *(longlong *)(lVar14 + 0x78) + 8;
          *(longlong *)(lVar14 + 0x68) = lVar13;
          *(longlong *)(lVar14 + 0x70) = lVar13 + 0x1e0;
        }
        else {
          if (lVar2 != lVar13 + 0x18) {
            thunk_FUN_1407a45e0(lVar2,*(longlong *)(lVar13 + 0x18) + 1);
            lVar13 = *(longlong *)(lVar14 + 0x60);
          }
          lVar13 = lVar13 + 0x28;
        }
        *(longlong *)(lVar14 + 0x60) = lVar13;
        if (cStack_a0 == '\0') {
                    /* WARNING: Subroutine does not return */
          FUN_140ba5010(1);
        }
        if (lStack_a8 == 0) {
          if (uStack_98._4_4_ != 0) goto LAB_14034bf13;
LAB_14034bb58:
          uStack_b0 = CONCAT62(CONCAT51(uStack_b0._3_5_,(char)(uStack_98 >> 0x18)),
                               CONCAT11((char)(uStack_98 >> 0x10),(undefined1)uStack_98));
          iVar11 = FUN_140340fd0(*(undefined8 *)(param_1 + 8),&uStack_b0,3,puStack_90);
          if (iVar11 == 0) {
            FUN_140028940(DAT_1411d8da0,"BSP: Queue set %s(0x%02X)=0x%04X");
          }
          else {
            FUN_140028670(DAT_1411d8da0,"BSP: Queue set %s(0x%02X)=0x%04X failed.",puStack_90,
                          uStack_98 & 0xff,uStack_98._2_2_);
          }
          if (lStack_a8 == 0) {
LAB_14034bf13:
                    /* WARNING: Subroutine does not return */
            FUN_140ba5010(1);
          }
          if (cStack_a0 != '\0') {
                    /* WARNING: Subroutine does not return */
            FUN_140ba5010(0x24);
          }
        }
        else {
          FUN_1403b6650();
          cStack_a0 = '\0';
          if (uStack_98._4_4_ == 0) goto LAB_14034bb58;
          if (lStack_a8 == 0) goto LAB_14034bf13;
        }
        iVar11 = FUN_1403b6360();
        if (iVar11 != 0) {
                    /* WARNING: Subroutine does not return */
          FUN_140ba5010(iVar11);
        }
        cStack_a0 = '\x01';
        if (puStack_90 != &uStack_80) {
          thunk_FUN_1407a45e0(puStack_90,uStack_80 + 1);
        }
        lVar14 = *(longlong *)(param_1 + 8);
        puVar12 = *(undefined1 **)(lVar14 + 0x60);
      } while (puVar12 != *(undefined1 **)(lVar14 + 0x80));
      if (cStack_a0 == '\0') {
                    /* WARNING: Subroutine does not return */
        FUN_140ba5010(1);
      }
    }
    if (lStack_a8 != 0) {
      FUN_1403b6650(lStack_a8);
      lVar14 = *(longlong *)(param_1 + 8);
      cStack_a0 = '\0';
    }
    iVar11 = FUN_14034ae50(lVar14,&uStack_b4);
    if (iVar11 != 0) {
      FUN_140028670(DAT_1411d8da0,"BSP: Queue handshake (Done) failed.");
      goto LAB_14034bd40;
    }
    if ((cStack_a0 != '\0') && (lStack_a8 != 0)) {
      FUN_1403b6650();
    }
  }
  FUN_140028670(DAT_1411d8da0,"BSP: Queue handshake (Prepare) failed.");
LAB_14034bd40:
  if (lStack_a8 == 0) {
                    /* WARNING: Subroutine does not return */
    FUN_140ba5010(1);
  }
  if (cStack_a0 != '\0') {
                    /* WARNING: Subroutine does not return */
    FUN_140ba5010(0x24);
  }
  iVar11 = FUN_1403b6360();
  if (iVar11 != 0) {
                    /* WARNING: Subroutine does not return */
    FUN_140ba5010(iVar11);
  }
  cStack_a0 = '\x01';
  FUN_1407001e0(&uStack_98);
  lVar14 = *(longlong *)(param_1 + 8);
  uVar1 = *(ulonglong *)(lVar14 + 0x50);
  *(ulonglong *)(lVar14 + 0x50) = uStack_98;
  puVar3 = *(ulonglong **)(lVar14 + 0x58);
  uVar5 = *(ulonglong *)(lVar14 + 0x60);
  uVar6 = *(ulonglong *)(lVar14 + 0x68);
  uVar4 = *(undefined8 *)(lVar14 + 0x70);
  uVar15 = *(undefined8 *)(lVar14 + 0x78);
  *(ulonglong **)(lVar14 + 0x58) = puStack_90;
  uVar7 = *(undefined8 *)(lVar14 + 0x80);
  uVar8 = *(undefined8 *)(lVar14 + 0x88);
  uVar9 = *(undefined8 *)(lVar14 + 0x90);
  uVar10 = *(undefined8 *)(lVar14 + 0x98);
  *(ulonglong *)(lVar14 + 0x60) = uStack_88;
  *(ulonglong *)(lVar14 + 0x68) = uStack_80;
  *(undefined8 *)(lVar14 + 0x70) = uStack_78;
  *(undefined8 *)(lVar14 + 0x78) = uStack_70;
  *(undefined8 *)(lVar14 + 0x80) = uStack_68;
  *(undefined8 *)(lVar14 + 0x88) = uStack_60;
  *(undefined8 *)(lVar14 + 0x90) = uStack_58;
  *(undefined8 *)(lVar14 + 0x98) = uStack_50;
  puStack_90 = puVar3;
  uStack_98 = uVar1;
  uStack_88 = uVar5;
  uStack_80 = uVar6;
  uStack_78 = uVar4;
  uStack_70 = uVar15;
  uStack_68 = uVar7;
  uStack_60 = uVar8;
  uStack_58 = uVar9;
  uStack_50 = uVar10;
  if (cStack_a0 == '\0') {
                    /* WARNING: Subroutine does not return */
    FUN_140ba5010(1);
  }
  if (lStack_a8 != 0) {
    FUN_1403b6650();
    lVar14 = *(longlong *)(param_1 + 8);
    cStack_a0 = '\0';
  }
  *(undefined1 *)(lVar14 + 0x33) = 0;
  uVar4 = DAT_1411d8da0;
  lVar14 = *(longlong *)(lVar14 + 8);
  *(undefined1 *)(lVar14 + 0xb0) = 1;
  *(undefined4 *)(lVar14 + 0x1c) = 6;
  FUN_140028850(uVar4,"Device (%s) status: %s",*(undefined8 *)(*(longlong *)(lVar14 + 0x20) + 8),
                "ERROR");
  uVar4 = *(undefined8 *)(*(longlong *)(param_1 + 8) + 8);
  uVar15 = FUN_1403bd030(uStack_b4);
  FUN_1405c2580(uVar4,"USB transfer error in RegQueueThread: %s",uVar15);
  FUN_1406ff2b0(&uStack_98);
LAB_14034beb7:
  if ((cStack_a0 != '\0') && (lStack_a8 != 0)) {
    FUN_1403b6650();
  }
  return;
}

