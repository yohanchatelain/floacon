#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void logger_info(const char *format, ...) {
  fprintf(stdout, "Info: ");
  va_list ap;
  va_start(ap, format);
  vfprintf(stdout, format, ap);
  va_end(ap);
}

void logger_warning(const char *format, ...) {
  fprintf(stderr, "Warning: ");
  va_list ap;
  va_start(ap, format);
  vwarn(format, ap);
  va_end(ap);
}

void logger_error(const char *format, ...) {
  fprintf(stderr, "Error: ");
  va_list ap;
  va_start(ap, format);
  err(EXIT_FAILURE, format, ap);
}
