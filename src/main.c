#include <stdio.h>
#include <stdlib.h>

#include "converter.h"
#include "extractor.h"
#include "printer.h"
#include "types.h"

void print_usage() {
  printf("fp-converter: <value> <input-precision> <input-exponent> "
         "<output-precision> <output-exponent>\n");
  exit(EXIT_FAILURE);
}

void check_args(int argc, char *argv[]) {
  if (argc != 6) {
    fprintf(stderr, "Invalid number of arguments: %d, expected 5\n", argc - 1);
    print_usage();
  }
}

int main(int argc, char *argv[]) {

  check_args(argc, argv);
  char *value = argv[1];
  int input_precision = atoi(argv[2]);
  int input_exponent = atoi(argv[3]);
  int output_precision = atoi(argv[4]);
  int output_exponent = atoi(argv[5]);

  format_t input_fmt = {.exponent = input_exponent,
                        .precision = input_precision};
  format_t output_fmt = {.exponent = output_exponent,
                         .precision = output_precision};

  mpfr_t x;
  fpconvert_convert(value, NULL, input_fmt, output_fmt, MPFR_RNDN, x);
  mpfr_printf("%Ra\n", x);

  return 0;
}
