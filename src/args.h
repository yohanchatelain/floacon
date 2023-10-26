#ifndef __FLOACON_ARGS_H__
#define __FLOACON_ARGS_H__

typedef struct {
  char input_value[512];
  int input_precision;
  int input_exponent;
  int output_precision;
  int output_exponent;
} floacon_argp_state_t;

void print_argp_state(floacon_argp_state_t *state);
void parse_args(int argc, char *argv[], floacon_argp_state_t *state);

#endif // __FLOACON_ARGS_H__