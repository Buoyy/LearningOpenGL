#ifndef E_DEBUG_H
#define E_DEBUG_H

#include <cglm/cglm.h>
#include <util/types.h>
#include <stdio.h>

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

#define ASSERTM(X, ...) assertm_impl(X, __FILE__, __LINE__, __VA_ARGS__)
#define ASSERT(X) assert_impl(X, __FILE__, __LINE__)

#define GL(X) debug_clear_errors(); X; debug_halt_on_error(__FILE__, __LINE__);

#else
#define GL(X) X 
#define ASSERTM(X, ...)
#define ASSERT(X)
#endif

#define DECL_PRINT_MAT_SQ(N)\
void print_mat##N(mat##N mat, const char *name);\

#define DEF_PRINT_MAT_SQ(N)\
void print_mat##N(mat##N mat, const char *name)\
{\
    printf("%s ", name);\
    glm_mat##N##_print(mat, stdout);\
}\

// ---------------------------------------------

void assert_impl(boolean condition, const char *file, int line);
void assertm_impl(boolean condition, const char *file, int line, const char *fmt, ...);

void debug_clear_errors(void);
void debug_halt_on_error(const char *file, int line);

#endif
