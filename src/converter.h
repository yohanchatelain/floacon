#ifndef _FLOACON_CONVERTER_H__
#define _FLOACON_CONVERTER_H__

#include <mpfr.h>

#include "types.h"

void floacon_set_exponent(floacon_format_t fmt);
void floacon_set_precision(floacon_format_t fmt);
void floacon_set_context(floacon_format_t fmt);
void floacon_convert(const char *input, int *base_ptr,
                     floacon_format_t source_fmt, floacon_format_t target_fmt,
                     mpfr_rnd_t rnd, mpfr_t x);

void print_usage();
void check_args(int argc, char *argv[]);

void floacon_from_float(char *out, mpfr_t x);
void floacon_from_binary(char *out, mpfr_t x);
void floacon_from_hex(char *out, mpfr_t x);
void floacon_from_scientific(char *out, mpfr_t x);
void floacon_from_general(char *out, mpfr_t x);

#endif /* _FLOACON_CONVERTER_H__ */