#include "cub3d.h"

float	distance(float x1, float y1, float x2, float y2);
static void	check_horizontal_hit(t_c *cub, float ra, float *hx, float *hy, float *distanceH);
static void	check_vertical_hit(t_c *cub, float ra, float *vx, float *vy, float *distanceV);

/**
 * Renders the rays for the field of view (FOV).
 * Each ray is calculated per screen pixel using angle increments.
 */
void	raycast(t_c *cub)
{
	int		r;
	float	ra;
	float	angle_increment;
	float	hx, hy, vx, vy;
	float	distanceH, distanceV;

	// Angle increment: FOV divided by screen width
	angle_increment = (60 * DEGREE) / WIDTH;

	// Start angle: player angle minus half FOV
	ra = cub->player.angle - (30 * DEGREE);
	r = 0;
	while (r < WIDTH)
	{
		// Normalize angle within [0, 2PI]
		while (ra < 0)
			ra += 2 * PI;
		while (ra > 2 * PI)
			ra -= 2 * PI;

		// Check horizontal intersections
		check_horizontal_hit(cub, ra, &hx, &hy, &distanceH);

		// Check vertical intersections
		check_vertical_hit(cub, ra, &vx, &vy, &distanceV);

		// Determine which intersection is closer and draw the ray
		if (distanceV < distanceH)
		{
			draw_line_dda(cub->ray_img, cub->player.pos.x, cub->player.pos.y, vx, vy, 0x00FF00FF);
			distanceV *= cos(cub->player.angle - ra);
			draw_3d(cub, r, distanceV);
		}
		else
		{
			draw_line_dda(cub->ray_img, cub->player.pos.x, cub->player.pos.y, hx, hy, 0x00FF00FF);
			distanceH *= cos(cub->player.angle - ra);
			draw_3d(cub, r, distanceH);
		}

		// Increment angle for next ray
		ra += angle_increment;
		r++;
	}
}

/**
 * Finds the closest horizontal wall intersection for a ray.
 */
static void	check_horizontal_hit(t_c *cub, float ra, float *hx, float *hy, float *distanceH)
{
	int		dof;
	float	rx, ry, xo, yo;
	float	aTan;

	aTan = -1 / tan(ra);
	*distanceH = 1000000;
	*hx = cub->player.pos.x;
	*hy = cub->player.pos.y;

	// Calculate first horizontal intersection
	if (ra > PI) // Looking Up
	{
		ry = (((int)cub->player.pos.y >> 5) << 5) - 0.0001;
		rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
		yo = -TILE_SIZE;
		xo = -yo * aTan;
	}
	else if (ra < PI) // Looking Down
	{
		ry = (((int)cub->player.pos.y >> 5) << 5) + TILE_SIZE;
		rx = (cub->player.pos.y - ry) * aTan + cub->player.pos.x;
		yo = TILE_SIZE;
		xo = -yo * aTan;
	}
	else // Looking Straight Left/Right
	{
		rx = cub->player.pos.x;
		ry = cub->player.pos.y;
		return;
	}

	// Cast horizontal ray until wall hit
	dof = 0;
	while (dof < 8)
	{
		int mx = (int)(rx) >> 5;
		int my = (int)(ry) >> 5;
		if (mx >= 0 && mx < cub->map_width && my >= 0 && my < cub->map_height &&
			cub->map[my][mx] == '1')
		{
			*hx = rx;
			*hy = ry;
			*distanceH = distance(cub->player.pos.x, cub->player.pos.y, rx, ry);
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}

/**
 * Finds the closest vertical wall intersection for a ray.
 */
static void	check_vertical_hit(t_c *cub, float ra, float *vx, float *vy, float *distanceV)
{
	int		dof;
	float	rx, ry, xo, yo;
	float	nTan;

	nTan = -tan(ra);
	*distanceV = 1000000;
	*vx = cub->player.pos.x;
	*vy = cub->player.pos.y;

	// Calculate first vertical intersection
	if (ra > (PI / 2) && ra < (3 * PI / 2)) // Looking Left
	{
		rx = (((int)cub->player.pos.x >> 5) << 5) - 0.0001;
		ry = (cub->player.pos.x - rx) * nTan + cub->player.pos.y;
		xo = -TILE_SIZE;
		yo = -xo * nTan;
	}
	else if (ra < (PI / 2) || ra > (3 * PI / 2)) // Looking Right
	{
		rx = (((int)cub->player.pos.x >> 5) << 5) + TILE_SIZE;
		ry = (cub->player.pos.x - rx) * nTan + cub->player.pos.y;
		xo = TILE_SIZE;
		yo = -xo * nTan;
	}
	else // Looking Straight Up/Down
	{
		rx = cub->player.pos.x;
		ry = cub->player.pos.y;
		return;
	}

	// Cast vertical ray until wall hit
	dof = 0;
	while (dof < 8)
	{
		int mx = (int)(rx) >> 5;
		int my = (int)(ry) >> 5;
		if (mx >= 0 && mx < cub->map_width && my >= 0 && my < cub->map_height &&
			cub->map[my][mx] == '1')
		{
			*vx = rx;
			*vy = ry;
			*distanceV = distance(cub->player.pos.x, cub->player.pos.y, rx, ry);
			break;
		}
		rx += xo;
		ry += yo;
		dof++;
	}
}

/**
 * Calculates distance between two points using Pythagorean theorem.
 */
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

bool	collision(t_c *cub, float x, float y)
{
	int mapX = (int)(x / TILE_SIZE);
	int mapY = (int)(y / TILE_SIZE);
	//printf("Checking collision at: x=%f, y=%f\n", x, y);
	// Safety check for map boundaries
	if (mapX < 0 || mapY < 0 ||
		mapX >= cub->map_width ||
		mapY >= cub->map_height)
	{
		printf("Collision: Out of map bounds at (%d, %d)\n", mapX, mapY);
		return (true);
	}

	// Check four corners for wall collision
	if (is_wall(cub, x -(PLAYER_SIZE / 2), y - (PLAYER_SIZE / 2)) ||
		is_wall(cub, x + (PLAYER_SIZE / 2), y - (PLAYER_SIZE / 2)) ||
		is_wall(cub, x - (PLAYER_SIZE / 2), y + (PLAYER_SIZE / 2)) ||
		is_wall(cub, x + (PLAYER_SIZE / 2), y + (PLAYER_SIZE / 2)))
	{
		printf("Collision with wall detected!\n");
		return (true);
	}
	return (false);
}

bool	is_wall(t_c *cub, float x, float y)
{
	int mapX = (int)(x / TILE_SIZE);
	int mapY = (int)(y / TILE_SIZE);
	// Validate map bounds to avoid segfault
	if (mapX < 0 || mapY < 0 ||
		mapX >= cub->map_width ||
		mapY >= cub->map_height)
	{
		return (true); // Out of bounds = treat as wall
	}

	return (cub->map[mapY][mapX] == '1');
}

void	draw_3d(t_c *cub, int x, float final_dist)
{
	float	line_height;
	float	draw_start;
	float	draw_end;

	// Projected wall height (Inverse proportional to distance)
	line_height = (TILE_SIZE * HEIGHT) / final_dist;
	draw_start = (HEIGHT / 2) - (line_height / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (HEIGHT / 2) + (line_height / 2);
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

 	// Draw Ceiling
	//for (int y = 0; y < draw_start; y++)
	//	mlx_put_pixel(cub->world_img, x, y, cub->roof);

	// Draw Wall (Currently solid color, can add textures later)
	for (int y = draw_start; y < draw_end; y++)
		mlx_put_pixel(cub->world_img, x, y, 0xFF0000FF); // Red walls

	// Draw Floor
	//for (int y = draw_end; y < HEIGHT; y++)
	//	mlx_put_pixel(cub->world_img, x, y, 0xFF00FFFF);
}