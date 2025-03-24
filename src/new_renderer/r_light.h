#ifndef __R_LIGHT_H__
#define __R_LIGHT_H__

typedef enum {

    LIGHT_POINT = 0,
    LIGHT_LINE,
    LIGHT_AREA,
    LIGHT_SPOT,

    MAX_LIGHT_TYPES
} light_type_t;

typedef struct {
    light_type_t        type;
} light_t;

#endif // __R_LIGHT_H__
