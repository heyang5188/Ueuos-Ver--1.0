#ifndef _MATH_MACRO_H_
#define _MATH_MACRO_H_
#define M_PI 3.14159265358979323846

#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))
#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)

#define CLAMP(x , min , max) ((x) > (max) ? (max) : ((x) < (min) ? (min) : x))
//#define FLOAT_EQUAL(a,b,tolerance)

#endif