#include <assert.h>
#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void __sprintf(char *buffer, char *fmt, mpfr_t x) {
  mpfr_sprintf(buffer, fmt, x);
}

void get_float(char *out, mpfr_t x) { __sprintf(out, "%Rf\n", x); }
void get_binary(char *out, mpfr_t x) { __sprintf(out, "%Rb\n", x); }
void get_hex(char *out, mpfr_t x) { __sprintf(out, "%Ra\n", x); }
void get_scientific(char *out, mpfr_t x) { __sprintf(out, "%Re\n", x); }
void get_general(char *out, mpfr_t x) { __sprintf(out, "%Rg\n", x); }

void fpconvert_set_exponent(format_t fmt) {
  mpfr_exp_t emax = 1 << (fmt.exponent - 1);
  mpfr_exp_t emin = -(1 << (fmt.exponent - 1)) - fmt.precision + 4;
  assert(emin < emax);
  mpfr_set_emax(emax);
  mpfr_set_emin(emin);
}

void fpconvert_set_precision(format_t fmt) {
  mpf_set_default_prec(fmt.precision);
}

void fpconvert_set_context(format_t fmt) {
  fpconvert_set_precision(fmt);
  fpconvert_set_exponent(fmt);
}

void fpconvert_convert(const char *input, int *base_ptr, format_t source_fmt,
                       format_t target_fmt, mpfr_rnd_t rnd, mpfr_t x) {
  int base = (base_ptr == NULL) ? 0 : *base_ptr;
  fpconvert_set_context(source_fmt);
  mpfr_init2(x, source_fmt.precision);
  mpfr_strtofr(x, input, NULL, base, rnd);

  fpconvert_set_context(target_fmt);
  int t = mpfr_add_ui(x, x, 0, rnd);
  t = mpfr_check_range(x, t, rnd);
  mpfr_subnormalize(x, t, rnd);
}
