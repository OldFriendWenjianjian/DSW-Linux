// FUN_1401f24f0

void FUN_1401f24f0(QFileDialog *param_1,QWidget *param_2)

{
  undefined8 uVar1;
  undefined8 local_b8;
  char *local_b0;
  undefined1 local_a8 [16];
  undefined8 local_98;
  undefined1 local_88 [16];
  undefined8 local_78;
  undefined1 local_68 [16];
  undefined8 local_58;
  
  local_68 = (undefined1  [16])0x0;
  local_88 = (undefined1  [16])0x0;
  local_a8 = (undefined1  [16])0x0;
  local_58 = 0;
  local_78 = 0;
  local_98 = 0;
  QFileDialog::QFileDialog
            (param_1,param_2,(QString *)local_a8,(QString *)local_88,(QString *)local_68);
  if ((int *)local_a8._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_a8._0_8_ = *(int *)local_a8._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_a8._0_8_ == 0) {
      free((void *)local_a8._0_8_);
    }
  }
  if ((int *)local_88._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_88._0_8_ = *(int *)local_88._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_88._0_8_ == 0) {
      free((void *)local_88._0_8_);
    }
  }
  if ((int *)local_68._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_68._0_8_ = *(int *)local_68._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_68._0_8_ == 0) {
      free((void *)local_68._0_8_);
    }
  }
  *(undefined ***)param_1 = &PTR_LAB_140fb1bc0;
  *(undefined ***)(param_1 + 0x10) = &PTR_FUN_140fb1d98;
  FUN_140287160();
  uVar1 = FUN_140283380();
  local_b8 = 9;
  local_b0 = "Open File";
  QString::fromUtf8((QString *)local_68,&local_b8);
  local_b8 = 0x11;
  local_b0 = "IDS_DLG_OPEN_FILE";
  QString::fromUtf8((QString *)local_88,&local_b8);
  FUN_140285080((QString *)local_a8,uVar1,2,(QString *)local_88,(QString *)local_68);
  QWidget::setWindowTitle((QString *)param_1);
  if ((int *)local_a8._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_a8._0_8_ = *(int *)local_a8._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_a8._0_8_ == 0) {
      free((void *)local_a8._0_8_);
    }
  }
  if ((int *)local_88._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_88._0_8_ = *(int *)local_88._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_88._0_8_ == 0) {
      free((void *)local_88._0_8_);
    }
  }
  if ((int *)local_68._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_68._0_8_ = *(int *)local_68._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_68._0_8_ == 0) {
      free((void *)local_68._0_8_);
    }
  }
  QFileDialog::setAcceptMode(param_1,0);
  local_b8 = 0x16;
  local_b0 = "DSWave Binary (*.dswb)";
  QString::fromUtf8((QString *)local_68,&local_b8);
  QFileDialog::setNameFilter((QString *)param_1);
  if ((int *)local_68._0_8_ != (int *)0x0) {
    LOCK();
    *(int *)local_68._0_8_ = *(int *)local_68._0_8_ + -1;
    UNLOCK();
    if (*(int *)local_68._0_8_ == 0) {
      free((void *)local_68._0_8_);
    }
  }
  QFileDialog::setDirectory((QString *)param_1);
  return;
}

