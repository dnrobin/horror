typedef enum { false = 0, true } bool;

#define USE_DOUBLE_PRECISION
#include "src/math.h"

int main2(int argc, char const *argv[])
{
    vec3_t look, left, up;

    float angles[2] = { M_PI/4*1, M_PI/4*2 };

    vec3(left,
		-m_cos(angles[0]),
         0, // always in the plane
        +m_sin(angles[0])
	);

    vec3(look,
		-m_cos(angles[1])*m_sin(angles[0]),
         m_sin(angles[1]),
        -m_cos(angles[1])*m_cos(angles[0])
	);

	vec3(up,
		m_sin(angles[1]),
        m_cos(angles[1]),
        m_sin(angles[1])
	);

    vec3_print(left);
    vec3_print(up);
    vec3_print(look);

    printf("%.f\n", vec3_dot(left, look));
    printf("%.f\n", vec3_dot(left, up));
    printf("%.f\n", vec3_dot(up, look));

    return 0;
}

int main3(int argc, char const *argv[])
{
    
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));
    printf("m_rand: %f\n", m_rand_btw(3, 4));

    return 0;
}

int main(int argc, char const *argv[])
{
    int Nx = 3, Ny = 2;
    int w = 800 / Nx, h = 600 / Ny;

    int x = 310;
    int y = 540;

    printf("{(%i,%i) => (%i,%i)}\n", x, y, x % w, y % h);

    return 0;
}
