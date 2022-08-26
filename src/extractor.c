
#include <mpfr.h>

#include "types.h"

mpfr_exp_t get_exponent(mpfr_t x) { return mpfr_get_exp(x); }

void get_significand(mpfr_t x, mpfr_t significand) {
  mpfr_exp_t e;
  mpfr_frexp(&e, significand, x, MPFR_RNDN);
}

mpfr_exp_t get_max_exponent(mpfr_t x) { return mpfr_get_emax(); }

mpfr_exp_t get_min_exponent(mpfr_t x) { return mpfr_get_emin(); }

void get_next(mpfr_t x, mpfr_t next) {
  mpfr_set(next, x, MPFR_RNDN);
  mpfr_nextabove(next);
}

void get_previous(mpfr_t x, mpfr_t previous) {
  mpfr_set(previous, x, MPFR_RNDN);
  mpfr_nextbelow(previous);
}
