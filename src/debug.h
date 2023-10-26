#ifndef __FLOACON_DEBUG_H__
#define __FLOACON_DEBUG_H__

#ifndef DEBUG
#define _DEBUG 0
#else
#define _DEBUG 1
#endif

#define debug_print(fmt, ...)                                                  \
  do {                                                                         \
    if (_DEBUG)                                                                \
      fprintf(stderr, fmt, ##__VA_ARGS__);                                     \
  } while (0)

#define debug_print_sep() debug_print("================================\n")

#endif // __FLOACON_DEBUG_H__