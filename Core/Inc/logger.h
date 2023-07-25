#ifndef _LOGGER_H
#define _LOGGER_H 

#include "main.h"
#include <stdbool.h>

typedef enum {
    INFO_L,
    ERROR_L,
    WARNING_L
} log_type_t;


bool logger_init(UART_HandleTypeDef* handle);
void log_print(log_type_t type, const char* format, ...);


#endif