
#include <mpfr.h>

#include "extractor.h"
#include "types.h"

floacon_exp_t floacon_get_exponent(floacon_t x) { return mpfr_get_exp(x); }

void floacon_get_significand(floacon_t x, floacon_t significand) {
  floacon_exp_t e;
  mpfr_frexp(&e, significand, x, MPFR_RNDN);
}

floacon_exp_t floacon_get_max_exponent(floacon_t x) { return mpfr_get_emax(); }

floacon_exp_t floacon_get_min_exponent(floacon_t x) { return mpfr_get_emin(); }

void floacon_get_next(floacon_t x, floacon_t next) {
  mpfr_set(next, x, MPFR_RNDN);
  mpfr_nextabove(next);
}

void floacon_get_previous(floacon_t x, floacon_t previous) {
  mpfr_set(previous, x, MPFR_RNDN);
  mpfr_nextbelow(previous);
}
