#ifndef __MAZE_GAME_MATH_H__
#define __MAZE_GAME_MATH_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef float               m_float;

#define M_PRINT_FILE stdout
#define M_FLOAT_EPSILON     1e-5f

#define M_INF               INFINITY
#define M_NAN               NAN

#define m_isnan             isnan
#define m_isinf             isinf

static const float M_DEG2RAD = 0.017453292519943295769236907684886127;
static const float M_RAD2DEG = 57.29577951308232087679815481410517033;

//--------------------------------------------------------------------------------------------
// math functions
//--------------------------------------------------------------------------------------------
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

static inline float m_sgn(float x)
{
    return signbit(x) ? -1.0 : 1.0;
}
static inline float m_snap(float x, float f)
{
    return m_sgn(x) * m_abs(m_round( x / f ) * f);
}
static inline float m_clamp(float x, float a, float b)
{
    return m_min(m_max(x, a), b);
}
static inline bool m_within(float x, float a, float b)
{
    return (x >= a) && (x <=b);
}
static inline float m_wrap_to(float x, float f)
{
    float k = m_floor((f - x) / (2 * f));
    return x + 2*f*k;
}
static inline float m_wrap(float x)
{
    return m_wrap_to(x, M_PI);
}
static inline float m_wrap_deg(float x)
{
    return m_wrap_to(x, 180);
}
static inline void m_srand(int seed)
{
    srand(seed);
}
static inline float m_rand()
{
    return (rand() % 10000) / 10000.0;  // 1e-5 precision
}
static inline float m_rand_btw(float a, float b)
{
    return a + (b - a) * m_rand();
}

//--------------------------------------------------------------------------------------------
// Vector 2 (int)
//--------------------------------------------------------------------------------------------

typedef int vec2i[2];

static const vec2i VEC2i_ZEROS = { 0, 0 };
static const vec2i VEC2i_ONES  = { 1, 1 };

static inline void vec2i_zero(int *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
}
static inline void vec2i_ones(int *v)
{
    v[0] = 1.0;
    v[1] = 1.0;
}
static inline void vec2i_set(float *out, int x, int y)
{
    out[0] = x;
    out[1] = y;
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

//--------------------------------------------------------------------------------------------
// Vector 2 (float)
//--------------------------------------------------------------------------------------------

typedef float vec2[2];

static const vec2 VEC2_ZEROS = { 0.0, 0.0 };
static const vec2 VEC2_ONES  = { 1.0, 1.0 };
static const vec2 VEC2_X     = { 1.0, 0.0 };
static const vec2 VEC2_Y     = { 0.0, 1.0 };

static inline void vec2_zero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
}
static inline void vec2_ones(float *v)
{
    v[0] = 1.0;
    v[1] = 1.0;
}
static inline void vec2_set(float *out, float x, float y)
{
    out[0] = x;
    out[1] = y;
}
static inline void vec2_copy(float *out, const float *v)
{
    out[0] = v[0];
    out[1] = v[1];
}
static inline void vec2_add(float *out, const float *a, const float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}
static inline void vec2_sub(float *out, const float *a, const float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}
static inline float vec2_dot(const float *a, const float *b)
{
    return a[0]*b[0] + a[1]*b[1];
}
static inline float vec2_len2(const float *v)
{
    return m_max(M_FLOAT_EPSILON, vec2_dot(v, v));
}
static inline float vec2_len(const float *v)
{
    return m_max(M_FLOAT_EPSILON, m_sqrt(vec2_dot(v, v)));
}
static inline void vec2_mul_vec2(float *out, const float *a, const float *b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}
static inline void vec2_div_vec2(float *out, const float *a, const float *b)
{
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
}
static inline void vec2_mul_f(float *out, const float *v, float f)
{
    out[0] = v[0] * f;
    out[1] = v[1] * f;
}
static inline void vec2_div_f(float *out, const float *v, float f)
{
    out[0] = v[0] / f;
    out[1] = v[1] / f;
}
static inline void vec2_round(float *out, const float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
}
static inline void vec2_snap(float *out, const float *v, float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
}
static inline void vec2_mirror_x(float *out, const float *v)
{
    out[0] = -v[0];
    out[1] = +v[1];
}
static inline void vec2_mirror_y(float *out, const float *v)
{
    out[0] = +v[0];
    out[1] = -v[1];
}
static inline void vec2_flip(float *out, const float *v)
{
    out[0] = -v[0];
    out[1] = -v[1];
}
static inline void vec2_normalize(float *out)
{
    vec2_mul_f(out, out, 1.0 / vec2_len(out));
}
static inline void vec2_get_normalized(float *out, const float *v)
{
    vec2_mul_f(out, v, 1.0 / vec2_len(v));
}
static inline void vec2_scale(float *out, const float *v, float scale)
{
    vec2_mul_f(out, v, scale);
}
static inline void vec2_trim(float *out, const float *v, float len)
{
    vec2_mul_f(out, v, len / vec2_len(v));
}
static inline void vec2_lerp(float *out, const float *a, const float *b, float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
}
static inline void vec2_rotate(float *out, const float *v, float angle)
{
    out[0] = v[0]*m_cos(angle);
    out[1] = v[1]*m_sin(angle);
}
static inline void vec2_rotate_about_point(float *out, const float *v, const float *p, float angle)
{
    out[0] = (v[0] - p[0])*m_cos(angle) + p[0];
    out[1] = (v[1] - p[1])*m_sin(angle) + p[1];
}
static inline void vec2_project_vec2(float *out, const float *v, const float *u)
{
    vec2 n;
    vec2_get_normalized(n, u);
    
    float h = vec2_dot(n, v);

    out[0] = n[0] * h;
    out[1] = n[1] * h;
}
static inline void vec2_reflect_vec2(float *out, const float *v, const float *u)
{
    vec2 n;
    vec2_get_normalized(n, u);

    float h = vec2_dot(n, v);

    out[0] = v[0] - 2*h*n[0];
    out[1] = v[1] - 2*h*n[1];
}
static inline void vec2_print(const float *v)
{
    fprintf(M_PRINT_FILE, "vec2 { ");
    for (int i = 0; i < 2; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}

//--------------------------------------------------------------------------------------------
// Vector 3
//--------------------------------------------------------------------------------------------
typedef float vec3[3];

static const vec3 VEC3_ZEROS = { 0.0, 0.0, 0.0 };
static const vec3 VEC3_ONES  = { 1.0, 1.0, 1.0 };
static const vec3 VEC3_X     = { 1.0, 0.0, 0.0 };
static const vec3 VEC3_Y     = { 0.0, 1.0, 0.0 };
static const vec3 VEC3_Z     = { 0.0, 0.0, 1.0 };

static inline void vec3_zero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}
static inline void vec3_ones(float *v)
{
    v[0] = 1.0;
    v[1] = 1.0;
    v[2] = 1.0;
}
static inline void vec3_set(float *out, float x, float y, float z)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;
}
static inline void vec3_copy(float *out, const float *v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}
static inline void vec3_add(float *out, const float *a, const float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}
static inline void vec3_sub(float *out, const float *a, const float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
static inline float vec3_dot(const float *a, const float *b)
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
static inline void vec3_cross(float *out, const float *a, const float *b)
{
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}
static inline float vec3_len2(const float *v)
{
    return m_max(M_FLOAT_EPSILON, vec3_dot(v, v));
}
static inline float vec3_len(const float *v)
{
    return m_max(M_FLOAT_EPSILON, m_sqrt(vec3_dot(v, v)));
}
static inline void vec3_mul_vec3(float *out, const float *a, const float *b)
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}
static inline void vec3_div_vec3(float *out, const float *a, const float *b)
{
    out[0] = a[0] / b[0];
    out[1] = a[1] / b[1];
    out[2] = a[2] / b[2];
}
static inline void vec3_mul_f(float *out, const float *v, float f)
{
    out[0] = v[0] * f;
    out[1] = v[1] * f;
    out[2] = v[2] * f;
}
static inline void vec3_div_f(float *out, const float *v, float f)
{
    out[0] = v[0] / f;
    out[1] = v[1] / f;
    out[2] = v[2] / f;
}
static inline void vec3_round(float *out, const float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
    out[2] = m_round(v[2]);
}
static inline void vec3_snap(float *out, const float *v, float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
    out[2] = m_snap(v[2], prec);
}
static inline void vec3_flip(float *out, const float *v)
{
    out[0] = -v[0];
    out[1] = -v[1];
    out[2] = -v[2];
}
static inline void vec3_mirror_x(float *out, const float *v)
{
    out[0] = -v[0];
    out[1] = +v[1];
    out[2] = +v[2];
}
static inline void vec3_mirror_y(float *out, const float *v)
{
    out[0] = +v[0];
    out[1] = -v[1];
    out[2] = +v[2];
}
static inline void vec3_mirror_z(float *out, const float *v)
{
    out[0] = +v[0];
    out[1] = +v[1];
    out[2] = -v[2];
}
static inline void vec3_normalize(float *out)
{
    vec3_mul_f(out, out, 1.0 / vec3_len(out));
}
static inline void vec3_get_normalized(float *out, const float *v)
{
    vec3_mul_f(out, v, 1.0 / vec3_len(v));
}
static inline void vec3_scale(float *out, const float *v, float scale)
{
    vec3_mul_f(out, v, scale);
}
static inline void vec3_trim(float *out, const float *v, float len)
{
    vec3_mul_f(out, v, len / vec3_len(v));
}
static inline void vec3_lerp(float *out, const float *a, const float *b, float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
    out[2] = (1 - t)*a[2] + t*b[2];
}
static inline void vec3_rotate_x(float *out, const float *v, float angle)
{
    float s = m_sin(angle);
    float c = m_cos(angle);
    out[0] = s*v[0];
    out[1] =   v[1];
    out[2] = c*v[2];
}
static inline void vec3_rotate_y(float *out, const float *v, float angle)
{
    float s = m_sin(angle);
    float c = m_cos(angle);
    out[0] =   v[0];
    out[1] = s*v[1];
    out[2] = c*v[2];
}
static inline void vec3_rotate_z(float *out, const float *v, float angle)
{
    float s = m_sin(angle);
    float c = m_cos(angle);
    out[0] = c*v[0];
    out[1] = s*v[1];
    out[2] =   v[2];
}
static inline void vec3_rotate(float *out, const float *v, float x, float y, float z)
{
    vec3_rotate_x(out, v, x);
    vec3_rotate_y(out, out, y);
    vec3_rotate_z(out, out, z);
}
static inline void vec3_rotate_about(float *out, const float *v, const float *axis, float angle)
{
    vec3 u;

    vec3_cross(u, axis, v);

    float c = m_cos(angle);
    float s = m_sin(angle);
    float h = vec3_dot(axis, v) * (1 - c);
    
    // Rodrigues' formula: out = cos(t)*v + sin(t)*(k x v) + (1 - cos(t))*(k . v)*k
    out[0] = c*v[0] + s*u[0] + h*axis[0];
    out[1] = c*v[1] + s*u[1] + h*axis[1];
    out[2] = c*v[2] + s*u[2] + h*axis[2];
}
static inline void vec3_project_vec3(float *out, const float *v, const float *u)
{
    vec3 n;
    vec3_get_normalized(n, u);
    
    float h = vec3_dot(n, v);

    out[0] = n[0] * h;
    out[1] = n[1] * h;
    out[2] = n[2] * h;
}
static inline void vec3_reflect_vec3(float *out, const float *v, const float *u)
{
    vec3 n;
    vec3_get_normalized(n, u);

    float h = vec3_dot(n, v);

    out[0] = v[0] - 2*h*n[0];
    out[1] = v[1] - 2*h*n[1];
    out[2] = v[2] - 2*h*n[2];
}
static inline void vec3_print(const float *v)
{
    fprintf(M_PRINT_FILE, "vec3 { ");
    for (int i = 0; i < 3; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}

//--------------------------------------------------------------------------------------------
// Vector 4
//--------------------------------------------------------------------------------------------

typedef float vec4[4];

static const vec4 VEC4_ZEROS = { 0.0, 0.0, 0.0, 0.0 };
static const vec4 VEC4_ONES  = { 1.0, 1.0, 1.0, 1.0 };
static const vec4 VEC4_X     = { 1.0, 0.0, 0.0, 0.0 };
static const vec4 VEC4_Y     = { 0.0, 1.0, 0.0, 0.0 };
static const vec4 VEC4_Z     = { 0.0, 0.0, 1.0, 0.0 };
static const vec4 VEC4_W     = { 0.0, 0.0, 0.0, 1.0 };

static inline void vec4_zero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
    v[3] = 0.0;
}
static inline void vec4_ones(float *v)
{
    v[0] = 1.0;
    v[1] = 1.0;
    v[2] = 1.0;
    v[3] = 1.0;
}
static inline void vec4_set(float *out, float x, float y, float z, float w)
{
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
}
static inline void vec4_copy(float *out, const float *v)
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
}
static inline void vec4_add(float *out, const float *a, const float *b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}
static inline void vec4_sub(float *out, const float *a, const float *b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}
static inline void vec4_lerp(float *out, const float *a, const float *b, float t)
{
    out[0] = (1 - t)*a[0] + t*b[0];
    out[1] = (1 - t)*a[1] + t*b[1];
    out[2] = (1 - t)*a[2] + t*b[2];
    out[3] = (1 - t)*a[3] + t*b[3];
}
static inline void vec4_round(float *out, const float *v)
{
    out[0] = m_round(v[0]);
    out[1] = m_round(v[1]);
    out[2] = m_round(v[2]);
    out[3] = m_round(v[3]);
}
static inline void vec4_snap(float *out, const float *v, float prec)
{
    out[0] = m_snap(v[0], prec);
    out[1] = m_snap(v[1], prec);
    out[2] = m_snap(v[2], prec);
    out[3] = m_snap(v[3], prec);
}
static inline void vec4_print(const float *v)
{
    fprintf(M_PRINT_FILE, "vec4 { ");
    for (int i = 0; i < 4; ++i) {
        if (i > 0) fprintf(M_PRINT_FILE, ", ");
        fprintf(M_PRINT_FILE, "%7.4f", v[i]);
    }
    fprintf(M_PRINT_FILE, ")}n");
}

//--------------------------------------------------------------------------------------------
// Matrix 2x2
//--------------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec2 mat2[2];

static const mat2 MAT2_ZEROS = { {0.0, 0.0}, {0.0, 0.0} };
static const mat2 MAT2_ONES  = { {1.0, 1.0}, {1.0, 1.0} };
static const mat2 MAT2_EYE   = { {1.0, 0.0}, {0.0, 1.0} };

static inline void mat2_zero(vec2 *out)
{
    out[0][0] = 0.0; out[1][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 0.0;
}
static inline void mat2_ones(vec2 *out)
{
    out[0][0] = 1.0; out[1][0] = 1.0;
    out[0][1] = 1.0; out[1][1] = 1.0;
}
static inline void mat2_set(vec2 *out,
    float m11, float m12,
    float m21, float m22)
{
    out[0][0] = m11; out[1][0] = m12;
    out[0][1] = m21; out[1][1] = m22;
}
static inline void mat2_identity(vec2 *out)
{
    out[0][0] = 1.0; out[1][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 1.0;
}
static inline void mat2_copy(vec2 *out, vec2 *m)
{
    out[0][0] = m[0][0]; out[1][0] = m[1][0];
    out[0][1] = m[0][1]; out[1][1] = m[1][1];
}
static inline float mat2_det(const vec2 *m)
{
    return m_snap(m[0][0]*m[1][1] - m[1][0]*m[0][1], M_FLOAT_EPSILON);
}
static inline void mat2_transpose(vec2 *out)
{
    float
        m11 = out[0][0], m12 = out[1][0],
        m21 = out[0][1], m22 = out[1][1];
    
    out[0][0] = m11; out[1][0] = m21;
    out[0][1] = m12; out[1][1] = m22;
}
static inline void mat2_invert(vec2 *out)
{
    float h = 1.0 / mat2_det(out),
        m11 = out[0][0], m12 = out[1][0],
        m21 = out[0][1], m22 = out[1][1];

    out[0][0] =  h*m22; out[1][0] = -h*m12;
    out[0][1] = -h*m21; out[1][1] =  h*m11;
}
static inline void mat2_get_transpose(vec2 *out, vec2 *m)
{
    out[0][0] = m[0][0]; out[1][0] = m[0][1];
    out[0][1] = m[1][0]; out[1][1] = m[1][1];
}
static inline void mat2_get_inverse(vec2 *out, const vec2 *a)
{
    float h = 1.0 / mat2_det(a);

    out[0][0] =  h*a[1][1]; out[1][0] = -h*a[1][0];
    out[0][1] = -h*a[0][1]; out[1][1] =  h*a[0][0];
}
static inline void mat2_mul_vec2(float *out, const vec2 *m, const float *a)
{
    out[0] = a[0]*m[0][0] + a[1]*m[1][0];
    out[1] = a[0]*m[0][1] + a[1]*m[1][1];
}
static inline void mat2_mul_mat2(vec2 *out, const vec2 *a, const vec2 *b)
{
    out[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1];
    out[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1];

    out[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1];
    out[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1];
}
static inline void mat2_print(const vec2 *m)
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

//--------------------------------------------------------------------------------------------
// Matrix 3x3
//--------------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec3 mat3[3];

static const mat3 MAT3_ZEROS = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };
static const mat3 MAT3_ONES  = { {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0} };
static const mat3 MAT3_EYE   = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };

static inline void mat3_zero(vec3 *out)
{
    out[0][0] = 0.0; out[1][0] = 0.0; out[2][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 0.0; out[2][1] = 0.0;
    out[0][2] = 0.0; out[1][2] = 0.0; out[2][2] = 0.0;
}
static inline void mat3_ones(vec3 *out)
{
    out[0][0] = 1.0; out[1][0] = 1.0; out[2][0] = 1.0;
    out[0][1] = 1.0; out[1][1] = 1.0; out[2][1] = 1.0;
    out[0][2] = 1.0; out[1][2] = 1.0; out[2][2] = 1.0;
}
static inline void mat3_set(vec3 *out,
    float m11, float m12, float m13,
    float m21, float m22, float m23,
    float m31, float m32, float m33)
{
    out[0][0] = m11; out[1][0] = m12; out[2][0] = m13;
    out[0][1] = m21; out[1][1] = m22; out[2][1] = m23;
    out[0][2] = m31; out[1][2] = m32; out[2][2] = m33;
}
static inline void mat3_identity(vec3 *out)
{
    out[0][0] = 1.0; out[1][0] = 0.0; out[2][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 1.0; out[2][1] = 0.0;
    out[0][2] = 0.0; out[1][2] = 0.0; out[2][2] = 1.0;
}
static inline void mat3_copy(vec3 *out, const vec3 *a)
{
    out[0][0] = a[0][0]; out[1][0] = a[1][0]; out[2][0] = a[2][0];
    out[0][1] = a[0][1]; out[1][1] = a[1][1]; out[2][1] = a[2][1];
    out[0][2] = a[0][2]; out[1][2] = a[1][2]; out[2][2] = a[2][2];
}
static inline float mat3_det(const vec3 *m)
{
    return m_snap(
          m[0][0]*m[1][1]*m[2][2] + m[1][0]*m[2][1]*m[0][2] + m[2][0]*m[0][1]*m[1][2]
        - m[2][0]*m[1][1]*m[0][2] - m[1][0]*m[0][1]*m[2][2] - m[0][0]*m[2][1]*m[1][2]
        , M_FLOAT_EPSILON);
}
static inline void mat3_transpose(vec3 *out)
{
    float
        m11 = out[0][0], m12 = out[1][0], m13 = out[2][0],
        m21 = out[0][1], m22 = out[1][1], m23 = out[2][1],
        m31 = out[0][2], m32 = out[1][2], m33 = out[2][2];
    
    out[0][0] = m11; out[1][0] = m21; out[2][0] = m31;
    out[0][1] = m12; out[1][1] = m22; out[2][1] = m32;
    out[0][2] = m13; out[1][2] = m23; out[2][2] = m33;
}
static inline void mat3_invert(vec3 *out)
{
    float
        m11 = out[0][0], m12 = out[1][0], m13 = out[2][0],
        m21 = out[0][1], m22 = out[1][1], m23 = out[2][1],
        m31 = out[0][2], m32 = out[1][2], m33 = out[2][2],

        d = mat3_det(out);
    
    out[0][0] = ( m22*m33 - m23*m32) / d;
    out[0][1] = (-m21*m33 + m23*m31) / d;
    out[0][2] = ( m21*m32 - m22*m31) / d;

    out[1][0] = (-m12*m33 + m13*m32) / d;
    out[1][1] = ( m11*m33 - m13*m31) / d;
    out[1][2] = (-m11*m32 + m12*m31) / d;

    out[2][0] = ( m12*m23 - m13*m22) / d;
    out[2][1] = (-m11*m23 + m13*m21) / d;
    out[2][2] = ( m11*m22 - m12*m21) / d;
}
static inline void mat3_get_transpose(vec3 *out, const vec3 *m)
{
    out[0][0] = m[0][0]; out[1][0] = m[0][1]; out[2][0] = m[0][2];
    out[0][1] = m[1][0]; out[1][1] = m[1][1]; out[2][1] = m[1][2];
    out[0][2] = m[2][0]; out[1][2] = m[2][1]; out[2][2] = m[2][2];
}
static inline void mat3_get_inverse(vec3 *out, const vec3 *m)
{
    float
        m11 = m[0][0], m12 = m[1][0], m13 = m[2][0],
        m21 = m[0][1], m22 = m[1][1], m23 = m[2][1],
        m31 = m[0][2], m32 = m[1][2], m33 = m[2][2],

        d = mat3_det(m);
    
    out[0][0] = ( m22*m33 - m23*m32) / d;
    out[0][1] = (-m21*m33 + m23*m31) / d;
    out[0][2] = ( m21*m32 - m22*m31) / d;

    out[1][0] = (-m12*m33 + m13*m32) / d;
    out[1][1] = ( m11*m33 - m13*m31) / d;
    out[1][2] = (-m11*m32 + m12*m31) / d;

    out[2][0] = ( m12*m23 - m13*m22) / d;
    out[2][1] = (-m11*m23 + m13*m21) / d;
    out[2][2] = ( m11*m22 - m12*m21) / d;
}
static inline void mat3_mul_vec3(float *out, const vec3 *m, const float *v)
{
    out[0] = v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0];
    out[1] = v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1];
    out[2] = v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2];
}
static inline void mat3_mul_mat3(vec3 *out, const vec3 *a, const vec3 *b)
{
    out[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2];
    out[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2];
    out[2][0] = a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2];

    out[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2];
    out[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2];
    out[2][1] = a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2];

    out[0][2] = a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2];
    out[1][2] = a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2];
    out[2][2] = a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2];
}
static inline void mat3_print(const vec3 *m)
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

//--------------------------------------------------------------------------------------------
// Matrix 4x4
//--------------------------------------------------------------------------------------------

/** column-major representation, addressing follows m[COL][ROW] **/

typedef vec4 mat4[4];

static const mat4 MAT4_ZEROS = { {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0} };
static const mat4 MAT4_ONES  = { {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0} };
static const mat4 MAT4_EYE   = { {1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0} };

static inline void mat4_zero(vec4 *out)
{
    out[0][0] = 0.0; out[1][0] = 0.0; out[2][0] = 0.0; out[3][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 0.0; out[2][1] = 0.0; out[3][1] = 0.0;
    out[0][2] = 0.0; out[1][2] = 0.0; out[2][2] = 0.0; out[3][2] = 0.0;
    out[0][3] = 0.0; out[1][3] = 0.0; out[2][3] = 0.0; out[3][3] = 0.0;
}
static inline void mat4_ones(vec4 *out)
{
    out[0][0] = 1.0; out[1][0] = 1.0; out[2][0] = 1.0; out[3][0] = 1.0;
    out[0][1] = 1.0; out[1][1] = 1.0; out[2][1] = 1.0; out[3][1] = 1.0;
    out[0][2] = 1.0; out[1][2] = 1.0; out[2][2] = 1.0; out[3][2] = 1.0;
    out[0][3] = 1.0; out[1][3] = 1.0; out[2][3] = 1.0; out[3][3] = 1.0;
}
static inline void mat4_set(vec4 *out,
    float m11, float m12, float m13, float m14,
    float m21, float m22, float m23, float m24,
    float m31, float m32, float m33, float m34,
    float m41, float m42, float m43, float m44)
{
    out[0][0] = m11; out[1][0] = m12; out[2][0] = m13; out[3][0] = m14;
    out[0][1] = m21; out[1][1] = m22; out[2][1] = m23; out[3][1] = m24;
    out[0][2] = m31; out[1][2] = m32; out[2][2] = m33; out[3][2] = m34;
    out[0][3] = m41; out[1][3] = m42; out[2][3] = m43; out[3][3] = m44;
}
static inline void mat4_identity(vec4 *out)
{
    out[0][0] = 1.0; out[1][0] = 0.0; out[2][0] = 0.0; out[3][0] = 0.0;
    out[0][1] = 0.0; out[1][1] = 1.0; out[2][1] = 0.0; out[3][1] = 0.0;
    out[0][2] = 0.0; out[1][2] = 0.0; out[2][2] = 1.0; out[3][2] = 0.0;
    out[0][3] = 0.0; out[1][3] = 0.0; out[2][3] = 0.0; out[3][3] = 1.0;
}
static inline void mat4_copy(vec4 *out, const vec4 *m)
{
    out[0][0] = m[0][0]; out[1][0] = m[1][0]; out[2][0] = m[2][0]; out[3][0] = m[3][0];
    out[0][1] = m[0][1]; out[1][1] = m[1][1]; out[2][1] = m[2][1]; out[3][1] = m[3][1];
    out[0][2] = m[0][2]; out[1][2] = m[1][2]; out[2][2] = m[2][2]; out[3][2] = m[3][2];
    out[0][3] = m[0][3]; out[1][3] = m[1][3]; out[2][3] = m[2][3]; out[3][3] = m[3][3];
}
static inline float mat4_det(const vec4 *m)
{
    return m_snap(
        + ( m[1][1]*m[2][2]*m[3][3] + m[1][2]*m[2][3]*m[3][1] + m[1][3]*m[2][1]*m[3][2] - m[1][3]*m[2][2]*m[3][1] - m[1][2]*m[2][1]*m[3][3] - m[1][1]*m[2][3]*m[3][2]) * m[0][0]
        + (-m[1][0]*m[2][2]*m[3][3] - m[1][2]*m[2][3]*m[3][0] - m[1][3]*m[2][0]*m[3][2] + m[1][3]*m[2][2]*m[3][0] + m[1][2]*m[2][0]*m[3][3] + m[1][0]*m[2][3]*m[3][2]) * m[0][1]
        + ( m[1][0]*m[2][1]*m[3][3] + m[1][1]*m[2][3]*m[3][0] + m[1][3]*m[2][0]*m[3][1] - m[1][3]*m[2][1]*m[3][0] - m[1][1]*m[2][0]*m[3][3] - m[1][0]*m[2][3]*m[3][1]) * m[0][2]
        + (-m[1][0]*m[2][1]*m[3][2] - m[1][1]*m[2][2]*m[3][0] - m[1][2]*m[2][0]*m[3][1] + m[1][2]*m[2][1]*m[3][0] + m[1][1]*m[2][0]*m[3][2] + m[1][0]*m[2][2]*m[3][1]) * m[0][3]
      , M_FLOAT_EPSILON);
}
static inline void mat4_transpose(vec4 *out)
{
    float
        m11 = out[0][0], m12 = out[1][0], m13 = out[2][0], m14 = out[3][0], 
        m21 = out[0][1], m22 = out[1][1], m23 = out[2][1], m24 = out[3][1], 
        m31 = out[0][2], m32 = out[1][2], m33 = out[2][2], m34 = out[3][2], 
        m41 = out[0][3], m42 = out[1][3], m43 = out[2][3], m44 = out[3][3];
    
    out[0][0] = m11; out[1][0] = m21; out[2][0] = m31; out[3][0] = m41;
    out[0][1] = m12; out[1][1] = m22; out[2][1] = m32; out[3][1] = m42;
    out[0][2] = m13; out[1][2] = m23; out[2][2] = m33; out[3][2] = m43;
    out[0][3] = m14; out[1][3] = m24; out[2][3] = m34; out[3][3] = m44;
}
static inline void mat4_invert(vec4 *out)
{
    float
        m11 = out[0][0], m12 = out[1][0], m13 = out[2][0], m14 = out[3][0], 
        m21 = out[0][1], m22 = out[1][1], m23 = out[2][1], m24 = out[3][1], 
        m31 = out[0][2], m32 = out[1][2], m33 = out[2][2], m34 = out[3][2], 
        m41 = out[0][3], m42 = out[1][3], m43 = out[2][3], m44 = out[3][3],

        d = mat4_det(out);

    out[0][0] = ( m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m24*m33*m42 - m23*m32*m44 - m22*m34*m43) / d;
    out[0][1] = (-m21*m33*m44 - m23*m34*m41 - m24*m31*m43 + m24*m33*m41 + m23*m31*m44 + m21*m34*m43) / d;
    out[0][2] = ( m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m24*m32*m41 - m22*m31*m44 - m21*m34*m42) / d;
    out[0][3] = (-m21*m32*m43 - m22*m33*m41 - m23*m31*m42 + m23*m32*m41 + m22*m31*m43 + m21*m33*m42) / d;

    out[1][0] = (-m12*m33*m44 - m13*m34*m42 - m14*m32*m43 + m14*m33*m42 + m13*m32*m44 + m12*m34*m43) / d;
    out[1][1] = ( m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m14*m33*m41 - m13*m31*m44 - m11*m34*m43) / d;
    out[1][2] = (-m11*m32*m44 - m12*m34*m41 - m14*m31*m42 + m14*m32*m41 + m12*m31*m44 + m11*m34*m42) / d;
    out[1][3] = ( m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m13*m32*m41 - m12*m31*m43 - m11*m33*m42) / d;

    out[2][0] = ( m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m14*m23*m42 - m13*m22*m44 - m12*m24*m43) / d;
    out[2][1] = (-m11*m23*m44 - m13*m24*m41 - m14*m21*m43 + m14*m23*m41 + m13*m21*m44 + m11*m24*m43) / d;
    out[2][2] = ( m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m14*m22*m41 - m12*m21*m44 - m11*m24*m42) / d;
    out[2][3] = (-m11*m22*m43 - m12*m23*m41 - m13*m21*m42 + m13*m22*m41 + m12*m21*m43 + m11*m23*m42) / d;

    out[3][0] = (-m12*m23*m34 - m13*m24*m32 - m14*m22*m33 + m14*m23*m32 + m13*m22*m34 + m12*m24*m33) / d;
    out[3][1] = ( m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m14*m23*m31 - m13*m21*m34 - m11*m24*m33) / d;
    out[3][2] = (-m11*m22*m34 - m12*m24*m31 - m14*m21*m32 + m14*m22*m31 + m12*m21*m34 + m11*m24*m32) / d;
    out[3][3] = ( m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m13*m22*m31 - m12*m21*m33 - m11*m23*m32) / d;
}
static inline void mat4_get_transpose(vec4 *out, const vec4 *m)
{
    out[0][0] = m[0][0]; out[1][0] = m[0][1]; out[2][0] = m[0][2]; out[3][0] = m[0][3];
    out[0][1] = m[1][0]; out[1][1] = m[1][1]; out[2][1] = m[1][2]; out[3][1] = m[1][3];
    out[0][2] = m[2][0]; out[1][2] = m[2][1]; out[2][2] = m[2][2]; out[3][2] = m[2][3];
    out[0][3] = m[3][0]; out[1][3] = m[3][1]; out[2][3] = m[3][2]; out[3][3] = m[3][3];
}
static inline void mat4_get_inverse(vec4 *out, const vec4 *m)
{
    float
        m11 = m[0][0], m12 = m[1][0], m13 = m[2][0], m14 = m[3][0], 
        m21 = m[0][1], m22 = m[1][1], m23 = m[2][1], m24 = m[3][1], 
        m31 = m[0][2], m32 = m[1][2], m33 = m[2][2], m34 = m[3][2], 
        m41 = m[0][3], m42 = m[1][3], m43 = m[2][3], m44 = m[3][3],

        d = mat4_det(m);
        
    out[0][0] = ( m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m24*m33*m42 - m23*m32*m44 - m22*m34*m43) / d;
    out[0][1] = (-m21*m33*m44 - m23*m34*m41 - m24*m31*m43 + m24*m33*m41 + m23*m31*m44 + m21*m34*m43) / d;
    out[0][2] = ( m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m24*m32*m41 - m22*m31*m44 - m21*m34*m42) / d;
    out[0][3] = (-m21*m32*m43 - m22*m33*m41 - m23*m31*m42 + m23*m32*m41 + m22*m31*m43 + m21*m33*m42) / d;

    out[1][0] = (-m12*m33*m44 - m13*m34*m42 - m14*m32*m43 + m14*m33*m42 + m13*m32*m44 + m12*m34*m43) / d;
    out[1][1] = ( m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m14*m33*m41 - m13*m31*m44 - m11*m34*m43) / d;
    out[1][2] = (-m11*m32*m44 - m12*m34*m41 - m14*m31*m42 + m14*m32*m41 + m12*m31*m44 + m11*m34*m42) / d;
    out[1][3] = ( m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m13*m32*m41 - m12*m31*m43 - m11*m33*m42) / d;

    out[2][0] = ( m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m14*m23*m42 - m13*m22*m44 - m12*m24*m43) / d;
    out[2][1] = (-m11*m23*m44 - m13*m24*m41 - m14*m21*m43 + m14*m23*m41 + m13*m21*m44 + m11*m24*m43) / d;
    out[2][2] = ( m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m14*m22*m41 - m12*m21*m44 - m11*m24*m42) / d;
    out[2][3] = (-m11*m22*m43 - m12*m23*m41 - m13*m21*m42 + m13*m22*m41 + m12*m21*m43 + m11*m23*m42) / d;

    out[3][0] = (-m12*m23*m34 - m13*m24*m32 - m14*m22*m33 + m14*m23*m32 + m13*m22*m34 + m12*m24*m33) / d;
    out[3][1] = ( m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m14*m23*m31 - m13*m21*m34 - m11*m24*m33) / d;
    out[3][2] = (-m11*m22*m34 - m12*m24*m31 - m14*m21*m32 + m14*m22*m31 + m12*m21*m34 + m11*m24*m32) / d;
    out[3][3] = ( m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m13*m22*m31 - m12*m21*m33 - m11*m23*m32) / d;
}
static inline void mat4_mul_vec4(float *out, const vec4 *m, const float *v)
{
    out[0] = v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0] + v[3]*m[3][0];
    out[1] = v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1] + v[3]*m[3][1];
    out[2] = v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] + v[3]*m[3][2];
    out[3] = v[0]*m[0][3] + v[1]*m[1][3] + v[2]*m[2][3] + v[3]*m[3][3];
}
static inline void mat4_mul_mat4(vec4 *out, const vec4 *a, const vec4 *b)
{
    out[0][0] = a[0][0]*b[0][0] + a[1][0]*b[0][1] + a[2][0]*b[0][2] + a[3][0]*b[0][3];
    out[1][0] = a[0][0]*b[1][0] + a[1][0]*b[1][1] + a[2][0]*b[1][2] + a[3][0]*b[1][3];
    out[2][0] = a[0][0]*b[2][0] + a[1][0]*b[2][1] + a[2][0]*b[2][2] + a[3][0]*b[2][3];
    out[3][0] = a[0][0]*b[3][0] + a[1][0]*b[3][1] + a[2][0]*b[3][2] + a[3][0]*b[3][3];

    out[0][1] = a[0][1]*b[0][0] + a[1][1]*b[0][1] + a[2][1]*b[0][2] + a[3][1]*b[0][3];
    out[1][1] = a[0][1]*b[1][0] + a[1][1]*b[1][1] + a[2][1]*b[1][2] + a[3][1]*b[1][3];
    out[2][1] = a[0][1]*b[2][0] + a[1][1]*b[2][1] + a[2][1]*b[2][2] + a[3][1]*b[2][3];
    out[3][1] = a[0][1]*b[3][0] + a[1][1]*b[3][1] + a[2][1]*b[3][2] + a[3][1]*b[3][3];

    out[0][2] = a[0][2]*b[0][0] + a[1][2]*b[0][1] + a[2][2]*b[0][2] + a[3][2]*b[0][3];
    out[1][2] = a[0][2]*b[1][0] + a[1][2]*b[1][1] + a[2][2]*b[1][2] + a[3][2]*b[1][3];
    out[2][2] = a[0][2]*b[2][0] + a[1][2]*b[2][1] + a[2][2]*b[2][2] + a[3][2]*b[2][3];
    out[3][2] = a[0][2]*b[3][0] + a[1][2]*b[3][1] + a[2][2]*b[3][2] + a[3][2]*b[3][3];

    out[0][3] = a[0][3]*b[0][0] + a[1][3]*b[0][1] + a[2][3]*b[0][2] + a[3][3]*b[0][3];
    out[1][3] = a[0][3]*b[1][0] + a[1][3]*b[1][1] + a[2][3]*b[1][2] + a[3][3]*b[1][3];
    out[2][3] = a[0][3]*b[2][0] + a[1][3]*b[2][1] + a[2][3]*b[2][2] + a[3][3]*b[2][3];
    out[3][3] = a[0][3]*b[3][0] + a[1][3]*b[3][1] + a[2][3]*b[3][2] + a[3][3]*b[3][3];
}
static inline void mat4_print(const vec4 *m)
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
//--------------------------------------------------------------------------------------------
// Special Matrix 4x4
//--------------------------------------------------------------------------------------------
static inline void mat4_orthographic(vec4 *m, float left, float right, float top, float bottom, float znear, float zfar)
{
    mat4_zero(m);

    float dx = right - left;
    float dy = top - bottom;
    float dz = zfar - znear;

    m[0][0] =  2/dx;
    m[1][1] =  2/dy;
    m[2][2] = -2/dz;
    m[3][0] = -(right + left)/dx;
    m[3][1] = -(top + bottom)/dy;
    m[3][2] = -(zfar + znear)/dz;
    m[3][3] = 1.0;
}
static inline void mat4_perspective(vec4 *m, float aspect, float yfov, float znear, float zfar)
{
    mat4_zero(m);

    float t = znear * m_tan(M_DEG2RAD * yfov / 2.0);
    float r = t * aspect;

    m[0][0] = znear/r;
    m[1][1] = znear/t;
    m[2][2] = -(zfar+znear)/(zfar-znear);
    m[3][2] = -2*zfar*znear/(zfar-znear);
    m[2][3] = -1;
}

//-------------------------------------------------------------------------------------
// Quaternions
//-------------------------------------------------------------------------------------

typedef float quat[4];  // [i, j, k, w]

static inline void quat_zero(float *q)
{
    q[0] = 0.0;
    q[1] = 0.0;
    q[2] = 0.0;
    q[3] = 0.0;
}
static inline void quat_identity(float *q)
{
    q[0] = 0.0;
    q[1] = 0.0;
    q[2] = 0.0;
    q[3] = 1.0;
}
static inline void quat_copy(float *out, const float *q)
{
    out[0] = q[0];
    out[1] = q[1];
    out[2] = q[2];
    out[3] = q[3];
}
static inline void quat_rotate_about(float *out, const float *q, const float *u, float angle);
static inline void quat_rotate(float *out, const float *q, float angle);
static inline void quat_to_mat3(vec3 *out, const float *q)
{
    float 
        q0q0 = q[0]*q[0], q0q1 = q[0]*q[1], q0q2 = q[0]*q[2], q0q3 = q[0]*q[3],
        q1q1 = q[1]*q[1], q1q2 = q[1]*q[2], q1q3 = q[1]*q[3],
        q2q2 = q[2]*q[2], q2q3 = q[2]*q[3],
        q3q3 = q[3]*q[3];

    out[0][0] = 2*(q0q0 + q1q1) - 1;
    out[0][1] = 2*(q1q2 + q0q3);
    out[0][2] = 2*(q1q3 - q0q2);
    
    out[1][0] = 2*(q1q2 - q0q3);
    out[1][1] = 2*(q0q0 + q2q2) - 1;
    out[1][2] = 2*(q2q3 + q0q1);
    
    out[2][0] = 2*(q1q3 + q0q2);
    out[2][1] = 2*(q2q3 - q0q1);
    out[2][2] = 2*(q0q0 + q3q3) - 1;
}
static inline void quat_to_mat4(vec4 *out, const float *q)
{   
    float 
        q0q0 = q[0]*q[0], q0q1 = q[0]*q[1], q0q2 = q[0]*q[2], q0q3 = q[0]*q[3],
        q1q1 = q[1]*q[1], q1q2 = q[1]*q[2], q1q3 = q[1]*q[3],
        q2q2 = q[2]*q[2], q2q3 = q[2]*q[3],
        q3q3 = q[3]*q[3];

    out[0][0] = 2*(q0q0 + q1q1) - 1;
    out[0][1] = 2*(q1q2 + q0q3);
    out[0][2] = 2*(q1q3 - q0q2);
    out[0][3] = 0;

    out[1][0] = 2*(q1q2 - q0q3);
    out[1][1] = 2*(q0q0 + q2q2) - 1;
    out[1][2] = 2*(q2q3 + q0q1);
    out[1][3] = 0;

    out[2][0] = 2*(q1q3 + q0q2);
    out[2][1] = 2*(q2q3 - q0q1);
    out[2][2] = 2*(q0q0 + q3q3) - 1;
    out[2][3] = 0;
    
    out[3][0] = 0;
    out[3][1] = 0;
    out[3][2] = 0;
    out[3][3] = 1;
}

//-------------------------------------------------------------------------------------
// Transform
//-------------------------------------------------------------------------------------

typedef struct {
    vec3            translation;
    quat            rotation;
    vec3            scaling;
} transform;

// lookat() performs a change of basis from canonical [x,y,z]
// coordinates to a rotated frame in view space. The matrix 
// must represent going from canonical coordinates to local 
// view coordinates. Thus, it is the >inverted< basis matrix.

static inline void transform_identity(transform *out)
{
    quat_identity(out->rotation);
    vec3_zero(out->translation);
    vec3_ones(out->scaling);
}
static inline void transform_transform_vec4(float *out, const transform *t, const float *v);
static inline void transform_transform_coord(float *out, const transform *t, const float *xyz);
static inline void transform_apply_transform(transform *out, const transform *in, const transform *other);
static inline void transform_from_mat4(transform *out, const vec4 *m)
{
    vec3 u, v, w;

    vec3_copy(u, m[0]);
    vec3_copy(v, m[1]);
    vec3_copy(w, m[2]);

    out->scaling[0] = vec3_len(u);
    out->scaling[1] = vec3_len(v);
    out->scaling[2] = vec3_len(w);

    vec3_normalize(u);
    vec3_normalize(v);
    vec3_normalize(w);
}
static inline void transform_to_mat4(vec4 *out, const transform *t)
{
    // ~~ transform matrix
    // | rx  ry  rz  tx  |
    // | ux  uy  uz  ty  |
    // | fx  fy  fz  tz  |
    // | 0   0   0   1/s |

    quat_to_mat4(out, t->rotation);

    out[3][0] = vec3_dot(t->translation, out[0]);
    out[3][1] = vec3_dot(t->translation, out[1]);
    out[3][2] = vec3_dot(t->translation, out[2]);

    // vec4_copy(out[3], t->translation);  // shouln't it be in local axis representation???
    
    out[0][0] *= t->scaling[0];
    out[1][1] *= t->scaling[1];
    out[2][2] *= t->scaling[2];         // what about w coordinate trick??
}
static inline void transform_inverse_to_mat4(vec4 *out, const transform *t)
{
    // ~~ inv transform matrix
    // |  rx  ux  fx  0   |
    // |  ry  uy  fy  0   |
    // |  rz  uz  fz  0   |
    // | -tx -ty -tz  s   |

    quat_to_mat4(out, t->rotation);
    mat4_transpose(out);
    out[0][3] = -vec3_dot(t->translation, out[0]);
    out[1][3] = -vec3_dot(t->translation, out[1]);
    out[2][3] = -vec3_dot(t->translation, out[2]);
    out[0][0] *= t->scaling[0];
    out[1][1] *= t->scaling[1];
    out[2][2] *= t->scaling[2];
}
static inline void transform_rotate_quat(vec4 *out, const vec4 *m, const float *q)
{
    float
        q0q0 = q[0]*q[0], q0q1 = q[0]*q[1], q0q2 = q[0]*q[2], q0q3 = q[0]*q[3],
        q1q0 = q[1]*q[0], q1q1 = q[1]*q[1], q1q2 = q[1]*q[2], q1q3 = q[1]*q[3],
        q2q0 = q[2]*q[0], q2q1 = q[2]*q[1], q2q2 = q[2]*q[2], q2q3 = q[2]*q[3],
        q3q0 = q[3]*q[0], q3q1 = q[3]*q[1], q3q2 = q[3]*q[2], q3q3 = q[3]*q[3];

    mat4 r;
    mat4_identity(r);

    r[0][0] = 2*q0q0 + 2*q1q1 - 1;
    r[0][1] = 2*(q1q2 + q0q3);
    r[0][2] = 2*(q1q3 - q0q2);
    
    r[1][0] = 2*(q1q2 - q0q3);
    r[1][1] = 2*q0q0 + 2*q2q2 - 1;
    r[1][2] = 2*(q2q3 + q0q1);
    
    r[2][0] = 2*(q1q3 + q0q2);
    r[2][1] = 2*(q2q3 - q0q1);
    r[2][2] = 2*q0q0 + 2*q3q3 - 1;

    mat4_mul_mat4(out, r, m);
}

//-------------------------------------------------------------------------------------
// Color spaces
//-------------------------------------------------------------------------------------

typedef float color[4];

#endif