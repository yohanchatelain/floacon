#include <argp.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "debug.h"
#include "types.h"

const char *argp_program_version = "0.0.1";
const char *argp_program_bug_address = "<yohan.chatelain@gmail.com>";

typedef enum {
  KEY_INPUT_VALUE,
  KEY_INPUT_PRECISION,
  KEY_INPUT_EXPONENT,
  KEY_OUTPUT_PRECISION,
  KEY_OUTPUT_EXPONENT,
  KEY_ROUNDING_MODE,
  KEY_OUTPUT_FORMAT,
  KEY_INPUT_FORMAT,
  __END_KEY_ARG__
} floacon_arg_key_t;

static const char key_input_value[] = "input-value";
static const char key_input_precision[] = "input-precision";
static const char key_input_exponent[] = "input-exponent";
static const char key_input_format[] = "input-format";
static const char key_output_precision[] = "output-precision";
static const char key_output_exponent[] = "output-exponent";
static const char key_output_format[] = "output-format";

static const char *keys_name[] = {
    [KEY_INPUT_VALUE] = key_input_value,
    [KEY_INPUT_PRECISION] = key_input_precision,
    [KEY_INPUT_EXPONENT] = key_input_exponent,
    [KEY_INPUT_FORMAT] = key_input_format,
    [KEY_OUTPUT_PRECISION] = key_output_precision,
    [KEY_OUTPUT_EXPONENT] = key_output_exponent,
    [KEY_OUTPUT_FORMAT] = key_output_format,
};

void init_argp_state(floacon_argp_state_t *state) {
  state->input_value[0] = '\0';
  state->input_precision = 0;
  state->input_exponent = 0;
  state->output_precision = 0;
  state->output_exponent = 0;
}

void print_argp_state(floacon_argp_state_t *state) {
  debug_print_sep();
  debug_print("argp-state:\n");
  debug_print("\t.input-value: %s\n", state->input_value);
  debug_print("\t.input-precision: %d\n", state->input_precision);
  debug_print("\t.input-exponent: %d\n", state->input_exponent);
  debug_print("\t.output-precision: %d\n", state->output_precision);
  debug_print("\t.output-exponent: %d\n", state->output_exponent);
}

void check_argp_state(struct argp_state *state) {
  floacon_argp_state_t *argp_state = (floacon_argp_state_t *)state->input;
  if (argp_state->input_precision <= 0) {
    argp_error(state, "Invalid input precision: %d",
               argp_state->input_precision);
  }
  if (argp_state->input_exponent <= 0) {
    argp_error(state, "Invalid input exponent: %d", argp_state->input_exponent);
  }
  if (argp_state->output_precision == 0) {
    argp_error(state, "Invalid output precision: %d",
               argp_state->output_precision);
  }
  if (argp_state->output_exponent == 0) {
    argp_error(state, "Invalid output exponent: %d",
               argp_state->output_exponent);
  }
}

static struct argp_option options[] = {
    {key_input_value, KEY_INPUT_VALUE, "VALUE", 0, "input value", 0},
    {key_input_precision, KEY_INPUT_PRECISION, "PRECISION", 0,
     "select input precision size", 0},
    {key_input_exponent, KEY_INPUT_EXPONENT, "EXPONENT", 0,
     "select input precision size", 0},
    {key_input_format, KEY_INPUT_FORMAT, "FORMAT", 0,
     "select input format among: binary16, binary32, binary64, binary128, "
     "binary256, bfloat16, TF32",
     0},
    {key_output_precision, KEY_OUTPUT_PRECISION, "PRECISION", 0,
     "select output precision size", 0},
    {key_output_exponent, KEY_OUTPUT_EXPONENT, "EXPONENT", 0,
     "select output exponent size", 0},
    {key_output_format, KEY_OUTPUT_FORMAT, "FORMAT", 0,
     "select output format among: binary16, binary32, binary64, binary128, "
     "binary256, bfloat16, TF32",
     0},
    {0}};

void debug_argparse_state(int key, char *arg, struct argp_state *state) {
  debug_print_sep();
  debug_print("key: %d\n", key);
  debug_print("\tProgram name: %s\n", state->name);
  if (key < __END_KEY_ARG__) {
    debug_print("\tkey-name: %s\n", keys_name[key]);
  } else {
    debug_print("\tkey-name: %s\n", "unknown");
  }
  debug_print("\targ: %s\n", arg);
  debug_print("\targ-num: %d\n", state->arg_num);
  debug_print("\tnext: %d\n", state->next);
  debug_print("\tnext-arg: %s\n", state->argv[state->next]);
}

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  floacon_argp_state_t *argp_state = (floacon_argp_state_t *)state->input;
  int val = -1;
  floacon_format_t fmt;
  char *endptr;
  switch (key) {
  case KEY_INPUT_VALUE:
    // small check
    if (arg == NULL || strlen(arg) == 0 || arg[0] == '\0') {
      argp_error(state, "Invalid input value: %s", arg);
    }
    strncpy(argp_state->input_value, arg, 512);
    debug_argparse_state(key, arg, state);
    break;
  case KEY_INPUT_PRECISION:
    val = strtol(arg, &endptr, 10);
    if (errno != 0 || val <= 0) {
      argp_error(state, "Invalid input precision: %s", arg);
    }
    argp_state->input_precision = val;
    debug_argparse_state(key, arg, state);
    break;
  case KEY_INPUT_EXPONENT:
    val = strtol(arg, &endptr, 10);
    if (errno != 0 || val <= 0) {
      argp_error(state, "Invalid input exponent: %s", arg);
    }
    argp_state->input_exponent = val;
    debug_argparse_state(key, arg, state);
    break;
  case KEY_INPUT_FORMAT:
    fmt = floacon_get_predefined_format_from_string(arg);
    if (is_null_format(fmt)) {
      argp_error(state, "Invalid input format: %s", arg);
    }
    argp_state->input_precision = fmt.precision;
    argp_state->input_exponent = fmt.exponent;
    debug_argparse_state(key, arg, state);
    break;
  case KEY_OUTPUT_PRECISION:
    val = strtol(arg, &endptr, 10);
    if (errno != 0 || val <= 0) {
      argp_error(state, "Invalid output precision: %s", arg);
    }
    argp_state->output_precision = val;
    debug_argparse_state(key, arg, state);
    break;
  case KEY_OUTPUT_EXPONENT:
    val = strtol(arg, &endptr, 10);
    if (errno != 0 || val <= 0) {
      argp_error(state, "Invalid output exponent: %s", arg);
    }
    argp_state->output_exponent = val;
    debug_argparse_state(key, arg, state);
    break;
  case KEY_OUTPUT_FORMAT:
    fmt = floacon_get_predefined_format_from_string(arg);
    if (is_null_format(fmt)) {
      argp_error(state, "Invalid output format: %s", arg);
    }
    argp_state->output_precision = fmt.precision;
    argp_state->output_exponent = fmt.exponent;
    debug_argparse_state(key, arg, state);
    break;
  case ARGP_KEY_END:
    debug_argparse_state(key, arg, state);
    check_argp_state(state);
    break;
  default:
    debug_argparse_state(key, arg, state);
    return ARGP_ERR_UNKNOWN;
  }
  return ARGP_KEY_ARG;
}

static struct argp argp = {options, parse_opt, "", "", 0, 0, 0};

void parse_args(int argc, char *argv[], floacon_argp_state_t *state) {
  init_argp_state(state);
  argp_parse(&argp, argc, argv, 0, 0, state);
}