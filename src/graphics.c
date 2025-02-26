#include "shared.h"
#include "graphics.h"

#include "glad.h"

void checkGLError()
{
	GLenum e = glGetError();
	if(e != GL_NO_ERROR) {
		printf("There is a GL error pending: \n");
		switch(e)
		{
			case GL_INVALID_ENUM: printf("GL_INVALID_ENUM\n"); break;
			case GL_INVALID_VALUE: printf("GL_INVALID_VALUE\n"); break;
			case GL_INVALID_OPERATION: printf("GL_INVALID_OPERATION\n"); break;
			// case GL_INVALID_FRAMEBUFFER_OPERATION: printf("GL_INVALID_FRAMEBUFFER_OPERATION\n"); break;
			case GL_OUT_OF_MEMORY: printf("GL_OUT_OF_MEMORY\n"); break;
			case GL_STACK_UNDERFLOW: printf("GL_STACK_UNDERFLOW\n"); break;
			case GL_STACK_OVERFLOW: printf("GL_STACK_OVERFLOW\n"); break;
		}
	}
}

void init_gl() 
{
	glClearColor( 0.4, 0.3, 1.0, 1.0 );
	glClearDepth( 1.0 );

    // glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
    // glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	// glBlendFunc(GL_ONE, GL_ONE);
	// glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
	// glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA);
	// glDepthFunc(GL_EQUAL);
	
	// enable a bunch of options -- not sure if it should be called on display instead...
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	if ( !GL_DEBUG_WITH_MIN ) {
		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_FOG);
	}
	
	// setup fog parameters
	float fogColor[] = { 0.4, 0.3, 1.0, 1.0 };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.25);
	glHint(GL_FOG_HINT, GL_NICEST);
	
	float flash_light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	float flash_light_diffuse[] = { 1.0, 0.9, 0.3, 1.0 };
	float flash_light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, flash_light_ambient);
	
	// flash light settings
	glLightfv(GL_LIGHT1, GL_AMBIENT, flash_light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, flash_light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, flash_light_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.00001);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1/0.017);
	
	float candle_light_ambient[] = { 0.7, 0.5, 0.1, 1.0 };
	float candle_light_diffuse[] = { 2.0, 1.4, 0.5, 1.0 };
	float candle_light_specular[] = { 1.0, 0.8, 0.3, 1.0 };
	
	// candle light settings
	glLightfv(GL_LIGHT3, GL_AMBIENT, candle_light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, candle_light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, candle_light_specular);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.2);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.01);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 89.99);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 120);	// uper limit of 120

	float party_light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	float party_light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float party_light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	
	// party light settings
	glLightfv(GL_LIGHT4, GL_AMBIENT, party_light_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, party_light_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, party_light_specular);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.01);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.01);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 10.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 100);
	
	// some scene options
	glShadeModel(GL_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void printScreen(int x, int y, float r, float g, float b, char *string)
{
	glLoadIdentity();
		glColor3f(r, g, b);
		glRasterPos3f(x, y, -1.0);
		int len, i;
		len = (int)strlen(string);
		for (i = 0; i < len; i++) {
			// glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
		}
}