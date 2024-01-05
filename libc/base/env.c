#include "env.h"
#include "syscall.h"

env_t getenv() {
    env_t env;

    _syscall(ENV_GET_SYSCALL, (size_t) &env, 0, 0);

    return env;
}