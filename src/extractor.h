#ifndef __FLOACON_EXTRACTOR_H__
#define __FLOACON_EXTRACTOR_H__

#include <mpfr.h>

#include "types.h"

floacon_exp_t floacon_get_exponent(floacon_t x);
void floacon_get_significand(floacon_t x, floacon_t significand);
floacon_exp_t floacon_get_max_exponent(floacon_t x);
floacon_exp_t floacon_get_min_exponent(floacon_t x);
void floacon_get_next(floacon_t x, floacon_t next);
void floacon_get_previous(floacon_t x, floacon_t previous);

#endif /* _FLOACON_EXTRACTOR_H_ */