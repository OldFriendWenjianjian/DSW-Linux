// FUN_140029c70

longlong * FUN_140029c70(longlong param_1,char *param_2)

{
  int iVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong local_20;
  
  if (*(char *)(param_1 + 0x70) != '\0') {
    if (*(char *)(param_1 + 0xe8) != '\0') {
      iVar1 = FUN_14036b300(param_1 + 0x78,param_2,0,0);
      if (-1 < iVar1) {
        local_20 = 0;
        lVar2 = FUN_140370680(param_1 + 0x78,param_2,&local_20,0);
        if (lVar2 != 0) {
          plVar3 = (longlong *)FUN_1407a4630(0x10);
          *plVar3 = lVar2;
          plVar3[1] = local_20;
          return plVar3;
        }
      }
    }
    iVar1 = strcmp(param_2,"dsw_configs");
    if (iVar1 != 0) {
      local_20 = 0;
      lVar2 = FUN_140370680(param_1,param_2,&local_20,0);
      if (lVar2 != 0) {
        plVar3 = (longlong *)FUN_1407a4630(0x10);
        *plVar3 = lVar2;
        plVar3[1] = local_20;
        return plVar3;
      }
    }
  }
  return (longlong *)0x0;
}

