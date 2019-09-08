#include "ft_fdf.h"

void handle_rotate(t_fdf *sp)
{
    sp->line->y0 = ((sp->line->y0 * cos(sp->line->a)) + (sp->line->z0 * sin(sp->line->a)));
    sp->line->z0 = (((-1 * (sp->line->y0 * sin(sp->line->a))) + (sp->line->z0 * cos(sp->line->a))));
    sp->line->y1 = ((sp->line->y1 * cos(sp->line->a)) + (sp->line->z1 * sin(sp->line->a)));
    sp->line->z1 = (((-1 * (sp->line->y1 * sin(sp->line->a))) + (sp->line->z1 * cos(sp->line->a))));
    sp->line->x0 = ((sp->line->x0 * cos(sp->line->b)) + (sp->line->z0 * sin(sp->line->b)));
    sp->line->z0 = (((-1 * (sp->line->x0 * sin(sp->line->b))) + (sp->line->z0 * cos(sp->line->b))));
    sp->line->x1 = ((sp->line->x1 * cos(sp->line->b) + (sp->line->z1 * sin(sp->line->b))));
    sp->line->z1 = ((-1 * (sp->line->x1 * sin(sp->line->b))) + (sp->line->z1 * cos(sp->line->b)));
    sp->line->x0 = ((sp->line->x0 * cos(0)) - (sp->line->y0 * sin(0)));
    sp->line->y0 = ((sp->line->x0 * sin(0)) + (sp->line->y0 * cos(0)));
    sp->line->x1 = ((sp->line->x1 * cos(0)) - (sp->line->y1 * sin(0)));
    sp->line->y1 = ((sp->line->x1 * sin(0)) + (sp->line->y1 * cos(0)));
}

void handle_x(t_fdf *sp, int x, int y)
{
    sp->line->x0 = x * sp->line->scale;
    sp->line->x1 = (x + 1) * sp->line->scale;
    sp->line->y0 = y * sp->line->scale;
    sp->line->y1 = y * sp->line->scale;
    sp->line->z0 = sp->real[y][x] * sp->line->scale;
    sp->line->z1 = sp->real[y][x + 1] * sp->line->scale;
    handle_rotate(sp);
    draw_line_antialias(sp);
}

void handle_y(t_fdf *sp, int x, int y)
{
    sp->line->x0 = x * sp->line->scale;
    sp->line->x1 = x * sp->line->scale;
    sp->line->y0 = y * sp->line->scale;
    sp->line->y1 = (y + 1) * sp->line->scale;
    sp->line->z0 = sp->real[y][x] * sp->line->scale;
    sp->line->z1 = sp->real[y + 1][x] * sp->line->scale;
    handle_rotate(sp);
    draw_line_antialias(sp);
}