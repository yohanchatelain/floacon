#ifndef __FLOACON_LOGGER_H__
#define __FLOACON_LOGGER_H__

#include "logger.h"

void logger_info(const char *format, ...);
void logger_warning(const char *format, ...);
void logger_error(const char *format, ...);

#endif // __FLOACON_LOGGER_H__