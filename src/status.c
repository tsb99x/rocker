#include "macro.h"

#include "status.h"

const char *messages[] = {
        "No error",             // NO_ERROR = 0,
        "String pool overflow", // STR_POOL_OVERFLOW,
        "Node pool overflow",   // NODE_POOL_OVERFLOW
};

const char *message_for_status(
        status_t err
) {
        if (err < 0 || err >= ARRLEN(messages))
                PANIC("No message defined for code %d\n", err);
        return messages[err];
}
