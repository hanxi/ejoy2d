#include "screen.h"
#include "opengl.h"
#include "spritepack.h"

struct screen {
	int width;
	int height;
	int scale;
	float invw;
	float invh;
};

static struct screen SCREEN;

void
screen_init(float w, float h, float scale) {
	SCREEN.width = (int)w;
	SCREEN.height = (int)h;
	SCREEN.scale = (int)scale;
	SCREEN.invw = 2.0f / SCREEN_SCALE / w;
	SCREEN.invh = -2.0f / SCREEN_SCALE / h;
	glViewport(0,0,w * scale,h * scale);
}

void
screen_trans(float *x, float *y) {
	*x *= SCREEN.invw;
	*y *= SCREEN.invh;
}

void
screen_scissor(int x, int y, int w, int h) {
	y = SCREEN.height - y - h;
	if (x<0) {
		x = 0;
	} else if (x>SCREEN.width) {
		x = SCREEN.width;
	}
	if (y<0) {
		y = 0;
	} else if (y>SCREEN.height) {
		y = SCREEN.height;
	}
	x *= SCREEN.scale;
	y *= SCREEN.scale;
	w *= SCREEN.scale;
	h *= SCREEN.scale;

	glScissor(x,y,w,h);
}


