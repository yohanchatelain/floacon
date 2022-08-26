#ifndef __FPCONVERTER_TYPES_H__
#define __FPCONVERTER_TYPES_H__

#include <mpfr.h>

typedef struct {
  mpfr_prec_t precision;
  mpfr_prec_t exponent;
} format_t;

#endif /* __FPCONVERTER_TYPES_H__ */
