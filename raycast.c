#include "cub3d.h"

void draw_line(mlx_image_t *image, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_put_pixel(image, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void clear_image(mlx_image_t *image)
{
    for (uint32_t y = 0; y < image->height; y++)
    {
        for (uint32_t x = 0; x < image->width; x++)
        {
            mlx_put_pixel(image, x, y, 0x00000000); // Transparent color
        }
    }
}

void draw_direction_line(mlx_image_t *image, float px, float py, float angle)
{
    float line_length = 50.0f; // Length of the line
    float end_x = px + cos(angle) * line_length;
    float end_y = py + sin(angle) * line_length;

    // Draw the line
    draw_line(image, (int)px, (int)py, (int)end_x, (int)end_y, 0x00FF00FF); // Green color
}

