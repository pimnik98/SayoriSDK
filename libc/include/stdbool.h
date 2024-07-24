#ifndef SAYORISDK_STDBOOL_H
#define SAYORISDK_STDBOOL_H

#ifndef __cplusplus

typedef enum {
    false = 0,
    true = 1
} bool;

#define __bool_true_false_are_defined 1 /// Определение макросов согласно стандарту IEEE Std 1003.1-2001

#endif

#endif //SAYORISDK_STDBOOL_H
