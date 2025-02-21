#ifndef _MAZE_LINMATH_H_
#define _MAZE_LINMATH_H_

#define PI 3.141592653589793

#include <math.h>

// #define MATH_DOUBLE_PRECISION

#ifdef MATH_DOUBLE_PRECISION
#define MATH_EPSILON __DBL_EPSILON__
    typedef double     m_float;
    #define acos       m_acos
    #define asin       m_asin
    #define atan       m_atan
    #define atan2      m_atan2
    #define cos        m_cos
    #define sin        m_sin
    #define tan        m_tan
    #define acosh      m_acosh
    #define asinh      m_asinh
    #define atanh      m_atanh
    #define cosh       m_cosh
    #define sinh       m_sinh
    #define tanh       m_tanh
    #define exp        m_exp
    #define exp2       m_exp2
    #define expm1      m_expm1
    #define log        m_log
    #define log10      m_log10
    #define log2       m_log2
    #define log1p      m_log1p
    #define logb       m_logb
    #define modf       m_modf
    #define ldexp      m_ldexp
    #define frexp      m_frexp
    #define scalbn     m_scalbn
    #define scalbln    m_scalbln
    #define fabs       m_fabs
    #define cbrt       m_cbrt
    #define hypot      m_hypot
    #define pow        m_pow
    #define sqrt       m_sqrt
    #define erf        m_erf
    #define erfc       m_erfc
    #define lgamma     m_lgamma
    #define tgamma     m_tgamma
    #define ceil       m_ceil
    #define floor      m_floor
    #define nearbyint  m_nearbyint
    #define rint       m_rint
    #define round      m_round
    #define trunc      m_trunc
    #define fmod       m_fmod
    #define remainder  m_remainder
    #define remquo     m_remquo
    #define copysign   m_copysign
    #define nan        m_nan
    #define fdim       m_fdim
    #define fmax       m_fmax
    #define fmin       m_fmin
#else
#define MATH_EPSILON __FLT_EPSILON__
    typedef float       m_float;
    #define acosf       m_acos
    #define asinf       m_asin
    #define atanf       m_atan
    #define atan2f      m_atan2
    #define cosf        m_cos
    #define sinf        m_sin
    #define tanf        m_tan
    #define acoshf      m_acosh
    #define asinhf      m_asinh
    #define atanhf      m_atanh
    #define coshf       m_cosh
    #define sinhf       m_sinh
    #define tanhf       m_tanh
    #define expf        m_exp
    #define exp2f       m_exp2
    #define expm1f      m_expm1
    #define logf        m_log
    #define log10f      m_log10
    #define log2f       m_log2
    #define log1pf      m_log1p
    #define logbf       m_logb
    #define modff       m_modf
    #define ldexpf      m_ldexp
    #define frexpf      m_frexp
    #define scalbnf     m_scalbn
    #define scalblnf    m_scalbln
    #define fabsf       m_fabs
    #define cbrtf       m_cbrt
    #define hypotf      m_hypot
    #define powf        m_pow
    #define sqrtf       m_sqrt
    #define erff        m_erf
    #define erfcf       m_erfc
    #define lgammaf     m_lgamma
    #define tgammaf     m_tgamma
    #define ceilf       m_ceil
    #define floorf      m_floor
    #define nearbyintf  m_nearbyint
    #define rintf       m_rint
    #define roundf      m_round
    #define truncf      m_trunc
    #define fmodf       m_fmod
    #define remainderf  m_remainder
    #define remquof     m_remquo
    #define copysignf   m_copysign
    #define nanf        m_nan
    #define fdimf       m_fdim
    #define fmaxf       m_fmax
    #define fminf       m_fmin
#endif

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define CLAMP(x,a,b) MIN((b), MAX((a), (x)))
#define ABS(a) (((a) < 0) ? -(a) : (a))

typedef struct { m_float x, y, z; } vec3_t;

static inline vec3_t vec3(m_float x, m_float y, m_float z, m_float w)
{
    return (vec3_t) { x, y, z };
}

static inline void vec3_zero(vec3_t *v)
{
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

static inline void vec3_ones(vec3_t *v)
{
    v->x = 1;
    v->y = 1;
    v->z = 1;
}

static inline void vec3_add(vec3_t *a, const vec3_t *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}

static inline void vec3_sub(vec3_t *a, const vec3_t *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
}

static inline void vec3_mul(vec3_t *a, const vec3_t *b)
{
    a->x *= b->x;
    a->y *= b->y;
    a->z *= b->z;
}

static inline void vec3_div(vec3_t *a, const vec3_t *b)
{
    a->x /= b->x;
    a->y /= b->y;
    a->z /= b->z;
}

static inline m_float vec3_length2(const vec3_t *a)
{
    return (a->x * a->x)
         + (a->y * a->y)
         + (a->z * a->z);
}

static inline m_float vec3_length(const vec3_t *a)
{
    return m_sqrt(
           (a->x * a->x)
         + (a->y * a->y)
         + (a->z * a->z));
}

static inline m_float vec3_distance(const vec3_t *a, const vec3_t *b)
{
    ////// TODO:
}

static inline m_float vec3_dot(const vec3_t *a, const vec3_t *b)
{
    return (a->x * b->x)
         + (a->y * b->y)
         + (a->z * b->z);
}


static inline void vec3_cross(vec3_t *v, const vec3_t *a, const vec3_t *b)
{
    v->x = a->y * b->z - a->z * b->y;
    v->y = a->z * b->x - a->x * b->z;
    v->z = a->x * b->y - a->y * b->x;
}


static inline void vec3_normalize(vec3_t *a)
{
    m_float h = MAX(MATH_EPSILON, vec3_length(a));
    a->x /= h;
    a->y /= h;
    a->z /= h;
}

static inline void vec3_scale(vec3_t *a, m_float scale)
{
    a->x *= scale;
    a->y *= scale;
    a->z *= scale;
}

static inline void vec3_trim(vec3_t *a, m_float length)
{
    m_float h = MAX(MATH_EPSILON, vec3_length(a));

    a->x *= length / h;
    a->y *= length / h;
    a->z *= length / h;
}

static inline void vec3_lookat()
{
    ////// TODO:
}

#endif