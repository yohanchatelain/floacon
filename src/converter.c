#include <assert.h>
#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "printer.h"
#include "types.h"

void __sprintf(char *buffer, char *fmt, floacon_t x) {
  mpfr_sprintf(buffer, fmt, x);
}

void floacon_from_float(char *out, floacon_t x) { __sprintf(out, "%Rf\n", x); }
void floacon_from_binary(char *out, floacon_t x) { __sprintf(out, "%Rb\n", x); }
void floacon_from_hex(char *out, floacon_t x) { __sprintf(out, "%Ra\n", x); }
void floacon_from_scientific(char *out, floacon_t x) {
  __sprintf(out, "%Re\n", x);
}
void floacon_from_general(char *out, floacon_t x) {
  __sprintf(out, "%Rg\n", x);
}

void floacon_set_exponent(floacon_format_t fmt) {
  mpfr_exp_t emax = 1 << (fmt.exponent - 1);
  mpfr_exp_t emin = -(1 << (fmt.exponent - 1)) - fmt.precision + 4;
  assert(emin < emax);
  mpfr_set_emax(emax);
  mpfr_set_emin(emin);
}

void floacon_set_precision(floacon_format_t fmt) {
  mpf_set_default_prec(fmt.precision);
}

void floacon_set_context(floacon_format_t fmt) {
  floacon_set_precision(fmt);
  floacon_set_exponent(fmt);
}

void floacon_convert(const char *input, int *base_ptr,
                     floacon_format_t source_fmt, floacon_format_t target_fmt,
                     mpfr_rnd_t rnd, floacon_t x) {
  int base = (base_ptr == NULL) ? 0 : *base_ptr;
  floacon_set_context(source_fmt);
  mpfr_init2(x, source_fmt.precision);
  mpfr_strtofr(x, input, NULL, base, rnd);

  floacon_set_context(target_fmt);
  int t = mpfr_prec_round(x, target_fmt.precision, rnd);
  t = mpfr_check_range(x, t, rnd);
  mpfr_subnormalize(x, t, rnd);
}
