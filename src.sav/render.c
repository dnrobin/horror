#include "shared.h"
#include "render.h"

// OOPS..........
#include "gamedefs.h"
#include "map_definitions.inc"
#include "game.h"
#include "timing.h"
#include "res.h"
#include "map.h"

#include "shader.h"

#include <stdlib.h>

#include <OpenGL/glu.h>

void init_render()
{
    
}

void display() 
{
	static float flare = 0.0;
	static float t = 0.0;
	t += getEllapsedSeconds(TIMER_LIGHT_ANIMATION);
	float twirl1 = sin(1*M_PI*t);
	float twirl2 = sin(2*M_PI*t);
	float twirl3 = sin(3*M_PI*t);
	flare = 0.1 * ( 7.0 + sin(.1*M_PI*t) + sin(3*M_PI*twirl1) + sin(.4*M_PI*t) + 2*sin(.7*M_PI*twirl3/3)*sin(.3*M_PI*t) );
	
	glClearAccum(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.05, 0.1, 0.4, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

	// /* MOVE ME AT SCREEN SPACE (ORTHO)! */
	// float FPS = 1.0 / getEllapsedSeconds(TIMER_FPS);
    // char buf[256];
 	// snprintf (buf, sizeof(buf), "FPS : %f", FPS);
    // // printScreen(10, 10, 1.0, 1.0, 1.0, buf);
	// /* MOVE ME AT SCREEN SPACE (ORTHO)! */

	glBlendFunc(GL_ONE, GL_ZERO);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glShadeModel(GL_FRONT_AND_BACK);
	glCullFace(GL_NONE);

	// get shader program handle
	uint prog = ((shader_t*)get_asset(MAP_ASSET_DEFAULT_SHADER)->obj)->gl_handle;

	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "albedo_map"), 0);
	glUniform1i(glGetUniformLocation(prog, "normal_map"), 1);
	glUniform1i(glGetUniformLocation(prog, "surface_map"), 2);

	
	int loc;

	mat4_t v;
	mat4_lookat_dir(v, g_camera->eye, g_camera->look, g_camera->up);
	loc = glGetUniformLocation(g_main_shader_program, "m_View");
	glUniformMatrix4fv(loc, 1, GL_FALSE, v);

	mat4_t p;
	mat4_perspective(p
		, g_window_width/(float)g_window_height
		, g_camera->yfov
		, g_camera->znear
		, g_camera->zfar);
	loc = glGetUniformLocation(g_main_shader_program, "m_Proj");
	glUniformMatrix4fv(loc, 1, GL_FALSE, p);

	mat4_t m;
	mat4_identity(m);
	loc = glGetUniformLocation(g_main_shader_program, "m_Model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, m);

	mat3_t n;
	mat3_mul_mat3(n, v, m);
	loc = glGetUniformLocation(g_main_shader_program, "m_NormalMatrix");
	glUniformMatrix3fv(loc, 1, GL_FALSE, n);

	mat4_print(p);
	mat4_print(v);
	mat4_print(m);
	mat3_print(n);

	// create light source to follow player around
	vec3_t light_pos;
	vec3(light_pos, -0.16, -0.02, -0.35);
	vec3_rotate(light_pos, light_pos, -0.5*g_camera->angles[0], -g_camera->angles[1], 0);
		if ( g_state[G_PLAYER_LOOK_BEHIND] ) {
			vec3_rotate(light_pos, light_pos,
        		-g_camera->angles[0],
        		-g_camera->angles[1],
        		-g_camera->angles[2]);
        }
	float light_position[] = { 
		g_camera->eye[0] + light_pos[0],
		g_camera->eye[1] + light_pos[1] - 0.3*g_camera->angles[0],
		g_camera->eye[2] + light_pos[2],
		1.0 };

	float light_direction[] = { g_camera->look[0], g_camera->look[1], g_camera->look[2], 1.0 };
	    if ( g_state[G_PLAYER_LOOK_BEHIND] ) {
        	vec3_rotate(light_direction, light_direction,
        		-g_camera->angles[0],
        		-g_camera->angles[1],
        		-g_camera->angles[2]);
        }

	// flash light settings
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1/0.017 + 1/0.2 * flare);
	
	// candle light settings
	glLightfv(GL_LIGHT3, GL_POSITION, light_position);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.005*(flare-0.5));
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1.6*flare);

	// party light settings
	float party_light_color11[] = { 0.82, 0.0, 0.73 };
	float party_light_color21[] = { 1.0, 0.0, 1.0 };
	float light_position2[] = { -9.0, 0.0, -11.0 };
	glLightfv(GL_LIGHT7, GL_AMBIENT, party_light_color11);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, party_light_color11);
	glLightfv(GL_LIGHT7, GL_SPECULAR, party_light_color21);
	glLightfv(GL_LIGHT7, GL_POSITION, light_position2);
	
	// terror light settings
	float party_direction[] = { sin(2*M_PI*t), -sin(2*M_PI*twirl1), cos(2*M_PI*t*flare) };
	float party_light_color1[] = { 0.5 + twirl1 / 4.0, 0.5 + twirl3 / 4.0, 0.5 + twirl2 / 4.0, 1.0 };
	float party_light_color2[] = { 0.5 - twirl1 / 4.0, 0.5 - twirl3 / 4.0, 0.5 - twirl2 / 4.0, 1.0 };
	float party_light_color3[] = { 0.5 + twirl1 / 3.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT4, GL_AMBIENT, party_light_color3);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, party_light_color1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, party_light_color3);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, party_direction);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.6*(0.5 + twirl1/2.0));
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 40.0 + 10.0*(0.5 + twirl1/2.0));
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 0.1);
	
	// create light source for goal
	float light2_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	float light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float light2_position[] = { 1.0, 1.0, -7.0 };
	float light2_spot_direction[] = { 0.0, -1.0, 0.0 };
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.05);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.001);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1/0.017);
	
	// create light to greet death zone
	float light5_ambient[] = { 1.0, 0.1, 0.0, 1.0 };
	float light5_diffuse[] = { 1.0, 0.4, 0.0, 1.0 };
	float light5_specular[] = { 1.0, 1.0, 0.0, 1.0 };
	float light5_position[] = { -4.0, 1.0, -14.0 };
	float light5_spot_direction[] = { 0.0, -1.0, 0.0 };
	glEnable(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, light5_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light5_diffuse);
	glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.08);
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.01);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light2_spot_direction);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 1/0.17);
	
	// draw the goal: a teapot!
    glPushMatrix();
    	glColor3f(1,0,0);
        glTranslatef(8.5, -0.3, 16.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
        // glutSolidTeapot(0.2);
    glPopMatrix();
	

	// activate/deactivate player light
	if (0) {
		if ( g_state[G_HAS_FLASH_LIGHT] && g_state[G_WITH_FLASH_LIGHT] && g_state[G_PLAYER_LIGHT_ON] ) {
			glEnable(GL_LIGHT1);
		} else {
			glDisable(GL_LIGHT1);
		}
		if ( !g_state[G_DEATH_ZONE] && g_state[G_HAS_CANDLE] && g_state[G_WITH_CANDLE] && g_state[G_PLAYER_LIGHT_ON] ) {
			glEnable(GL_LIGHT3);
		} else {
			glDisable(GL_LIGHT3);
		}
		if ( g_state[G_PARTY_LIGHT_ON] ) {
			glEnable(GL_LIGHT4);
		} else {
			glDisable(GL_LIGHT4);
		}
	}
	
	// DEADZONE HAS RED FOG
	if ( g_state[G_DEATH_ZONE] ) {
		float fogColor[] = {0.3, 0.01, 0.06, 1.0};
		glFogfv(GL_FOG_COLOR, fogColor);
	} else {
		float fogColor[] = {0.05, 0.1, 0.4, 1.0};
		glFogfv(GL_FOG_COLOR, fogColor);
	}
	
	// ADD CAMERA TRACKBALL FOR DEBUG
	if ( g_state[G_DEBUG_CAMERA] ) {
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-15.0, 0.0, 1.0, 0.0);
		glTranslatef(-0.1, -0.05, -0.2);
		glScalef(0.02, 0.02, 0.02);
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(1.0, 0.0, 0.0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 1.0, 0.0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 1.0);
		glEnd();
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(g_camera->look[0], g_camera->look[1], g_camera->look[2]);
		glEnd();
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(g_camera->up[0], g_camera->up[1], g_camera->up[2]);
		glEnd();
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(g_camera->right[0], g_camera->right[1], g_camera->right[2]);
		glEnd();
		glPopMatrix();
	}

	/* Player vision animated overlays */
	static bool just_turned_off_lights = false;
	static float a, b, vision_adapt_amount;
    float vision_decay_amount = (g_player_stress_level/10.0)*(1.0 + 0.2*sin(2*M_PI*t));
	float alpha = 0.25*(1 - exp(-(g_player_stress_level/3.0)*(g_player_stress_level/3.0)));

	/**** THIS SECTION IS SCREEN SPACE EFFECTS -- ORTHO *****/

	// Noise in the vision
	if (0) {
		glPushMatrix();
		glLoadIdentity();
			glDisable(GL_LIGHTING);
			glScalef(0.138, 0.098, 1.0);
			glTranslatef(0.0, 0.0, -0.14);
			glBindTexture(GL_TEXTURE_2D, 6);
			glColor4f(0.5 * (1.0+vision_decay_amount), 0.2, 0.2, alpha); //vision_decay_amount
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-1.0, -1.0, 0);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(1.0, -1.0, 0);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(1.0, 1.0, 0);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-1.0, 1.0, 0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

    //Vision perturbations in relation to fear level
	if (0) {
		glPushMatrix();
		glLoadIdentity();
			glScalef(0.134, 0.092, 1.0);
			glTranslatef(0.0, 0.0, -0.13);
			glBindTexture(GL_TEXTURE_2D, 4);
			glColor4f(0.9 * (1.0+vision_decay_amount), 0.2, 0.2, vision_decay_amount);
			glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-1.0, -1.0, 0);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(1.0, -1.0, 0);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(1.0, 1.0, 0);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-1.0, 1.0, 0);
			glEnd();
		glPopMatrix();
	}

    // Adaptive night vision 
    // if ( !g_state[G_PLAYER_LIGHT_ON] ) {
    // 	GLfloat dhg[3] = {0.13, 0.13, 0.13};
	//     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, dhg);
	//     glColor4f(0.0, 0.0, 0.0, g_vision_adapt_factor);
    //    	glBlendFunc(GL_ONE, GL_SRC_ALPHA);

    //     if ( !just_turned_off_lights ) {
    //         just_turned_off_lights = true;
    //         a = t; b = 0.0;
    //     }
    //     b = t - a; g_vision_adapt_factor = 1.0 - exp(-0.5*b*b);
    //     if ( g_vision_adapt_factor > 0.9991 ) g_vision_adapt_factor = 1.0;

    // } else {
	//     glColor4f(0.8, 0.89, 0.5, g_vision_adapt_factor);
    //    	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // 	if ( just_turned_off_lights ) {
    //         just_turned_off_lights = false;
    //         a = t; b = 0.0;
    //     }
    //     b = t - a; g_vision_adapt_factor = exp(-12*b*b) * 0.8;
    //     if ( g_vision_adapt_factor < 0.0001 ) g_vision_adapt_factor = 0.0;
    // }

    // Vision adapt
	if (0) {
		glPushMatrix();
			glLoadIdentity();
			glDisable(GL_LIGHTING);
			glScalef(0.134, 0.092, 1.0);
			glTranslatef(0.0, 0.0, -0.12);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-1.0, -1.0, 0);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(1.0, -1.0, 0);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(1.0, 1.0, 0);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-1.0, 1.0, 0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

    // High contrast effect
	if (0) {
		glPushMatrix();
		glLoadIdentity();
			glDisable(GL_LIGHTING);
			glScalef(0.134, 0.092, 1.0);
			glTranslatef(0.0, 0.0, -0.11);
			glBindTexture(GL_TEXTURE_2D, 0);
			glColor4f(0.5, 0.5, 0.5, 0.0);
			glBlendFunc(GL_DST_COLOR, GL_DST_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(-1.0, -1.0, 0);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(1.0, -1.0, 0);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(1.0, 1.0, 0);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(-1.0, 1.0, 0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	if ( g_state[G_SHOW_WIREFRAME] ) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glCallList(GL_LIST_ID_MAP);
}