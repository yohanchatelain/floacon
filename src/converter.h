#ifndef _FPCONVERTER_CONVERTER_H__
#define _FPCONVERTER_CONVERTER_H__

#include <mpfr.h>

#include "types.h"

void fpconvert_set_exponent(format_t fmt);
void fpconvert_set_precision(format_t fmt);
void fpconvert_set_context(format_t fmt);
void fpconvert_convert(const char *input, int *base_ptr, format_t source_fmt,
                       format_t target_fmt, mpfr_rnd_t rnd, mpfr_t x);

void print_usage();
void check_args(int argc, char *argv[]);

void get_float(char *out, mpfr_t x);
void get_binary(char *out, mpfr_t x);
void get_hex(char *out, mpfr_t x);
void get_scientific(char *out, mpfr_t x);
void get_general(char *out, mpfr_t x);

#endif /* _FPCONVERTER_CONVERTER_H__ */