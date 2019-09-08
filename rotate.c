#include "ft_fdf.h"

void handle_x(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 15;
    sp->x1 = (x + 1) * 15;
    sp->y0 = y * 15;
    sp->y1 = y * 15;
    sp->z0 = sp->real[y][x] * 15;
    sp->z1 = sp->real[y][x + 1] * 15;
    rot_x(sp);
    rot_y(sp);
    rot_z(sp);
    draw_line_antialias(sp);
}

void handle_y(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 15;
    sp->x1 = x * 15;
    sp->y0 = y * 15;
    sp->y1 = (y + 1) * 15;
    sp->z0 = sp->real[y][x] * 15;
    sp->z1 = sp->real[y + 1][x] * 15;
    rot_x(sp);
    rot_y(sp);
    rot_z(sp);
    draw_line_antialias(sp);
}

void rot_x(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->x0;
    y = sp->y0;
    z = sp->z0;
    sp->y0 = ((y * cos(sp->a)) + (z * sin(sp->a)));
    sp->z0 = (((-1 * (y * sin(sp->a))) + (z * cos(sp->a))));
    x = sp->x1;
    y = sp->y1;
    z = sp->z1;
    sp->y1 = ((y * cos(sp->a)) + (z * sin(sp->a)));
    sp->z1 = (((-1 * (y * sin(sp->a))) + (z * cos(sp->a))));
}

void rot_y(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->x0;
    y = sp->y0;
    z = sp->z0;
    sp->x0 = ((x * cos(sp->b)) + (z * sin(sp->b)));
    sp->z0 = (((-1 * (x * sin(sp->b))) + (z * cos(sp->b))));
    x = sp->x1;
    y = sp->y1;
    z = sp->z1;
    sp->x1 = ((x * cos(sp->b) + (z * sin(sp->b))));
    sp->z1 = ((-1 * (x * sin(sp->b))) + (z * cos(sp->b)));
}
void rot_z(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->x0;
    y = sp->y0;
    z = sp->z0;
    sp->x0 = ((x * cos(0)) - (y * sin(0)));
    sp->y0 = ((x * sin(0)) + (y * cos(0)));
    x = sp->x1;
    y = sp->y1;
    z = sp->z1;
    sp->x1 = ((x * cos(0)) - (y * sin(0)));
    sp->y1 = ((x * sin(0)) + (y * cos(0)));
}