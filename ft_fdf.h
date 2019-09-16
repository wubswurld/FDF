#ifndef FT_FDF_H
#define FT_FDF_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "./Minilibx/mlx.h"
#include "libft/libft.h"

#define ipart(X) ((int)(X))
#define round(X) ((int)(((double)(X)) + 0.5))
#define fpart(X) (((double)(X)) - (double)ipart(X))
#define rfpart(X) (1.0 - fpart(X))

typedef struct s_head
{
    void *ptr;
    void *window;
} t_head;

typedef struct s_algo
{
    double dx;
    double dy;
    double gradient;
    double xend;
    double yend;
    double xgap;
    double intery;
    int px1;
    int py1;
    int px2;
    int py2;
    bool steep;
    double interx;
} t_algo;

typedef struct s_lines
{
    t_algo *head;
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
    int scale;
} t_lines;

typedef struct s_fdf
{
    t_head *mlx;
    t_lines *line;
    int **real;
    char *hold;
    struct stat *buf;
    char **tmo;
    char **ret;
} t_fdf;

void free_fdf(t_fdf *sp);
void handle_x(t_fdf *sp, int x, int y);
void handle_y(t_fdf *sp, int x, int y);

void draw_line_antialias(t_fdf *sp);
//rotate
void handle_rotate(t_fdf *sp);

//key press
int key_press(int keycode, t_fdf *sp);
int close_prog(void *param);
void handleKeyPress(t_fdf *sp);
//parse
void parse_fdf(t_fdf *sp);
void check_arg(char *str);
int count_2d(char **str);
void read_file(char *str, t_fdf *sp);
int check_valid(char *str);
void store_file(t_fdf *sp, char *hld);
void rot_z(t_fdf *sp);
void rot_z(t_fdf *sp);
void rot_z(t_fdf *sp);

#endif