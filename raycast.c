#include "cub3d.h"

float	distance(float x1, float y1, float x2, float y2);

void raycast(t_c *cub)
{
	int r, mx, my, dof;
	float rx, ry, ra, xo, yo;
	ra = cub->player.angle;
	r = 0;
	float distanceH = 1000000;
	float hx = cub->player.pos.x;
	float hy = cub->player.pos.y;
	while(r < 1)
	{
		dof = 0;
		float aTan = -1/tan(ra);
		if (ra > PI) //looking up
		{
			ry = ((((int)cub->player.pos.y) >> 5) << 5) - 0.0001; //shifting by 5, dividing or multyplying by 32
			rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
			yo = -TILE_SIZE;
			xo = -yo * aTan;
		}
		if (ra < PI) //looking down
		{
			ry = ((((int)cub->player.pos.y) >> 5) << 5) + 32;
			rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
			yo = TILE_SIZE;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) //looking straight left or right
		{
			rx = cub->player.pos.x;
			ry = cub->player.pos.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 5;
			my = (int)(ry) >> 5;
			if (mx >= 0 && mx < cub->map_width && my >= 0 && my < cub->map_height && cub->map[my][mx] == '1') //ray hit wall
			{
				hx = rx;
				hy = ry;
				distanceH = distance(cub->player.pos.x, cub->player.pos.y, hx, hy);
				dof = 8;
			}
			else //next line
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		dof = 0;
		float distanceV = 1000000;
		float vx = cub->player.pos.x;
		float vy = cub->player.pos.y;
		float nTan = -tan(ra);
		if (ra > (PI / 2) && ra < (3 * PI / 2)) //looking left
		{
			rx = ((((int)cub->player.pos.x) >> 5) << 5) - 0.0001; //shifting by 5, dividing or multyplying by 32
			ry = (cub->player.pos.x - rx) * nTan + cub->player.pos.y;
			xo = -TILE_SIZE;
			yo = -xo * nTan;
		}
		if (ra < (PI / 2) || ra > (3 * PI / 2)) //looking right
		{
			rx = ((((int)cub->player.pos.x) >> 5) << 5) + 32;
			ry = (cub->player.pos.x - rx) * nTan + cub->player.pos.y;
			xo = TILE_SIZE;
			yo = -xo * nTan;
		}
		if (ra == (PI / 2) || ra == (3 * PI/ 2)) //looking straight up or down
		{
			rx = cub->player.pos.x;
			ry = cub->player.pos.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 5;
			my = (int)(ry) >> 5;
			if (mx >= 0 && mx < cub->map_width && my >= 0 && my < cub->map_height && cub->map[my][mx] == '1') //ray hit wall
			{
				vx = rx;
				vy = ry;
				distanceV = distance(cub->player.pos.x, cub->player.pos.y, vx, vy);
				dof = 8;
			}
			else //next line
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (distanceV < distanceH)
		{
			rx = vx;
			ry = vy;
		}
		if (distanceV > distanceH)
		{
			rx = hx;
			ry = hy;
		}
		draw_line_dda(cub->ray_img, cub->player.pos.x, cub->player.pos.y, rx, ry, 0x00FF00FF);
		r++;
	}
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void draw_line_dda(mlx_image_t *ray_img, float x0, float y0, float x1, float y1, uint32_t color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; i++) {
        mlx_put_pixel(ray_img, (int)round(x), (int)round(y), color);
        x += x_inc;
        y += y_inc;
    }
}