#include "ft_fdf.h"

void handle_x(t_fdf *sp, int x, int y)
{
    sp->line->x0 = x * 15;
    sp->line->x1 = (x + 1) * 15;
    sp->line->y0 = y * 15;
    sp->line->y1 = y * 15;
    sp->line->z0 = sp->real[y][x] * 15;
    sp->line->z1 = sp->real[y][x + 1] * 15;
    rot_x(sp);
    rot_y(sp);
    rot_z(sp);
    draw_line_antialias(sp);
}

void handle_y(t_fdf *sp, int x, int y)
{
    sp->line->x0 = x * 15;
    sp->line->x1 = x * 15;
    sp->line->y0 = y * 15;
    sp->line->y1 = (y + 1) * 15;
    sp->line->z0 = sp->real[y][x] * 15;
    sp->line->z1 = sp->real[y + 1][x] * 15;
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

    x = sp->line->x0;
    y = sp->line->y0;
    z = sp->line->z0;
    sp->line->y0 = ((y * cos(sp->line->a)) + (z * sin(sp->line->a)));
    sp->line->z0 = (((-1 * (y * sin(sp->line->a))) + (z * cos(sp->line->a))));
    x = sp->line->x1;
    y = sp->line->y1;
    z = sp->line->z1;
    sp->line->y1 = ((y * cos(sp->line->a)) + (z * sin(sp->line->a)));
    sp->line->z1 = (((-1 * (y * sin(sp->line->a))) + (z * cos(sp->line->a))));
}

void rot_y(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->line->x0;
    y = sp->line->y0;
    z = sp->line->z0;
    sp->line->x0 = ((x * cos(sp->line->b)) + (z * sin(sp->line->b)));
    sp->line->z0 = (((-1 * (x * sin(sp->line->b))) + (z * cos(sp->line->b))));
    x = sp->line->x1;
    y = sp->line->y1;
    z = sp->line->z1;
    sp->line->x1 = ((x * cos(sp->line->b) + (z * sin(sp->line->b))));
    sp->line->z1 = ((-1 * (x * sin(sp->line->b))) + (z * cos(sp->line->b)));
}
void rot_z(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->line->x0;
    y = sp->line->y0;
    z = sp->line->z0;
    sp->line->x0 = ((x * cos(0)) - (y * sin(0)));
    sp->line->y0 = ((x * sin(0)) + (y * cos(0)));
    x = sp->line->x1;
    y = sp->line->y1;
    z = sp->line->z1;
    sp->line->x1 = ((x * cos(0)) - (y * sin(0)));
    sp->line->y1 = ((x * sin(0)) + (y * cos(0)));
}