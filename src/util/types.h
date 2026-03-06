#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H

#define true 1
#define false 0

#define VEC1(TYPE, NAME)\
typedef struct { TYPE x; } NAME;\

#define VEC2(TYPE, NAME)\
typedef struct { TYPE x, y; } NAME;\

#define VEC3(TYPE, NAME)\
typedef struct { TYPE x, y, z; } NAME;\

#define VEC4(TYPE, NAME)\
typedef struct { TYPE x, y, z, w; } NAME;\

typedef unsigned int uint;
typedef unsigned char byte;
typedef byte boolean;

VEC3(byte, solid_color)

#endif

