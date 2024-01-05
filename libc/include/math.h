#ifndef SAYORISDK_MATH_H
#define SAYORISDK_MATH_H

#define ABS(a) ((a) >= 0 ? (a) : -(a))

#define MIN(a, b) \
({ __typeof__ (a) _a = (a); \
   __typeof__ (b) _b = (b); \
   _a < _b ? _a : _b; })

#define MAX(a, b) \
({ __typeof__ (a) _a = (a); \
   __typeof__ (b) _b = (b); \
   _a > _b ? _a : _b; })


static inline double floor(double x) {
    int intPart = (int)x;

    return intPart - (x < 0 && x != intPart);
}

static inline double ceil(double x) {
    int intPart = (int)x;

    return intPart + (x > 0 && x != intPart);
}

static inline double fabs(double x) {
    return (x < 0) ? -x : x;
}

#define PI 3.141592653589793

#define ASIN_STEPS 6000
#define ATAN_STEPS 6000


#endif //SAYORISDK_MATH_H
