#ifndef __FPCONVERTER_TYPES_H__
#define __FPCONVERTER_TYPES_H__

#include <mpfr.h>

typedef mpfr_t floacon_t;
typedef mpfr_exp_t floacon_exp_t;
typedef mpfr_prec_t floacon_prec_t;

typedef struct {
  char name[256];
  floacon_prec_t exponent;
  floacon_prec_t precision;
} floacon_format_t;

typedef enum {
  BINARY16,
  BINARY32,
  BINARY64,
  BINARY128,
  BINARY256,
  BFLOAT16,
  TF32,
  __FLOACON_PREDEFINED_FORMATS_END__
} floacon_predefined_format;

int is_null_format(const floacon_format_t fmt);
floacon_format_t
floacon_get_predefined_format(const floacon_predefined_format fmt);
floacon_format_t floacon_get_predefined_format_from_string(const char *fmt);

#endif /* __FPCONVERTER_TYPES_H__ */
