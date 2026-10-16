// FUN_1403bb4d0

int FUN_1403bb4d0(longlong param_1,undefined8 *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  int iVar3;
  LPCRITICAL_SECTION lpCriticalSection;
  HANDLE pvVar4;
  
  lVar1 = *(longlong *)(param_1 + 8);
  FUN_1403baf60(lVar1,4,"libusb_open","open %d.%d",*(undefined1 *)(param_1 + 0x18),
                *(undefined1 *)(param_1 + 0x1a));
  if (*(int *)(param_1 + 0x48) == 0) {
    iVar3 = -4;
  }
  else {
    lpCriticalSection = calloc(1,0x6e8);
    if (lpCriticalSection == (LPCRITICAL_SECTION)0x0) {
      iVar3 = -0xb;
    }
    else {
      InitializeCriticalSection(lpCriticalSection);
      pvVar4 = (HANDLE)FUN_1403badb0(param_1);
      lpCriticalSection[1].LockSemaphore = pvVar4;
      iVar3 = FUN_1403c2c60(lpCriticalSection);
      if (iVar3 < 0) {
        FUN_1403baf60(*(undefined8 *)(param_1 + 8),4,"libusb_open","open %d.%d returns %d",
                      *(undefined1 *)(param_1 + 0x18),*(undefined1 *)(param_1 + 0x1a),iVar3);
        FUN_1403bb2e0(param_1);
        DeleteCriticalSection(lpCriticalSection);
        free(lpCriticalSection);
        return iVar3;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)(lVar1 + 0x68));
      plVar2 = *(longlong **)(lVar1 + 0x60);
      *(longlong *)&lpCriticalSection[1].LockCount = lVar1 + 0x58;
      lpCriticalSection[1].OwningThread = plVar2;
      *plVar2 = (longlong)&lpCriticalSection[1].LockCount;
      *(LONG **)(lVar1 + 0x60) = &lpCriticalSection[1].LockCount;
      LeaveCriticalSection((LPCRITICAL_SECTION)(lVar1 + 0x68));
      *param_2 = lpCriticalSection;
      iVar3 = 0;
    }
  }
  return iVar3;
}

