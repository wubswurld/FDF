#include "ft_fdf.h"
#include <stdio.h>
#include <sys/stat.h>

// t_shift *check_type[1] = {handleKeyPress};

int check_valid(char *str)
{
    int x = 0;
    while (str[x])
    {
        if (!ft_isdigit(str[x]) && str[x] != '-' && str[x] != ' ' && str[x] != '\n')
            return (1);
        x++;
    }
    return (0);
}

void store_file(t_fdf *sp, char *hld)
{
    int y = 0;
    int count = 0;
    while (hld[y])
    {
        // if (hld[y] != ' ')
        sp->hold[count++] = hld[y];
        y++;
    }
    sp->hold[count] = '\0';
}

void read_file(char *str, t_fdf *sp)
{
    int fd;
    int x;
    struct stat *buf;
    char *hld;

    x = 0;
    buf = malloc(sizeof(struct stat));
    lstat(str, buf);
    sp->hold = (char *)malloc(sizeof(char) * (buf->st_size));
    hld = (char *)malloc(sizeof(char) * (buf->st_size));
    fd = open(str, O_RDONLY);
    while ((x = read(fd, hld, buf->st_size)) > 0)
    {
        if (!(check_valid(hld)))
            sp->hold = ft_strdup(hld);
        else
        {
            ft_putstr("invalid file contents");
            exit(1);
        }
    }
    // free(buf);
    // free(hld);
}

void check_arg(char *str)
{
    int x;

    x = 0;
    if (ft_strlen(str) < 5)
    {
        ft_putstr("invalid file name");
        exit(1);
    }
    while (str[x])
        x++;
    if (ft_strcmp(str + x - 4, ".fdf") != 0)
    {
        ft_putstr("invalid file name");
        exit(1);
    }
}

int count_2d(char **str)
{
    int x = 0;
    while (str[x])
        x++;
    return (x);
}

void count_strings(char **ret)
{
    int a = 0;
    while (ret[a])
    {
        if (ret[a + 1])
        {
            if (ft_strlen(ret[a]) - ft_strlen(ret[a + 1]) != 0)
            {
                ft_putstr("done");
                exit(1);
            }
        }
        a++;
    }
}

void parse_fdf(t_fdf *sp)
{
    int x = 0;
    int count;
    char **ret;
    char **tmo;
    ret = ft_strsplit(sp->hold, '\n');
    sp->real = (int **)malloc(sizeof(int *) * (count_2d(ret)));
    sp->max_x = count_2d(ret);
    while (ret[x])
    {
        tmo = ft_strsplit(ret[x], ' ');
        sp->real[x] = (int *)malloc(sizeof(int) * (count_2d(tmo)));
        count = 0;
        while (tmo[count])
        {
            sp->real[x][count] = ft_atoi(tmo[count]);
            count++;
        }
        sp->max_y = count;
        x++;
    }
}

static void draw_line(t_fdf *sp)
{
    int delta[2];
    int sign[2];
    int error[2];

    delta[0] = abs(sp->x1 - sp->x0);
    delta[1] = abs(sp->y1 - sp->y0);
    sign[0] = sp->x0 < sp->x1 ? 1 : -1;
    sign[1] = sp->y0 < sp->y1 ? 1 : -1;
    error[0] = delta[0] - delta[1];
    while (sp->x0 != sp->x1 || sp->y0 != sp->y1)
    {
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->x0 + sp->c_x, sp->y0 + sp->c_y, 255);
        if ((error[1] = error[0] * 2) > -delta[1])
        {
            error[0] -= delta[1];
            sp->x0 += sign[0];
        }
        if (error[1] < delta[0])
        {
            error[0] += delta[0];
            sp->y0 += sign[1];
        }
    }
}

// void draw_line_antialias(t_fdf *sp)
// {
//     //   unsigned int x1, unsigned int y1,
//     //   unsigned int x2, unsigned int y2,
//     double dx = (double)x2 - (double)x1;
//     double dy = (double)y2 - (double)y1;
//     if (fabs(dx) > fabs(dy))
//     {
//         if (x2 < x1)
//         {
//             swap_(x1, x2);
//             swap_(y1, y2);
//         }
//         double gradient = dy / dx;
//         double xend = round_(x1);
//         double yend = y1 + gradient * (xend - x1);
//         double xgap = rfpart_(x1 + 0.5);
//         int xpxl1 = xend;
//         int ypxl1 = ipart_(yend);
//         plot_(xpxl1, ypxl1, rfpart_(yend) * xgap);
//         plot_(xpxl1, ypxl1 + 1, fpart_(yend) * xgap);
//         double intery = yend + gradient;

//         xend = round_(x2);
//         yend = y2 + gradient * (xend - x2);
//         xgap = fpart_(x2 + 0.5);
//         int xpxl2 = xend;
//         int ypxl2 = ipart_(yend);
//         plot_(xpxl2, ypxl2, rfpart_(yend) * xgap);
//         plot_(xpxl2, ypxl2 + 1, fpart_(yend) * xgap);

//         int x;
//         for (x = xpxl1 + 1; x < xpxl2; x++)
//         {
//             plot_(x, ipart_(intery), rfpart_(intery));
//             plot_(x, ipart_(intery) + 1, fpart_(intery));
//             intery += gradient;
//         }
//     }
//     else
//     {
//         if (y2 < y1)
//         {
//             swap_(x1, x2);
//             swap_(y1, y2);
//         }
//         double gradient = dx / dy;
//         double yend = round_(y1);
//         double xend = x1 + gradient * (yend - y1);
//         double ygap = rfpart_(y1 + 0.5);
//         int ypxl1 = yend;
//         int xpxl1 = ipart_(xend);
//         plot_(xpxl1, ypxl1, rfpart_(xend) * ygap);
//         plot_(xpxl1 + 1, ypxl1, fpart_(xend) * ygap);
//         double interx = xend + gradient;

//         yend = round_(y2);
//         xend = x2 + gradient * (yend - y2);
//         ygap = fpart_(y2 + 0.5);
//         int ypxl2 = yend;
//         int xpxl2 = ipart_(xend);
//         plot_(xpxl2, ypxl2, rfpart_(xend) * ygap);
//         plot_(xpxl2 + 1, ypxl2, fpart_(xend) * ygap);

//         int y;
//         for (y = ypxl1 + 1; y < ypxl2; y++)
//         {
//             plot_(ipart_(interx), y, rfpart_(interx));
//             plot_(ipart_(interx) + 1, y, fpart_(interx));
//             interx += gradient;
//         }
//     }
// }

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
    sp->z0 = ((x * cos(sp->b)) + (z * sin(sp->b)));
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

void handle_x(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 10;
    sp->x1 = (x + 1) * 10;
    sp->y0 = y * 10;
    sp->y1 = y * 10;
    sp->z0 = sp->real[x][y] * 10;
    sp->z1 = sp->real[x + 1][y] * 10;
    // rot_x(sp);
    rot_y(sp);
    // rot_z(sp);
    draw_line(sp);
}

void handle_y(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 10;
    sp->x1 = x * 10;
    sp->y0 = y * 10;
    sp->y1 = (y + 1) * 10;
    sp->z0 = sp->real[x][y] * 10;
    sp->z1 = sp->real[x][y + 1] * 10;
    // rot_x(sp);
    rot_y(sp);
    // rot_z(sp);
    draw_line(sp);
}

int fdf_plot(t_fdf *sp)
{
    int x = 0;
    mlx_clear_window(sp->mlx->ptr, sp->mlx->window);
    sp->c_x = 550;
    sp->c_y = 1200 / 3.5;
    while (x < sp->max_x)
    {
        int y = 0;
        while (y < sp->max_y)
        {
            if (x + 1 < (sp->max_x))
                handle_x(sp, x, y);
            if (y + 1 < (sp->max_y))
                handle_y(sp, x, y);
            y++;
        }
        x++;
    }
    return (0);
}

int key_press(int keycode, t_fdf *sp)
{
    printf("ignore: %d\n", sp->max_x);
    if (keycode == 126)
        sp->a += 0.1;
    if (keycode == 125)
        sp->a -= 0.1;
    if (keycode == 123)
        sp->b += 0.1;
    if (keycode == 124)
        sp->b -= 0.1;
    if (keycode == 0)
        printf("a");
    if (keycode == 13)
        printf("w");
    if (keycode == 2)
        printf("d");
    if (keycode == 1)
        printf("s");
    return (0);
}

// int mouse_move(int x, int y, void *param)
// {

// }

void handleKeyPress(t_fdf *sp)
{
    mlx_hook(sp->mlx->window, 2, 0, key_press, sp);
    // mlx_hook(sp->mlx->window, 6, 0, key_press, sp);
}

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    sp->mlx = (t_head *)malloc(sizeof(t_head));
    if (ac == 2)
    {
        sp->a = 0.3;
        sp->b = 0.4;
        check_arg(av[1]);
        read_file(av[1], sp);
        parse_fdf(sp);
        sp->mlx->ptr = mlx_init();
        sp->mlx->window = mlx_new_window(sp->mlx->ptr, 1200, 1200, "Wubs FDF");
        handleKeyPress(sp);
        mlx_loop_hook(sp->mlx->ptr, fdf_plot, sp);
        mlx_loop(sp->mlx->ptr);
    }
    else
        ft_putstr("usage: ./ft_fdf <map>");
    return (0);
}
