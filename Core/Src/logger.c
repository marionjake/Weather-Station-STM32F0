#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <math.h>


UART_HandleTypeDef* logger_handle;
static SemaphoreHandle_t mutex;

char capture_buffer[100];
char message_buffer[100];


bool logger_init(UART_HandleTypeDef* handle) {
    logger_handle = handle;
    mutex = xSemaphoreCreateMutex();
    if(mutex != NULL && logger_handle != NULL)
        return true;
}

void log_print(log_type_t type, const char* format, ...) {
    if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
        memset(capture_buffer,0,sizeof(capture_buffer));
        memset(message_buffer,0,sizeof(message_buffer));
        va_list args;
        va_start(args, format);
        vsnprintf(capture_buffer, sizeof(capture_buffer), format, args);
        va_end(args);
        
        char log_type_buffer[8];
        if (type == INFO_L) {
            strncpy(log_type_buffer, "INFO", sizeof(log_type_buffer));
        } else if (type == ERROR_L) {
            strncpy(log_type_buffer, "ERROR", sizeof(log_type_buffer));
        } else if (type == WARNING_L)
        {
            strncpy(log_type_buffer, "WARNING", sizeof(log_type_buffer));
        }
        snprintf(message_buffer, sizeof(message_buffer), "[%s] %s\n", log_type_buffer, capture_buffer);
        HAL_UART_Transmit(logger_handle, message_buffer, strlen(message_buffer), 100);
    }
    xSemaphoreGive(mutex);
}
