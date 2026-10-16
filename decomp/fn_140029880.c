// FUN_140029880

void FUN_140029880(longlong param_1)

{
  byte *pbVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint uVar11;
  uint uVar12;
  ulonglong local_30;
  
  iVar4 = FUN_14036b300(param_1,"dsw_configs",0);
  if (-1 < iVar4) {
    local_30 = 0;
    lVar5 = FUN_1403705a0(param_1,iVar4,&local_30);
    *(longlong *)(param_1 + 0xf0) = lVar5;
    if (lVar5 != 0) {
      iVar4 = FUN_14036a770(param_1 + 0x78,lVar5,local_30);
      if (iVar4 != 0) {
LAB_140029aa5:
        *(undefined1 *)(param_1 + 0xe8) = 1;
        return;
      }
      puVar10 = *(uint **)(param_1 + 0xf0);
      if (3 < local_30) {
        uVar12 = 0;
        lVar5 = 0;
        do {
          pbVar1 = (byte *)((longlong)puVar10 + lVar5);
          cVar2 = (char)lVar5;
          lVar5 = lVar5 + 1;
          uVar12 = uVar12 | (uint)*pbVar1 << (cVar2 * '\b' & 0x1fU);
        } while (lVar5 != 4);
        uVar11 = 0;
        lVar5 = 0;
        *puVar10 = (uVar12 >> 7 | uVar12 << 0x19) + 0xedcba988 ^ 0x55aa55aa;
        do {
          pbVar1 = (byte *)((longlong)puVar10 + lVar5);
          cVar2 = (char)lVar5;
          lVar5 = lVar5 + 1;
          uVar11 = uVar11 | (uint)*pbVar1 << (cVar2 * '\b' & 0x1fU);
        } while (lVar5 != 4);
        puVar8 = puVar10 + 1;
        uVar12 = uVar11 >> 0x10;
        if (local_30 != 4) {
          do {
            uVar11 = uVar11 << 0xd ^ uVar11;
            uVar11 = uVar11 ^ uVar11 >> 0x11;
            uVar11 = (uVar11 ^ uVar11 << 5) * 0x19660d + 0x3c6ef35f;
            uVar3 = *puVar8;
            puVar9 = (uint *)((longlong)puVar8 + 1);
            *(byte *)puVar8 =
                 (byte)(uVar11 >> 0x18) ^ (byte)(uVar11 >> 0xb) ^ (byte)uVar3 ^ (byte)uVar12;
            puVar8 = puVar9;
            uVar12 = (uint)(byte)uVar3;
          } while (puVar9 != (uint *)((longlong)puVar10 + local_30));
        }
        puVar6 = (undefined1 *)((longlong)puVar10 + 0xf);
        puVar8 = puVar10;
        do {
          uVar12 = *puVar8;
          puVar7 = puVar6 + -1;
          *(undefined1 *)puVar8 = *puVar6;
          *puVar6 = (char)uVar12;
          puVar6 = puVar7;
          puVar8 = (uint *)((longlong)puVar8 + 1);
        } while ((undefined1 *)((longlong)puVar10 + 7) != puVar7);
        puVar10 = *(uint **)(param_1 + 0xf0);
        if (0x10 < local_30) {
          iVar4 = FUN_14036a770(param_1 + 0x78,puVar10 + 4,local_30 - 0x10,0);
          if (iVar4 != 0) goto LAB_140029aa5;
          puVar10 = *(uint **)(param_1 + 0xf0);
        }
      }
      FUN_140362110(puVar10);
      *(undefined8 *)(param_1 + 0xf0) = 0;
    }
  }
  return;
}

