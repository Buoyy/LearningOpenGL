#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H

#define VEC1(TYPE, NAME)\
typedef struct { TYPE x; } NAME;\

#define VEC2(TYPE, NAME)\
typedef struct { TYPE x, y; } NAME;\

#define VEC3(TYPE, NAME)\
typedef struct { TYPE x, y, z; } NAME;\

#define VEC4(TYPE, NAME)\
typedef struct { TYPE x, y, z, w; } NAME;\

VEC2(float, vec2)
VEC3(unsigned char, bytevec3)


#endif

