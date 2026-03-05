#ifndef E_DEBUG_H
#define E_DEBUG_H


#ifndef NDEBUG 
#define ASSERT(x) if (!(x)) __builtin_debugtrap()
#define GL(x) debug_clear_errors(); x; debug_halt_on_error(__FILE__, __LINE__);
#else
#define GL(x) x
#define ASSERT(x)
#endif

void debug_clear_errors(void);
void debug_halt_on_error(const char *file, int line);

#endif
