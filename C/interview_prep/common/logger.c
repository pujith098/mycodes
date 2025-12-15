#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "logger.h"

// Global log level
static int LOG_LEVEL = INFO;

// Initialize logger
void logger_init(void) {
    // Check environment variable for log level
    const char *env = getenv("LOG_LEVEL");
    if (env) {
        if (strcmp(env, "DEBUG") == 0) LOG_LEVEL = DEBUG;
        else if (strcmp(env, "INFO") == 0) LOG_LEVEL = INFO;
        else if (strcmp(env, "WARN") == 0) LOG_LEVEL = WARN;
    }
}

// Internal logger function
static void log_message(const char *level, const char *fmt, va_list args) {
    printf("[%s] ", level);
    vprintf(fmt, args);
    printf("\n");
    fflush(stdout);
}

// Public logging functions
void logger_info(const char *fmt, ...) {
    if (LOG_LEVEL <= INFO) {
        va_list args;
        va_start(args, fmt);
        log_message("INFO", fmt, args);
        va_end(args);
    }
}

void logger_warn(const char *fmt, ...) {
    if (LOG_LEVEL <= WARN) {
        va_list args;
        va_start(args, fmt);
        log_message("WARN", fmt, args);
        va_end(args);
    }
}

void logger_debug(const char *fmt, ...) {
    if (LOG_LEVEL <= DEBUG) {
        va_list args;
        va_start(args, fmt);
        log_message("DEBUG", fmt, args);
        va_end(args);
    }
}

