#include "ft_fdf.h"

void round_one(t_fdf *sp)
{
    if (sp->line->x1 < sp->line->x0)
    {
        ft_swap(&sp->line->x0, &sp->line->x1);
        ft_swap(&sp->line->y0, &sp->line->y1);
    }
    sp->line->head->gradient = sp->line->head->dy / sp->line->head->dx;
    sp->line->head->xend = round(sp->line->x0);
    sp->line->head->yend = sp->line->y0 + sp->line->head->gradient * (sp->line->head->xend - sp->line->x0);
    sp->line->head->xgap = rfpart(sp->line->x0 + 0.5);
    sp->line->head->px1 = sp->line->head->xend;
    sp->line->head->py1 = ipart(sp->line->head->yend);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px1 + sp->line->c_x, sp->line->head->py1 + sp->line->c_y, 255);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px1 + sp->line->c_x, (sp->line->head->py1 + 1) + sp->line->c_y, 255);
    sp->line->head->intery = sp->line->head->yend + sp->line->head->gradient;
}

void round_two(t_fdf *sp)
{
    sp->line->head->xend = round(sp->line->x1);
    sp->line->head->yend = sp->line->y1 + sp->line->head->gradient * (sp->line->head->xend - sp->line->x1);
    sp->line->head->xgap = fpart(sp->line->x1 + 0.5);
    sp->line->head->px2 = sp->line->head->xend;
    sp->line->head->py2 = ipart(sp->line->head->yend);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px2 + sp->line->c_x, sp->line->head->py2 + sp->line->c_y, 255);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px2 + sp->line->c_x, (sp->line->head->py2 + 1) + sp->line->c_y, 255);
    int x = sp->line->head->px1;
    while (x < sp->line->head->px2)
    {
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, x + sp->line->c_x, ipart(sp->line->head->intery) + sp->line->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, x + sp->line->c_x, (ipart(sp->line->head->intery) + 1) + sp->line->c_y, 255);
        sp->line->head->intery += sp->line->head->gradient;
        x++;
    }
}

void round_three(t_fdf *sp)
{
    if (sp->line->y1 < sp->line->y0)
    {
        ft_swap(&sp->line->x0, &sp->line->x1);
        ft_swap(&sp->line->y0, &sp->line->y1);
    }
    sp->line->head->gradient = sp->line->head->dx / sp->line->head->dy;
    sp->line->head->yend = round(sp->line->y0);
    sp->line->head->xend = sp->line->x0 + sp->line->head->gradient * (sp->line->head->yend - sp->line->y0);
    sp->line->head->xgap = rfpart(sp->line->y0 + 0.5);
    sp->line->head->py1 = sp->line->head->yend;
    sp->line->head->px1 = ipart(sp->line->head->xend);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px1 + sp->line->c_x, sp->line->head->py1 + sp->line->c_y, 255);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (sp->line->head->px1 + 1) + sp->line->c_x, sp->line->head->py1 + sp->line->c_y, 255);
    sp->line->head->interx = sp->line->head->xend + sp->line->head->gradient;
}

void round_four(t_fdf *sp)
{
    sp->line->head->yend = round(sp->line->y1);
    sp->line->head->xend = sp->line->x1 + sp->line->head->gradient * (sp->line->head->yend - sp->line->y1);
    sp->line->head->xgap = fpart(sp->line->y1 + 0.5);
    sp->line->head->py2 = sp->line->head->yend;
    sp->line->head->px2 = ipart(sp->line->head->xend);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->line->head->px2 + sp->line->c_x, sp->line->head->py2 + sp->line->c_y, 255);
    mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (sp->line->head->px2 + 1) + sp->line->c_x, sp->line->head->py2 + sp->line->c_y, 255);
    int y = sp->line->head->py1;
    while (y < sp->line->head->py2)
    {
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, ipart(sp->line->head->interx) + sp->line->c_x, y + sp->line->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (ipart(sp->line->head->interx) + 1) + sp->line->c_x, y + sp->line->c_y, 255);
        sp->line->head->interx += sp->line->head->gradient;
        y++;
    }
}

void draw_line_antialias(t_fdf *sp)
{
    sp->line->head->dx = (double)sp->line->x1 - (double)sp->line->x0;
    sp->line->head->dy = (double)sp->line->y1 - (double)sp->line->y0;
    if (fabs(sp->line->head->dx) > fabs(sp->line->head->dy))
    {
        round_one(sp);
        round_two(sp);
    }
    else
    {
        round_three(sp);
        round_four(sp);
    }
}