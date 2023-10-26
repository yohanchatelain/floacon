#include <string.h>

#include "logger.h"
#include "types.h"

/* Predefined formats */
/* Null format */
static const floacon_format_t null_format = {
    .name = "null", .exponent = 0, .precision = 0};
/* IEEE-754 formats */
static const floacon_format_t binary16_format = {
    .name = "binary16", .exponent = 5, .precision = 11};
static const floacon_format_t binary32_format = {
    .name = "binary32", .exponent = 8, .precision = 24};
static const floacon_format_t binary64_format = {
    .name = "binary64", .exponent = 11, .precision = 53};
static const floacon_format_t binary128_format = {
    .name = "binary128", .exponent = 15, .precision = 113};
static const floacon_format_t binary256_format = {
    .name = "binary256", .exponent = 19, .precision = 237};
/* Google formats */
static const floacon_format_t bfloat16_format = {
    .name = "bfloat16", .exponent = 8, .precision = 8};
/* Nvidia formats */
static const floacon_format_t tf32_format = {
    .name = "TF32", .exponent = 6, .precision = 11};

int is_null_format(const floacon_format_t fmt) {
  if (strcmp(fmt.name, null_format.name) == 0) {
    return 1;
  } else {
    return 0;
  }
}

floacon_format_t
floacon_get_predefined_format(const floacon_predefined_format fmt) {
  switch (fmt) {
  case BINARY16:
    return binary16_format;
  case BINARY32:
    return binary32_format;
  case BINARY64:
    return binary64_format;
  case BINARY128:
    return binary128_format;
  case BINARY256:
    return binary256_format;
  case BFLOAT16:
    return bfloat16_format;
  case TF32:
    return tf32_format;
  default:
    return null_format;
  }
}

floacon_format_t floacon_get_predefined_format_from_string(const char *fmt) {
  if (strcasecmp(fmt, binary16_format.name) == 0) {
    return binary16_format;
  } else if (strcasecmp(fmt, binary32_format.name) == 0) {
    return binary32_format;
  } else if (strcasecmp(fmt, binary64_format.name) == 0) {
    return binary64_format;
  } else if (strcasecmp(fmt, binary128_format.name) == 0) {
    return binary128_format;
  } else if (strcasecmp(fmt, binary256_format.name) == 0) {
    return binary256_format;
  } else if (strcasecmp(fmt, bfloat16_format.name) == 0) {
    return bfloat16_format;
  } else if (strcasecmp(fmt, tf32_format.name) == 0) {
    return tf32_format;
  } else {
    return null_format;
  }
}