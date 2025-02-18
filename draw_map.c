#include "cub3d.h"

void draw_map2D(t_c *cub)
{
    int x;
    int y;
    int tx;
    int ty;
    uint32_t color;

    x = 0;
    y = 0;
    ty = 0;
    while (cub->map[y] != NULL)
    {
        x = 0;
        while (cub->map[y][x] != '\0')
        {
            //Set Color
            if (cub->map[y][x] == '1')
                color = 0x0000009E;
            else
                color = 0x80809E9E;
			
            //color = 0x7F7F7FFF;
            //Draw map
            tx = 0;
            while (tx < TILE_SIZE)
            {
                ty = 0;
                while (ty < TILE_SIZE)
                {
                    mlx_put_pixel(cub->mini_map, x * TILE_SIZE + tx, y * TILE_SIZE + ty, color);
                    ty++;
                }
                tx++;
            }
            x++;
        }
        y++;
    }
}

void    draw_floor_and_ceiling(t_c *cub)
{
    int x;
    int y;

    y = 0;
    while (y < (HEIGHT / 2))
    {
        x = 0;
        while (x <= WIDTH)
        {
            //mlx_put_pixel(cub->window, x, y, cub->roof);
            mlx_put_pixel(cub->img, x, y, 0x7F7FFFFF);
            x++;
        }
        y++;
    }
    while (y < HEIGHT)
    {
        x = 0;
        while (x <= WIDTH)
        {
            //mlx_put_pixel(cub->window, x, y, cub->floor);
            mlx_put_pixel(cub->img, x, y, 0xA55A2AFF);
            x++;
        }
        y++;
    }
}
