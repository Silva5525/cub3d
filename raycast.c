#include "cub3d.h"

int	step_calc(int temp1, int temp2);

void raycast(t_c *cub)
{
	int r, mx, my, dof;
	float rx, ry, ra, xo, yo;
	ra = cub->player.angle;
	r = 0;
	while(r < 1)
	{
		dof = 0;
		float aTan = -1/tan(ra);
		if (ra > PI) //looking up
		{
			ry = ((((int)cub->player.pos.y) >> 6) << 6) - 0.0001;
			rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) //looking down
		{
			ry = ((((int)cub->player.pos.y) << 6) << 6) + 64;
			rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
			yo = 64;
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
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < cub->map_width && my >= 0 && my < cub->map_height && cub->map[my][mx] == '1') //ray hit wall
			{
				dof = 8;
			}
			else //next line
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		draw_line_dda(cub->ray_img, cub->player.pos.x, cub->player.pos.y, rx , ry , 0x00FF00FF);
		r++;
	}
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