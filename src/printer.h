#ifndef __FPCONVERTER_PRINTER_H__
#define __FPCONVERTER_PRINTER_H__

#include <mpfr.h>


void print_float(mpfr_t x);
void print_binary(mpfr_t x);
void print_hex(mpfr_t x);
void print_scientific(mpfr_t x);
void print_general(mpfr_t x);

#endif /* _FPCONVERTER_PRINTER_H_ */