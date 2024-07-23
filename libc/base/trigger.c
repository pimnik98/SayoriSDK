#include "trigger.h"
#include "syscall.h"

/**
 * @brief - Зарегистрировать триггер
 *
 * @param int type - Код триггера
 * @param trigger_cmd_t handler - Команда для выполнения
 *
 * @return - В случае успеха индекс триггера, в противном случае -1
 */
int TriggerReg(int type,trigger_cmd_t handler) {
    int w = _syscall(SYSCALL_TRIGGER_REG, (int) type, (int) handler, 0);
    return w;
}

/**
 * @brief - Включить триггер
 *
 * @param int index - Индекс
 */
void TriggerOn(int index) {
    _syscall(SYSCALL_TRIGGER_ON, (int) index, 0, 0);
}

/**
 * @brief - Выключить триггер
 *
 * @param int index - Индекс
 */
void TriggerOff(int index) {
    _syscall(SYSCALL_TRIGGER_OFF, (int) index, 0, 0);
}

/**
 * @brief - Удалить триггер
 *
 * @param int index - Индекс
 */
void TriggerDel(int index) {
    _syscall(SYSCALL_TRIGGER_DEL, (int) index, 0, 0);
}
