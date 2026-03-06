#ifndef E_DEBUG_H
#define E_DEBUG_H

#include <cglm/cglm.h>
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

#define ERR_ASSERT(X)\
    fprintf(stderr, "ASSERT::FAIL(%s)\n", #X);\
    fprintf(stderr, "FILE::%s\n\n", __FILE__);\
    fprintf(stderr, "FUNC::%s, LINE::%d\n", __func__, __LINE__);\

#define ASSERT(X) if (!(X))\
{\
    ERR_ASSERT(X);\
    BREAKPOINT();\
}\

#define ASSERTM(X, FMT, ...) if (!(X))\
{\
    ERR_ASSERT(X);\
    fprintf(stderr, "\n" FMT "\n", ##__VA_ARGS__);\
    BREAKPOINT();\
}

#define GL(X) debug_clear_errors(); X; debug_halt_on_error(__FILE__, __LINE__);
#else
#define GL(X) X 
#define ASSERT(X)
#define ASSERTM(X)
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

#define DECL_PRINT_GLM_VEC(N)\
void print_vec##N(vec##N vec, const char *name);\

#define DECL_PRINT_GLM_IVEC(N)\
void print_ivec##N(vec##N vec, const char *name);\

#define DEF_PRINT_GLM_VEC(N)\
void print_vec##N(vec##N vec, const char *name)\
{\
    printf("%s ", name);\
    glm_vec##N##_print(vec, stdout);\
}\

#define DEF_PRINT_GLM_IVEC(N)\
void print_ivec##N(vec##N vec, const char *name)\
{\
    printf("%s ", name);\
    glm_ivec##N##_print(vec, stdout);\
}\

void debug_clear_errors(void);
void debug_halt_on_error(const char *file, int line);

DECL_PRINT_GLM_VEC(2)
DECL_PRINT_GLM_VEC(3)
DECL_PRINT_GLM_VEC(4)
DECL_PRINT_MAT_SQ(4)

#endif
