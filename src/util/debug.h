#ifndef E_DEBUG_H
#define E_DEBUG_H

#ifndef NDEBUG

#if defined(__GNUC__) && !defined(__clang__)
#define BREAKPOINT() __builtin_trap()
#endif 

#if defined(__clang__)
#define BREAKPOINT() __builtin_debugtrap()
#endif

#ifdef _MSC_VER
#define BREAKPOINT() __debugbreak()
#endif

#define ASSERT(x) if (!(x)) BREAKPOINT()
#define GL(x) debug_clear_errors(); x; debug_halt_on_error(__FILE__, __LINE__);
#else
#define GL(x) x
#define ASSERT(x)
#endif

void debug_clear_errors(void);
void debug_halt_on_error(const char *file, int line);
void breakpoint(void);

#endif
