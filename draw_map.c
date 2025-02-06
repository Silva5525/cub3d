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
                color = 0x0000FFFF;
			else if (cub->map[y][x] == ' ')
                color = 0xFF000000;
            else
				color = 0x7F7F7FFF;
            //Draw map
            tx = 0;
            while (tx < TILE_SIZE)
            {
                ty = 0;
                while (ty < TILE_SIZE)
                {
                    mlx_put_pixel(cub->img, x * TILE_SIZE + tx, y * TILE_SIZE + ty, color);
                    ty++;
                    if (ty == TILE_SIZE || tx == 0)
                        mlx_put_pixel(cub->img, x * TILE_SIZE + tx, y * TILE_SIZE + ty - 1, 0xFFFFFF00);
                }
                tx++;
            }
            x++;
        }
        y++;
    }
}
