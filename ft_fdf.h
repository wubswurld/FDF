#ifndef FT_FDF_H
#define FT_FDF_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "./Minilibx/mlx.h"
#include "libft/libft.h"

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

void rot_x(t_fdf *sp);
void rot_y(t_fdf *sp);
void rot_z(t_fdf *sp);
void handle_x(t_fdf *sp, int x, int y);
void handle_y(t_fdf *sp, int x, int y);

void draw_line_antialias(t_fdf *sp);
typedef void t_shift(t_fdf *sp);

#endif