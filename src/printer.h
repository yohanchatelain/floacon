#ifndef __FLOACON_PRINTER_H__
#define __FLOACON_PRINTER_H__

#include <mpfr.h>

#include "types.h"

typedef enum {
  FLOACON_OUTPUT_FLOAT,
  FLOACON_OUTPUT_BINARY,
  FLOACON_OUTPUT_HEX,
  FLOACON_OUTPUT_SCIENTIFIC,
  FLOACON_OUTPUT_GENERAL
} floacon_output_format_t;

void floacon_print_float(floacon_t x);
void floacon_print_binary(floacon_t x);
void floacon_print_hex(floacon_t x);
void floacon_print_scientific(floacon_t x);
void floacon_print_general(floacon_t x);
void floacon_print(floacon_output_format_t format, floacon_t x);

#endif /* _FLOACON_PRINTER_H_ */