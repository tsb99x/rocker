#pragma once

typedef enum status {
        NO_ERROR = 0,
        STR_POOL_OVERFLOW,
        NODE_POOL_OVERFLOW
} status_t;

const char *message_for_status(
        status_t err
);
