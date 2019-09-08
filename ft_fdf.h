#ifndef FT_FDF_H
#define FT_FDF_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "./Minilibx/mlx.h"
#include "libft/libft.h"

#define ALP sp->a

typedef struct s_head
{
    void *ptr;
    void *window;
} t_head;

typedef struct s_fdf
{
    t_head *mlx;
    int **real;
    char *hold;
    struct stat *buf;
    int max_x;
    int max_y;
    int c_x;
    int c_y;
    int x0;
    int x1;
    int y0;
    int y1;
    int z0;
    int z1;
    double a;
    double b;
} t_fdf;

void draw_line_antialias(t_fdf *sp);
typedef void t_shift(t_fdf *sp);
// static void draw_line(t_fdf *sp);

#endif