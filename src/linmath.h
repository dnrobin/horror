#ifndef __MAZE_GAME_MATH_H__
#define __MAZE_GAME_MATH_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// #define USE_DOUBLE_PRECISION

#define M_PRINT_FILE stdout

#ifdef USE_DOUBLE_PRECISION

    typedef double m_float;
    
    #define M_FLOAT_EPSILON     1e-7f
    #define M_VECTOR_EPSILON    M_FLOAT_EPSILON
    #define M_MATRIX_EPSILON    M_FLOAT_EPSILON

    #define m_abs               fabs
    #define m_min               fmin
    #define m_max               fmax
    #define m_round             round
    #define m_ceil              ceil
    #define m_floor             floor
    #define m_rem               remainder
    #define m_mod               modf
    #define m_pow               pow
    #define m_exp               exp
    #define m_log               log
    #define m_log2              log2
    #define m_log10             log10
    #define m_sqrt              sqrt
    #define m_sin               sin
    #define m_cos               cos
    #define m_tan               tan
    #define m_asin              asin
    #define m_acos              acos
    #define m_atan              atan
    #define m_atan2             atan2
    #define m_sinh              sinh
    #define m_cosh              cosh
    #define m_tanh              tanh
    #define m_asinh             asinh
    #define m_acosh             acosh
    #define m_atanh             atanh
    
#else

    typedef float m_float;

    #define M_FLOAT_EPSILON     1e-5f
    #define M_VECTOR_EPSILON    M_FLOAT_EPSILON
    #define M_MATRIX_EPSILON    M_FLOAT_EPSILON  

    #define m_abs               fabsf
    #define m_min               fminf
    #define m_max               fmaxf
    #define m_round             roundf
    #define m_ceil              ceilf
    #define m_floor             floorf
    #define m_rem               remainderf
    #define m_mod               modff
    #define m_pow               powf
    #define m_exp               expf
    #define m_log               logf
    #define m_log2              log2f
    #define m_log10             log10f
    #define m_sqrt              sqrtf
    #define m_sin               sinf
    #define m_cos               cosf
    #define m_tan               tanf
    #define m_asin              asinf
    #define m_acos              acosf
    #define m_atan              atanf
    #define m_atan2             atan2f
    #define m_sinh              sinhf
    #define m_cosh              coshf
    #define m_tanh              tanhf
    #define m_asinh             asinhf
    #define m_acosh             acoshf
    #define m_atanh             atanhf
#endif

#define M_INF               INFINITY
#define M_NAN               NAN

static const m_float M_DEG2RAD = 0.017453292519943295769236907684886127;
static const m_float M_RAD2DEG = 57.29577951308232087679815481410517033;

#define M_ABS(x) ((x) < 0 ? -(x) : (x))
#define M_MIN(x,y) ((x) < (y) ? (x) : (y))
#define M_MAX(x,y) ((x) > (y) ? (x) : (y))
#define M_CLAMP(x,a,b) M_MIN(M_MAX((x), (a)), (b))
#define M_WITHIN(x,a,b) ((x) >= (a) && (x) <= (b))

//-------------------------------------------------------------------------------------
// functions
//-------------------------------------------------------------------------------------

#define m_isnan             isnan
#define m_isinf             isinf

static inline m_float m_sgn(m_float x)
{
    return signbit(x) ? -1.0 : 1.0;
}

static inline m_float m_snap(m_float x, m_float f)
{
    return m_sgn(x) * m_round(m_abs(x) / f) * f;
}

static inline bool m_clamp(m_float x, m_float a, m_float b)
{
    return m_min(m_max(x, a), b);
}

static inline bool m_within(m_float x, m_float a, m_float b)
{
    return x >= a && x <=b;
}

static inline m_float m_wrap(m_float x)
{
    // TODO: troubleshoot remainderf() outputs unexpected values!
    return m_rem(x, 2*M_PI) * 2*M_PI;
}

static inline void m_srand(int seed)
{
    srand(seed);
}

static inline m_float m_rand()
{
    return (rand() % 10000) / 10000.0;
}

static inline m_float m_rand_btw(m_float a, m_float b)
{
    return a + (b - a) * m_rand();
}

//-------------------------------------------------------------------------------------
// Vector 2 int
//-------------------------------------------------------------------------------------

typedef int vec2i_t[2];
static const vec2i_t VEC2i_ZEROS = { 0, 0 };
static const vec2i_t VEC2i_ONES  = { 1, 1 };

static inline void vec2i(int *v, int x, int y)
{
    v[0] = x;
    v[1] = y;
}
static inline void vec2i_clear(int *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
}
static inline void vec2i_copy(int *out, const int *v)
{
    out[0] = v[0];
    out[1] = v[1];
}
static inline void vec2i_add(int *out, const int *a, const int *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}
static inline void vec2i_sub(int *out, const int *a, const int *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}
static inline void vec2i_print(const int *v)
{
    fprintf(M_PRINT_FILE, "vec2i { ");
    for (int i = 0; i < 2; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%i", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}

//-------------------------------------------------------------------------------------
// Vector 2
//-------------------------------------------------------------------------------------

typedef m_float vec2_t[2];
static const vec2_t VEC2_ZEROS = { 0.0, 0.0 };
static const vec2_t VEC2_ONES  = { 1.0, 1.0 };
static const vec2_t VEC2_X     = { 1.0, 0.0 };
static const vec2_t VEC2_Y     = { 0.0, 1.0 };

static inline void vec2(m_float *v, m_float x, m_float y)
{
    v[0] = x;
    v[1] = y;
}
static inline void vec2_clear(m_float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
}
static inline void vec2_copy(m_float *out, const m_float *v)
{
    out[0] = v[0];
    out[1] = v[1];
}
static inline void vec2_add(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}
static inline void vec2_sub(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}
static inline void vec2_mul(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}
static inline void vec2_div(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
}
static inline void vec2_mul_f(m_float *out, const m_float *v, m_float f)
{
    out[0] = v[0] * f;
    out[1] = v[1] * f;
}
static inline void vec2_div_f(m_float *out, const m_float *v, m_float f)
{
    out[0] = v[0] / f;
    out[1] = v[1] / f;
}
static inline void vec2_flip(m_float *out, const m_float *v)
{
    out[0] = -v[0];
    out[1] = -v[1];
}
static inline void vec2_mirror_x(m_float *out, const m_float *v)
{
    out[0] = -v[0];
    out[1] = +v[1];
}
static inline void vec2_mirror_y(m_float *out, const m_float *v)
{
    out[0] = +v[0];
    out[1] = -v[1];
}
static inline m_float vec2_dot(const m_float *a, const m_float *b)
{
    return a[0]*b[0] + a[1]*b[1];
}
static inline m_float vec2_length2(const m_float *v)
{
    m_float l = vec2_dot(v, v);
    if (l < M_FLOAT_EPSILON) {
        l = M_FLOAT_EPSILON;
    }
    return l;
}
static inline m_float vec2_length(const m_float *v)
{
    m_float l = m_sqrt(vec2_dot(v, v));
    if (l < M_FLOAT_EPSILON) {
        l = M_FLOAT_EPSILON;
    }
    return l;
}
static inline void vec2_normalize(m_float *out, const m_float *v)
{
    vec2_mul_f(out, v, 1.0 / vec2_length(v));
}
static inline void vec2_trim(m_float *out, const m_float *v, m_float length)
{
    vec2_mul_f(out, v, length / vec2_length(v));
}
static inline void vec2_round(m_float *out, const m_float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
}
static inline void vec2_snap(m_float *out, const m_float *v, m_float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
}
static inline void vec2_lerp(m_float *out, const m_float *a, const m_float *b, m_float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
}
static inline void vec2_scale(m_float *out, const m_float *v, m_float scale)
{
    vec2_mul_f(out, v, scale);
}
static inline void vec2_rotate(m_float *out, const m_float *v, m_float angle)
{
    out[0] = v[0]*m_cos(angle);
    out[1] = v[1]*m_sin(angle);
}
static inline void vec2_rotate_about_point(m_float *out, const m_float *v, const m_float *point)
{
    // TODO:
}
static inline void vec2_project_vec2(m_float *out, const m_float *v, const m_float *u)
{
    vec2_t b;
    vec2_normalize(b, u);
    m_float h = vec2_dot(v, b);

    out[0] = h * b[0];
    out[1] = h * b[1];
}
static inline void vec2_reflect_vec2(m_float *out, const m_float *v, const m_float *u)
{
    vec2_t n;
    vec2_normalize(n, u);
    m_float h = vec2_dot(v, n);

    out[0] = v[0] - 2*h*n[0];
    out[1] = v[1] - 2*h*n[1];
}
static inline void vec2_print(const m_float *v)
{
    fprintf(M_PRINT_FILE, "vec2 { ");
    for (int i = 0; i < 2; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}

//-------------------------------------------------------------------------------------
// Vector 3
//-------------------------------------------------------------------------------------

typedef m_float vec3_t[3];
static const vec3_t VEC3_ZEROS = { 0.0, 0.0, 0.0 };
static const vec3_t VEC3_ONES  = { 1.0, 1.0, 1.0 };
static const vec3_t VEC3_X     = { 1.0, 0.0, 0.0 };
static const vec3_t VEC3_Y     = { 0.0, 1.0, 0.0 };
static const vec3_t VEC3_Z     = { 0.0, 0.0, 1.0 };
static const vec3_t VEC3_UP    = { 0.0, 1.0, 0.0 };

static inline void vec3(m_float *v, m_float x, m_float y, m_float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
static inline void vec3_clear(m_float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}
static inline void vec3_copy(m_float *out, const m_float *v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}
static inline void vec3_add(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}
static inline void vec3_sub(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
static inline void vec3_mul(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}
static inline void vec3_div(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
    out[2] = a[2] / b[2];
}
static inline void vec3_flip(m_float *out, const m_float *v)
{
    out[0] = -v[0];
    out[1] = -v[1];
    out[2] = -v[2];
}
static inline void vec3_mirror_x(m_float *out, const m_float *v)
{
    out[0] = -v[0];
    out[1] = +v[1];
    out[2] = +v[2];
}
static inline void vec3_mirror_y(m_float *out, const m_float *v)
{
    out[0] = +v[0];
    out[1] = -v[1];
    out[2] = +v[2];
}
static inline void vec3_mirror_z(m_float *out, const m_float *v)
{
    out[0] = +v[0];
    out[1] = +v[1];
    out[2] = -v[2];
}
static inline void vec3_mul_f(m_float *out, const m_float *v, m_float f)
{
    out[0] = v[0] * f;
    out[1] = v[1] * f;
    out[2] = v[2] * f;
}
static inline void vec3_div_f(m_float *out, const m_float *v, m_float f)
{
    out[0] = v[0] / f;
    out[1] = v[1] / f;
    out[2] = v[2] / f;
}
static inline void vec3_cross(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
static inline m_float vec3_dot(const m_float *a, const m_float *b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
static inline m_float vec3_length2(const m_float *v)
{
    m_float l = vec3_dot(v, v);
    if (l < M_FLOAT_EPSILON) {
        l = M_FLOAT_EPSILON;
    }
    return l;
}
static inline m_float vec3_length(const m_float *v)
{
    m_float l = m_sqrt(vec3_dot(v, v));
    if (l < M_FLOAT_EPSILON) {
        l = M_FLOAT_EPSILON;
    }
    return l;
}
static inline void vec3_normalize(m_float *out, const m_float *v)
{
    vec3_mul_f(out, v, 1.0 / vec3_length(v));
}
static inline void vec3_trim(m_float *out, const m_float *v, m_float length)
{
    vec3_mul_f(out, v, length / vec3_length(v));
}
static inline void vec3_round(m_float *out, const m_float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
    out[2] = m_round(v[2]);
}
static inline void vec3_snap(m_float *out, const m_float *v, m_float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
    out[2] = m_snap(v[2], prec);
}
static inline void vec3_lerp(m_float *out, const m_float *a, const m_float *b, m_float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
    out[2] = (1 - t)*a[2] + t*b[2];
}
static inline void vec3_scale(m_float *out, const m_float *v, m_float scale)
{
    vec3_mul_f(out, v, scale);
}
static inline void vec3_rotate_x(m_float *out, const m_float *v, m_float angle)
{
    m_float s = m_sin(angle);
    m_float c = m_cos(angle);
    out[0] = s*v[0];
    out[1] =   v[1];
    out[2] = c*v[2];
}
static inline void vec3_rotate_y(m_float *out, const m_float *v, m_float angle)
{
    m_float s = m_sin(angle);
    m_float c = m_cos(angle);
    out[0] =   v[0];
    out[1] = s*v[1];
    out[2] = c*v[2];
}
static inline void vec3_rotate_z(m_float *out, const m_float *v, m_float angle)
{
    m_float s = m_sin(angle);
    m_float c = m_cos(angle);
    out[0] = c*v[0];
    out[1] = s*v[1];
    out[2] =   v[2];
}
static inline void vec3_rotate(m_float *out, const m_float *v, m_float x, m_float y, m_float z)
{
    vec3_rotate_x(out, v, x);
    vec3_rotate_y(out, out, y);
    vec3_rotate_z(out, out, z);
}
static inline void vec3_rotate_about(m_float *out, const m_float *v, const m_float *axis, m_float angle)
{
    vec3_t u;

    vec3_cross(u, axis, v);

    m_float c = m_cos(angle);
    m_float s = m_sin(angle);
    m_float h = vec3_dot(axis, v) * (1 - c);
    
    // Rodrigues' formula: out = cos(t)*v + sin(t)*(k x v) + (1 - cos(t))*(k . v)*k
    out[0] = c*v[0] + s*u[0] + h*axis[0];
    out[1] = c*v[1] + s*u[1] + h*axis[1];
    out[2] = c*v[2] + s*u[2] + h*axis[2];
}
static inline void vec3_project_vec3(m_float *out, const m_float *v, const m_float *u)
{
    vec3_t b;
    vec3_normalize(b, u);
    m_float h = vec3_dot(v, b);

    out[0] = h * b[0];
    out[1] = h * b[1];
    out[2] = h * b[2];
}
static inline void vec3_reflect_vec3(m_float *out, const m_float *v, const m_float *u)
{
    vec3_t n;
    vec3_normalize(n, u);
    m_float h = vec3_dot(v, n);

    out[0] = v[0] - 2*h*n[0];
    out[1] = v[1] - 2*h*n[1];
    out[2] = v[2] - 2*h*n[2];
}
static inline void vec3_print(const m_float *v)
{
    fprintf(M_PRINT_FILE, "vec3 { ");
    for (int i = 0; i < 3; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, " }\n");
}

//-------------------------------------------------------------------------------------
// Vector 4
//-------------------------------------------------------------------------------------

typedef m_float vec4_t[4];
static const vec4_t VEC4_ZEROS = { 0.0, 0.0, 0.0, 0.0 };
static const vec4_t VEC4_ONES  = { 1.0, 1.0, 1.0, 1.0 };
static const vec4_t VEC4_X     = { 1.0, 0.0, 0.0, 0.0 };
static const vec4_t VEC4_Y     = { 0.0, 1.0, 0.0, 0.0 };
static const vec4_t VEC4_Z     = { 0.0, 0.0, 1.0, 0.0 };
static const vec4_t VEC4_W     = { 0.0, 0.0, 0.0, 1.0 };

static inline void vec4(m_float *v, m_float x, m_float y, m_float z, m_float w)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}
static inline void vec4_clear(m_float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
    v[3] = 0.0;
}
static inline void vec4_copy(m_float *out, const m_float *v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
}
static inline void vec4_add(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}
static inline void vec4_sub(m_float *out, const m_float *a, const m_float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}
static inline void vec4_lerp(m_float *out, const m_float *a, const m_float *b, m_float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
    out[2] = (1 - t)*a[2] + t*b[2];
    out[3] = (1 - t)*a[3] + t*b[3];
}
static inline void vec4_round(m_float *out, const m_float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
    out[2] = m_round(v[2]);
    out[3] = m_round(v[3]);
}
static inline void vec4_snap(m_float *out, const m_float *v, m_float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
    out[2] = m_snap(v[2], prec);
    out[3] = m_snap(v[3], prec);
}
static inline void vec4_print(const m_float *v)
{
    fprintf(M_PRINT_FILE, "vec4 { ");
    for (int i = 0; i < 4; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}


//-------------------------------------------------------------------------------------
// Matrix 2
//-------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec2_t mat2_t[2];
static const mat2_t MAT2_ZEROS = { {0.0, 0.0}, {0.0, 0.0} };
static const mat2_t MAT2_ONES  = { {1.0, 1.0}, {1.0, 1.0} };
static const mat2_t MAT2_EYE   = { {1.0, 0.0}, {0.0, 1.0} };

static inline void mat2(vec2_t *m
    , m_float m11, m_float m12
    , m_float m21, m_float m22)
{
    m[0][0] = m11; m[1][0] = m12;
    m[0][1] = m21; m[1][1] = m22;
}
static inline void mat2_clear(vec2_t *m)
{
    m[0][0] = 0.0; m[1][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 0.0;
}
static inline void mat2_identity(vec2_t *m)
{
    m[0][0] = 1.0; m[1][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 1.0;
}
static inline m_float mat2_det(const vec2_t *m)
{
    return m_snap(m[0][0]*m[1][1] - m[1][0]*m[0][1], M_FLOAT_EPSILON);
}
static inline void mat2_inv(vec2_t *m, const vec2_t *a)
{
    m_float h = 1.0 / mat2_det(a);

    m[0][0] =  h*a[1][1]; m[1][0] = -h*a[1][0];
    m[0][1] = -h*a[0][1]; m[1][1] =  h*a[0][0];
}
static inline void mat2_mul_vec2(m_float *out, const vec2_t *m, const m_float *a)
{
    out[0] = a[0]*m[0][0] + a[1]*m[1][0];
    out[1] = a[0]*m[0][1] + a[1]*m[1][1];
}
static inline void mat2_mul_mat2(vec2_t *m, const vec2_t *a, const vec2_t *b)
{
    m[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1];
    m[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1];

    m[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1];
    m[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1];
}
static inline void mat2_print(const vec2_t *m)
{
    fprintf(M_PRINT_FILE, "mat2\n{\n");
    for (int i = 0; i < 2; ++i) {
        fprintf(M_PRINT_FILE,"  ");
        for (int j = 0; j < 2; ++j) {
            fprintf(M_PRINT_FILE, "%7.4f, ", m[j][i]);
        }
        fprintf(M_PRINT_FILE, "\n");
    }
    fprintf(M_PRINT_FILE, "}\n");
}

//-------------------------------------------------------------------------------------
// Matrix 3
//-------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec3_t mat3_t[3];
static const mat3_t MAT3_ZEROS = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };
static const mat3_t MAT3_ONES  = { {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0} };
static const mat3_t MAT3_EYE   = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };

static inline void mat3(vec3_t *m
    , m_float m11, m_float m12, m_float m13
    , m_float m21, m_float m22, m_float m23
    , m_float m31, m_float m32, m_float m33)
{
    m[0][0] = m11; m[1][0] = m12; m[2][0] = m13;
    m[0][1] = m21; m[1][1] = m22; m[2][1] = m23;
    m[0][2] = m31; m[1][2] = m32; m[2][2] = m33;
}
static inline void mat3_copy(vec3_t *m, const vec3_t *a)
{
    m[0][0] = a[0][0]; m[1][0] = a[1][0]; m[2][0] = a[2][0];
    m[0][1] = a[0][1]; m[1][1] = a[1][1]; m[2][1] = a[2][1];
    m[0][2] = a[0][2]; m[1][2] = a[1][2]; m[2][2] = a[2][2];
}
static inline void mat3_clear(vec3_t *m)
{
    m[0][0] = 0.0; m[1][0] = 0.0; m[2][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 0.0; m[2][1] = 0.0;
    m[0][2] = 0.0; m[1][2] = 0.0; m[2][2] = 0.0;
}
static inline void mat3_identity(vec3_t *m)
{
    m[0][0] = 1.0; m[1][0] = 0.0; m[2][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 1.0; m[2][1] = 0.0;
    m[0][2] = 0.0; m[1][2] = 0.0; m[2][2] = 1.0;
}
static inline void mat3_transpose(vec3_t *m, const vec3_t *a)
{
    m[0][0] = a[0][0]; m[1][0] = a[0][1]; m[2][0] = a[0][2];
    m[0][1] = a[1][0]; m[1][1] = a[1][1]; m[2][1] = a[1][2];
    m[0][2] = a[2][0]; m[1][2] = a[2][1]; m[2][2] = a[2][2];
}
static inline void mat3_transpose_i(vec3_t *m)
{
    mat3_t a;
    mat3_copy(a, m);
    
    m[0][0] = a[0][0]; m[1][0] = a[0][1]; m[2][0] = a[0][2];
    m[0][1] = a[1][0]; m[1][1] = a[1][1]; m[2][1] = a[1][2];
    m[0][2] = a[2][0]; m[1][2] = a[2][1]; m[2][2] = a[2][2];
}
static inline m_float mat3_det(const vec3_t *m)
{
    return m_snap(
          m[0][0]*m[1][1]*m[2][2] + m[1][0]*m[2][1]*m[0][2] + m[2][0]*m[0][1]*m[1][2]
        - m[2][0]*m[1][1]*m[0][2] - m[1][0]*m[0][1]*m[2][2] - m[0][0]*m[2][1]*m[1][2]
        , M_FLOAT_EPSILON);
}
static inline void mat3_inv(vec3_t *out, const vec3_t *mat)
{
    /* copied from cglm impl */
    m_float
        a = mat[0][0], b = mat[0][1], c = mat[0][2],
        d = mat[1][0], e = mat[1][1], f = mat[1][2],
        g = mat[2][0], h = mat[2][1], i = mat[2][2],

        c1  = e * i - f * h, c2 = d * i - g * f, c3 = d * h - g * e,

        idt = 1.0 / (a * c1 - b * c2 + c * c3), ndt = -idt;

    out[0][0] = idt * c1;
    out[0][1] = ndt * (b * i - h * c);
    out[0][2] = idt * (b * f - e * c);
    out[1][0] = ndt * c2;
    out[1][1] = idt * (a * i - g * c);
    out[1][2] = ndt * (a * f - d * c);
    out[2][0] = idt * c3;
    out[2][1] = ndt * (a * h - g * b);
    out[2][2] = idt * (a * e - d * b);
}
static inline void mat3_mul_vec3(m_float *out, const vec3_t *m, const m_float *a)
{
    out[0] = a[0]*m[0][0] + a[1]*m[1][0] + a[2]*m[2][0];
    out[1] = a[0]*m[0][1] + a[1]*m[1][1] + a[2]*m[2][1];
    out[2] = a[0]*m[0][2] + a[1]*m[1][2] + a[2]*m[2][2];
}
static inline void mat3_mul_mat3(vec3_t *m, const vec3_t *a, const vec3_t *b)
{
    m[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2];
    m[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2];
    m[2][0] = a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2];

    m[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2];
    m[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2];
    m[2][1] = a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2];

    m[0][2] = a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2];
    m[1][2] = a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2];
    m[2][2] = a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2];
}
static inline void mat3_print(const vec3_t *m)
{
    fprintf(M_PRINT_FILE, "mat3\n{\n");
    for (int i = 0; i < 3; ++i) {
        fprintf(M_PRINT_FILE,"  ");
        for (int j = 0; j < 3; ++j) {
            fprintf(M_PRINT_FILE, "%7.4f, ", m[j][i]);
        }
        fprintf(M_PRINT_FILE, "\n");
    }
    fprintf(M_PRINT_FILE, "}\n");
}

//-------------------------------------------------------------------------------------
// Matrix 4
//-------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec4_t mat4_t[4];
static const mat4_t MAT4_ZEROS = { {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0} };
static const mat4_t MAT4_ONES  = { {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0} };
static const mat4_t MAT4_EYE   = { {1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0} };

static inline void mat4(vec4_t *m
    , m_float m11, m_float m12, m_float m13, m_float m14
    , m_float m21, m_float m22, m_float m23, m_float m24
    , m_float m31, m_float m32, m_float m33, m_float m34
    , m_float m41, m_float m42, m_float m43, m_float m44)
{
    m[0][0] = m11; m[1][0] = m12; m[2][0] = m13; m[3][0] = m14;
    m[0][1] = m21; m[1][1] = m22; m[2][1] = m23; m[3][1] = m24;
    m[0][2] = m31; m[1][2] = m32; m[2][2] = m33; m[3][2] = m34;
    m[0][3] = m41; m[1][3] = m42; m[2][3] = m43; m[3][3] = m44;
}
static inline void mat4_copy(vec4_t *m, const vec4_t *a)
{
    m[0][0] = a[0][0]; m[1][0] = a[1][0]; m[2][0] = a[2][0]; m[3][0] = a[3][0];
    m[0][1] = a[0][1]; m[1][1] = a[1][1]; m[2][1] = a[2][1]; m[3][1] = a[3][1];
    m[0][2] = a[0][2]; m[1][2] = a[1][2]; m[2][2] = a[2][2]; m[3][2] = a[3][2];
    m[0][3] = a[0][3]; m[1][3] = a[1][3]; m[2][3] = a[2][3]; m[3][3] = a[3][3];
}
static inline void mat4_clear(vec4_t *m)
{
    m[0][0] = 0.0; m[1][0] = 0.0; m[2][0] = 0.0; m[3][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 0.0; m[2][1] = 0.0; m[3][1] = 0.0;
    m[0][2] = 0.0; m[1][2] = 0.0; m[2][2] = 0.0; m[3][2] = 0.0;
    m[0][3] = 0.0; m[1][3] = 0.0; m[2][3] = 0.0; m[3][3] = 0.0;
}
static inline void mat4_identity(vec4_t *m)
{
    m[0][0] = 1.0; m[1][0] = 0.0; m[2][0] = 0.0; m[3][0] = 0.0;
    m[0][1] = 0.0; m[1][1] = 1.0; m[2][1] = 0.0; m[3][1] = 0.0;
    m[0][2] = 0.0; m[1][2] = 0.0; m[2][2] = 1.0; m[3][2] = 0.0;
    m[0][3] = 0.0; m[1][3] = 0.0; m[2][3] = 0.0; m[3][3] = 1.0;
}
static inline void mat4_transpose(vec4_t *m, const vec4_t *a)
{
    m[0][0] = a[0][0]; m[1][0] = a[0][1]; m[2][0] = a[0][2]; m[3][0] = a[0][3];
    m[0][1] = a[1][0]; m[1][1] = a[1][1]; m[2][1] = a[1][2]; m[3][1] = a[1][3];
    m[0][2] = a[2][0]; m[1][2] = a[2][1]; m[2][2] = a[2][2]; m[3][2] = a[2][3];
    m[0][3] = a[3][0]; m[1][3] = a[3][1]; m[2][3] = a[3][2]; m[3][3] = a[3][3];
}
static inline void mat4_transpose_i(vec4_t *m)
{
    mat4_t a;
    mat4_copy(a, m);
    
    m[0][0] = a[0][0]; m[1][0] = a[0][1]; m[2][0] = a[0][2]; m[3][0] = a[0][3];
    m[0][1] = a[1][0]; m[1][1] = a[1][1]; m[2][1] = a[1][2]; m[3][1] = a[1][3];
    m[0][2] = a[2][0]; m[1][2] = a[2][1]; m[2][2] = a[2][2]; m[3][2] = a[2][3];
    m[0][3] = a[3][0]; m[1][3] = a[3][1]; m[2][3] = a[3][2]; m[3][3] = a[3][3];
}
static inline m_float mat4_det(const vec4_t *m)
{
    return m_snap(
          m[0][0]*m[1][1]*m[2][2]*m[3][3] + m[1][0]*m[2][1]*m[3][2]*m[0][3] + m[2][0]*m[3][1]*m[0][2]*m[1][3] + m[3][0]*m[0][1]*m[1][2]*m[1][3]
        - m[3][0]*m[2][1]*m[1][2]*m[0][3] - m[0][0]*m[3][1]*m[2][2]*m[1][3] - m[1][0]*m[0][1]*m[3][2]*m[2][3] - m[2][0]*m[1][1]*m[0][2]*m[3][3]
      , M_FLOAT_EPSILON);
}
static inline void mat4_inv(vec4_t *out, const vec4_t *mat)
{
    /* copied from cglm impl */
    
    m_float 
        a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
        e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
        i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
        m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3],

        c1  = k * p - l * o,  c2  = c * h - d * g,  c3  = i * p - l * m,
        c4  = a * h - d * e,  c5  = j * p - l * n,  c6  = b * h - d * f, 
        c7  = i * n - j * m,  c8  = a * f - b * e,  c9  = j * o - k * n,
        c10 = b * g - c * f,  c11 = i * o - k * m,  c12 = a * g - c * e,

        idt = 1.0/(c8*c1+c4*c9+c10*c3+c2*c7-c12*c5-c6*c11), ndt = -idt;

    out[0][0] = (f * c1  - g * c5  + h * c9)  * idt;
    out[0][1] = (b * c1  - c * c5  + d * c9)  * ndt;
    out[0][2] = (n * c2  - o * c6  + p * c10) * idt;
    out[0][3] = (j * c2  - k * c6  + l * c10) * ndt;

    out[1][0] = (e * c1  - g * c3  + h * c11) * ndt;
    out[1][1] = (a * c1  - c * c3  + d * c11) * idt;
    out[1][2] = (m * c2  - o * c4  + p * c12) * ndt;
    out[1][3] = (i * c2  - k * c4  + l * c12) * idt;

    out[2][0] = (e * c5  - f * c3  + h * c7)  * idt;
    out[2][1] = (a * c5  - b * c3  + d * c7)  * ndt;
    out[2][2] = (m * c6  - n * c4  + p * c8)  * idt;
    out[2][3] = (i * c6  - j * c4  + l * c8)  * ndt;

    out[3][0] = (e * c9  - f * c11 + g * c7)  * ndt;
    out[3][1] = (a * c9  - b * c11 + c * c7)  * idt;
    out[3][2] = (m * c10 - n * c12 + o * c8)  * ndt;
    out[3][3] = (i * c10 - j * c12 + k * c8)  * idt;
}
static inline void mat4_mul_vec4(m_float *out, const vec4_t *m, const m_float *a)
{
    out[0] = a[0]*m[0][0] + a[1]*m[1][0] + a[2]*m[2][0] + a[3]*m[3][0];
    out[1] = a[0]*m[0][1] + a[1]*m[1][1] + a[2]*m[2][1] + a[3]*m[3][1];
    out[2] = a[0]*m[0][2] + a[1]*m[1][2] + a[2]*m[2][2] + a[3]*m[3][2];
    out[3] = a[0]*m[0][3] + a[1]*m[1][3] + a[2]*m[2][3] + a[3]*m[3][3];
}
static inline void mat4_mul_mat4(vec4_t *m, const vec4_t *a, const vec4_t *b)
{
    m[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2] + a[3][0]*b[0][3];
    m[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2] + a[3][0]*b[1][3];
    m[2][0] = a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2] + a[3][0]*b[2][3];
    m[3][0] = a[0][0]*b[3][0] + a[1][0]*b[3][1] + a[2][0]*b[3][2] + a[3][0]*b[3][3];

    m[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2] + a[3][1]*b[0][3];
    m[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2] + a[3][1]*b[1][3];
    m[2][1] = a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2] + a[3][1]*b[2][3];
    m[3][1] = a[0][1]*b[3][0] + a[1][1]*b[3][1] + a[2][1]*b[3][2] + a[3][1]*b[3][3];

    m[0][2] = a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2] + a[3][2]*b[0][3];
    m[1][2] = a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2] + a[3][2]*b[1][3];
    m[2][2] = a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2] + a[3][2]*b[2][3];
    m[3][2] = a[0][2]*b[3][0] + a[1][2]*b[3][1] + a[2][2]*b[3][2] + a[3][2]*b[3][3];

    m[0][3] = a[0][3]*b[0][0] + a[1][3]*b[0][1] + a[2][3]*b[0][2] + a[3][3]*b[0][3];
    m[1][3] = a[0][3]*b[1][0] + a[1][3]*b[1][1] + a[2][3]*b[1][2] + a[3][3]*b[1][3];
    m[2][3] = a[0][3]*b[2][0] + a[1][3]*b[2][1] + a[2][3]*b[2][2] + a[3][3]*b[2][3];
    m[3][3] = a[0][3]*b[3][0] + a[1][3]*b[3][1] + a[2][3]*b[3][2] + a[3][3]*b[3][3];
}
static inline void mat4_orthographic(vec4_t *m, m_float xmin, m_float xmax, m_float ymin, m_float ymax, m_float zmin, m_float zmax)
{
    mat4_clear(m);

    m_float dx = xmax - xmin;
    m_float dy = ymax - ymin;
    m_float dz = zmax - zmin;

    m[0][0] =  2/dx;
    m[1][1] =  2/dy;
    m[2][2] = -2/dz;
    m[3][0] = -(xmax + xmin)/dx;
    m[3][1] = -(ymax + ymin)/dy;
    m[3][2] = -(zmax + zmin)/dz;
    m[3][3] = 1.0;
}
static inline void mat4_perspective(vec4_t *m, m_float aspect, m_float yfov, m_float n, m_float f)
{
    mat4_clear(m);

    m_float t = n * m_tan(M_DEG2RAD * yfov / 2.0);
    m_float r = t * aspect;

    m[0][0] = n/r;
    m[1][1] = n/t;
    m[2][2] = -(f+n)/(f-n);
    m[3][2] = -2*f*n/(f-n);
    m[2][3] = -1;
}
static inline void mat4_lookat(vec4_t *m, const m_float *eye, const m_float *point, const m_float *up)
{
    vec3_t f, r, u;

    vec3_sub(f, eye, point);
    vec3_normalize(f, f);

    vec3_cross(r, up, f);
    vec3_normalize(r, r);

    vec3_cross(u, r, f);
    vec3_normalize(u, u);

    mat4_identity(m);

    m[0][0] = r[0];
    m[1][0] = r[1];
    m[2][0] = r[2];
    
    m[0][1] = u[0];
    m[1][1] = u[1];
    m[2][1] = u[2];
    
    m[0][2] = f[0];
    m[1][2] = f[1];
    m[2][2] = f[2];

    m[3][0] = -vec3_dot(eye, r);
    m[3][1] = -vec3_dot(eye, u);
    m[3][2] = -vec3_dot(eye, f);
}
static inline void mat4_lookat_dir(vec4_t *m, const m_float *eye, const m_float *dir, const m_float *up)
{
    mat4_identity(m);
    
    vec3_t f, r, u;

    vec3_flip(f, dir);
    vec3_normalize(f, f);

    vec3_cross(r, up, f);
    vec3_normalize(r, r);

    vec3_cross(u, r, f);
    vec3_normalize(u, u);

    m[0][0] = r[0];
    m[1][0] = r[1];
    m[2][0] = r[2];
    
    m[0][1] = u[0];
    m[1][1] = u[1];
    m[2][1] = u[2];
    
    m[0][2] = f[0];
    m[1][2] = f[1];
    m[2][2] = f[2];

    m[3][0] = -vec3_dot(eye, r);
    m[3][1] = -vec3_dot(eye, u);
    m[3][2] = -vec3_dot(eye, f);
}
static inline void mat4_transform_from_local(vec4_t *m, const m_float *origin, const m_float *x, const m_float *y, const m_float *z)
{
    mat4_identity(m);

    m[0][0] = x[0];
    m[1][0] = x[1];
    m[2][0] = x[2];
    
    m[0][1] = y[0];
    m[1][1] = y[1];
    m[2][1] = y[2];
    
    m[0][2] = z[0];
    m[1][2] = z[1];
    m[2][2] = z[2];

    m[3][0] = -vec3_dot(origin, x);
    m[3][1] = -vec3_dot(origin, y);
    m[3][2] = -vec3_dot(origin, z);
}
static inline void mat4_inv_transform_from_local(vec4_t *m, const m_float *origin, const m_float *x, const m_float *y, const m_float *z)
{
    mat4_identity(m);

    m[0][0] = x[0];
    m[0][1] = x[1];
    m[0][2] = x[2];
    
    m[1][0] = y[0];
    m[1][1] = y[1];
    m[1][2] = y[2];
    
    m[2][0] = z[0];
    m[2][1] = z[1];
    m[2][2] = z[2];

    m[0][3] = vec3_dot(origin, x);
    m[1][3] = vec3_dot(origin, y);
    m[2][3] = vec3_dot(origin, z);
}
static inline void mat4_print(const vec4_t *m)
{
    fprintf(M_PRINT_FILE, "mat4\n{\n");
    for (int i = 0; i < 4; ++i) {
        fprintf(M_PRINT_FILE,"  ");
        for (int j = 0; j < 4; ++j) {
            fprintf(M_PRINT_FILE, "%7.4f, ", m[j][i]);
        }
        fprintf(M_PRINT_FILE, "\n");
    }
    fprintf(M_PRINT_FILE, "}\n");
}

//-------------------------------------------------------------------------------------
// Transform (special mat4)
//-------------------------------------------------------------------------------------

typedef mat4_t tform_t;

static inline void tform(const m_float *translation, const m_float *rotation, const m_float *scale)
{
    // TODO:

    // ~~ transform matrix
    // | rx  ry  rz  tx  |
    // | ux  uy  uz  ty  |
    // | fx  fy  fz  tz  |
    // | 0   0   0   1/s |
}
static inline void tform_clear(vec4_t *t)
{
    // TODO:
}
static inline void tform_inv(vec4_t *out, const tform_t t)
{
    // ~~ inv transform matrix
    // |  rx  ux  fx  0   |
    // |  ry  uy  fy  0   |
    // |  rz  uz  fz  0   |
    // | -tx -ty -tz  1/s |

    mat4_transpose(out, t);
    out[0][3] = -out[0][3];
    out[1][3] = -out[1][3];
    out[2][3] = -out[2][3];
}
static inline void tform_lookat(vec4_t *m, const m_float *eye, const m_float *up, m_float *point)
{
    // lookat() performs a change of basis from canonical [x,y,z]
    // coordinates to a rotated frame in view space. The matrix 
    // must represent going from canonical coordinates to local 
    // view coordinates. Thus, it is the >inverted< basis matrix.

    mat4_identity(m);

    vec3_t f, r, u;

    vec3_sub(f, eye, point); // order flips direction of f
    vec3_normalize(f, f);

    vec3_cross(r, up, f);
    vec3_normalize(r, r);

    vec3_cross(u, f, r);
    vec3_normalize(u, u);

    vec3_copy(m[0], r);
    vec3_copy(m[1], u);
    vec3_copy(m[2], f);

    mat4_transpose_i(m);  // inv is transpose

    m[3][0] = vec3_dot(r, eye);
    m[3][1] = vec3_dot(u, eye);
    m[3][2] = vec3_dot(f, eye);
}

//-------------------------------------------------------------------------------------
// Frustum math
//-------------------------------------------------------------------------------------

// THIS IS COLLISION MATH!

typedef struct {
    m_float near, far;
    m_float left, right;
    m_float top, bottom;
    m_float angle;
} frustum_t;

// TODO: write some visibility checks with the frustum?

//-------------------------------------------------------------------------------------
// Color spaces
//-------------------------------------------------------------------------------------

typedef float color_t[4];




#endif