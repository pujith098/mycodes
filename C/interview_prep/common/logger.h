#ifndef LOGGER_H
#define LOGGER_H

#define DEBUG 0
#define INFO  1
#define WARN  2

void logger_init(void);
void logger_info(const char *fmt, ...);
void logger_warn(const char *fmt, ...);
void logger_debug(const char *fmt, ...);

#endif // LOGGER_H

