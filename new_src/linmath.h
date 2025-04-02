#ifndef __MAZE_LINMATH_H__
#define __MAZE_LINMATH_H__

#include <float.h>
#include <math.h>

typedef double m_float;

#define m_abs               fabs
#define m_min               fmin
#define m_max               fmax
#define m_mod               fmod
#define m_sin               sin
#define m_cos               cos
#define m_tan               tan
#define m_asin              asin
#define m_acos              acos
#define m_atan              atan
#define m_exp               exp

typedef m_float         vec2[2];

static const vec2       vec2_ZEROS      = { 0, 0 };
static const vec2       vec2_ONES       = { 1, 1 };
static const vec2       vec2_X          = { 1, 0 };
static const vec2       vec2_Y          = { 0, 1 };

typedef m_float         vec3[3];

static const vec3       vec3_ZEROS      = { 0, 0, 0 };
static const vec3       vec3_ONES       = { 1, 1, 1 };
static const vec3       vec3_X          = { 1, 0, 0 };
static const vec3       vec3_Y          = { 0, 1, 0 };
static const vec3       vec3_Z          = { 0, 0, 1 };
static const vec3       vec3_UP         = { 0, 1, 0 };

typedef m_float         vec4[4];

static const vec4       vec4_ZEROS      = { 0, 0, 0, 0 };
static const vec4       vec4_ONES       = { 1, 1, 1, 1 };
static const vec4       vec4_X          = { 1, 0, 0, 0 };
static const vec4       vec4_Y          = { 0, 1, 0, 0 };
static const vec4       vec4_Z          = { 0, 0, 1, 0 };
static const vec4       vec4_W          = { 0, 0, 0, 1 };

static inline void vec4_clear(m_float *v);
static inline void vec4_copy(m_float *v, const m_float *a);
static inline void vec4_set(m_float *v, m_float x, m_float y, m_float z, m_float w);

typedef vec2            mat2[2];

static const mat2       mat2_ZEROS      = { {0, 0}, {0, 0} };
static const mat2       mat2_ONES       = { {1, 1}, {1, 1} };
static const mat2       mat2_EYE        = { {1, 0}, {0, 1} };

typedef vec3            mat3[3];

static const mat3       mat3_ZEROS      = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
static const mat3       mat3_ONES       = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
static const mat3       mat3_EYE        = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

static inline void mat3_clear(vec3 *m);
static inline void mat3_copy(vec3 *m, const vec3 *a);
static inline void mat3_set(vec3 *m
    , m_float m11, m_float m12, m_float m13
    , m_float m21, m_float m22, m_float m23
    , m_float m31, m_float m32, m_float m33);
static inline m_float mat3_det(const vec3 *m);
static inline void mat3_inverse(vec3 *m, const vec3 *a);
static inline void mat3_transpose(vec3 *m, const vec3 *a);

static inline void mat3_inverted(vec3 *m);
static inline void mat3_transposed(vec3 *m);

typedef vec4            mat4[4];

static const mat4       mat4_ZEROS      = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
static const mat4       mat4_ONES       = { {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1} };
static const mat4       mat4_EYE        = { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };

static inline void mat4_clear(vec4 *m);
static inline void mat4_copy(vec4 *m, const vec4 *a);
static inline void mat4_set(vec4 *m
    , m_float m11, m_float m12, m_float m13, m_float m14
    , m_float m21, m_float m22, m_float m23, m_float m24
    , m_float m31, m_float m32, m_float m33, m_float m34
    , m_float m41, m_float m42, m_float m43, m_float m44);
static inline m_float mat4_det(const vec4 *m);
static inline void mat4_inverse(vec4 *m, const vec4 *a);
static inline void mat4_transpose(vec4 *m, const vec4 *a);
static inline void mat4_mul_mat4(vec4 *m, const vec4 *a);
static inline void mat4_mul_vec4(vec4 *m, const m_float *v);
static inline void mat4_transform(vec4 *m, const m_float *origin, const m_float *up, const m_float *right, m_float scale);
static inline void mat4_orthographic(vec4 *m, m_float left, m_float right, m_float top, m_float bottom, m_float znear, m_float zfar); 
static inline void mat4_perspective(vec4 *m, m_float aspect, m_float yfov, m_float znear, m_float zfar);

static inline void mat4_inverted(vec4 *m);
static inline void mat4_transposed(vec4 *m);

#endif