#include "ft_fdf.h"

#define ipart_(X) ((int)(X))
#define round_(X) ((int)(((double)(X)) + 0.5))
#define fpart_(X) (((double)(X)) - (double)ipart_(X))
#define rfpart_(X) (1.0 - fpart_(X))

void draw_line_antialias(t_fdf *sp)
{
    //   unsigned int x1, unsigned int y1,
    //   unsigned int x2, unsigned int y2,
    double dx = (double)sp->x1 - (double)sp->x0;
    double dy = (double)sp->y1 - (double)sp->y0;
    if (fabs(dx) > fabs(dy))
    {
        if (sp->x1 < sp->x0)
        {
            ft_swap(&sp->x0, &sp->x1);
            ft_swap(&sp->y0, &sp->y1);
        }
        double gradient = dy / dx;
        double xend = round_(sp->x0);
        double yend = sp->y0 + gradient * (xend - sp->x0);
        double xgap = rfpart_(sp->x0 + 0.5);
        int xpxl1 = xend;
        int ypxl1 = ipart_(yend);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl1 + sp->c_x, ypxl1 + sp->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl1 + sp->c_x, (ypxl1 + 1) + sp->c_y, 255);
        // plot_(xpxl1, ypxl1, rfpart_(yend) * xgap);
        // plot_(xpxl1, ypxl1 + 1, fpart_(yend) * xgap);
        double intery = yend + gradient;

        xend = round_(sp->x1);
        yend = sp->y1 + gradient * (xend - sp->x1);
        xgap = fpart_(sp->x1 + 0.5);
        int xpxl2 = xend;
        int ypxl2 = ipart_(yend);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl2 + sp->c_x, ypxl2 + sp->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl2 + sp->c_x, (ypxl2 + 1) + sp->c_y, 255);
        // plot_(xpxl2, ypxl2, rfpart_(yend) * xgap);
        // plot_(xpxl2, ypxl2 + 1, fpart_(yend) * xgap);

        int x;
        for (x = xpxl1 + 1; x < xpxl2; x++)
        {
            // plot_(x, ipart_(intery), rfpart_(intery));
            // plot_(x, ipart_(intery) + 1, fpart_(intery));
            mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, x + sp->c_x, ipart_(intery) + sp->c_y, 255);
            mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, x + sp->c_x, (ipart_(intery) + 1) + sp->c_y, 255);
            intery += gradient;
        }
    }
    else
    {
        if (sp->y1 < sp->y0)
        {
            ft_swap(&sp->x0, &sp->x1);
            ft_swap(&sp->y0, &sp->y1);
        }
        double gradient = dx / dy;
        double yend = round_(sp->y0);
        double xend = sp->x0 + gradient * (yend - sp->y0);
        double ygap = rfpart_(sp->y0 + 0.5);
        int ypxl1 = yend;
        int xpxl1 = ipart_(xend);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl1 + sp->c_x, ypxl1 + sp->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (xpxl1 + 1) + sp->c_x, ypxl1 + sp->c_y, 255);
        // plot_(xpxl1, ypxl1, rfpart_(xend) * ygap);
        // plot_(xpxl1 + 1, ypxl1, fpart_(xend) * ygap);
        double interx = xend + gradient;

        yend = round_(sp->y1);
        xend = sp->x1 + gradient * (yend - sp->y1);
        ygap = fpart_(sp->y1 + 0.5);
        int ypxl2 = yend;
        int xpxl2 = ipart_(xend);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, xpxl2 + sp->c_x, ypxl2 + sp->c_y, 255);
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (xpxl2 + 1) + sp->c_x, ypxl2 + sp->c_y, 255);
        // plot_(xpxl2, ypxl2, rfpart_(xend) * ygap);
        // plot_(xpxl2 + 1, ypxl2, fpart_(xend) * ygap);

        int y;
        for (y = ypxl1 + 1; y < ypxl2; y++)
        {
            mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, ipart_(interx) + sp->c_x, y + sp->c_y, 255);
            mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, (ipart_(interx) + 1) + sp->c_x, y + sp->c_y, 255);
            // plot_(ipart_(interx), y, rfpart_(interx));
            // plot_(ipart_(interx) + 1, y, fpart_(interx));
            interx += gradient;
        }
    }
}