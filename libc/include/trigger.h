#ifndef SAYORISDK_TRIGGER_H
#define SAYORISDK_TRIGGER_H

#include "stdint.h"
#define TRIGGER_MAIN_RUNNER		0x0000
#define TRIGGER_KEY_PRESSED		0x0001
#define TRIGGER_MOUSE_MOVE		0x0002
#define TRIGGER_MOUSE_CLICK		0x0003

#define SYSCALL_TRIGGER_REG     9       ///< КОД для регистрации триггера
#define SYSCALL_TRIGGER_ON      10      ///< КОД для включения триггера
#define SYSCALL_TRIGGER_OFF     11      ///< КОД для выключения триггера
#define SYSCALL_TRIGGER_DEL     12      ///< КОД для удаления триггера

typedef void (*trigger_cmd_t)(void*,void*,void*,void*,void*);

int  TriggerReg(int type,trigger_cmd_t handler);
void TriggerOn(int index);
void TriggerOff(int index);
void TriggerDel(int index);

#endif //SAYORISDK_TRIGGER_H
