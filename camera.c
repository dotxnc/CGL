#include "camera.h"

void cgl_InitCamera(Camera* cam, float x, float y, float z)
{
	cam->pos[0] = x;
	cam->pos[1] = y;
	cam->pos[2] = z;

	cam->front[0] = 0.0;
	cam->front[1] = 0.0;
	cam->front[2] = -1.0;

	cam->up[0] = 0.0;
	cam->up[1] = 1.0;
	cam->up[2] = 0.0;
}
