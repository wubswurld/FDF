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
    int y = 0;
    char **ret;
    char **tmo;
    ret = ft_strsplit(sp->hold, '\n');
    sp->real = (int **)malloc(sizeof(int *) * (count_2d(ret)));
    sp->max_y = count_2d(ret);
    while (ret[y])
    {
        tmo = ft_strsplit(ret[y], ' ');
        sp->real[y] = (int *)malloc(sizeof(int) * (count_2d(tmo)));
        int x = 0;
        while (tmo[x])
        {
            sp->real[y][x] = ft_atoi(tmo[x]);
            x++;
        }
        sp->max_x = x;
        y++;
    }
}

int fdf_plot(t_fdf *sp)
{
    int y = 0;
    mlx_clear_window(sp->mlx->ptr, sp->mlx->window);
    while (y < sp->max_y)
    {
        int x = 0;
        while (x < sp->max_x)
        {
            if (y + 1 < (sp->max_y))
                handle_y(sp, x, y);
            if (x + 1 < (sp->max_x))
                handle_x(sp, x, y);
            ++x;
        }
        ++y;
    }
    return (0);
}

int key_press(int keycode, t_fdf *sp)
{
    if (keycode == 126)
        sp->a += 0.2;
    if (keycode == 125)
        sp->a -= 0.2;
    if (keycode == 123)
        sp->b += 0.1;
    if (keycode == 124)
        sp->b -= 0.1;
    if (keycode == 0)
        sp->c_x -= 15;
    if (keycode == 13)
        sp->c_y += 15;
    if (keycode == 2)
        sp->c_x += 15;
    if (keycode == 1)
        sp->c_y -= 15;
    if (keycode == 53)
        exit(0);
    return (0);
}

int close_prog(void *param)
{
    (void)param;
    exit(0);
}

void handleKeyPress(t_fdf *sp)
{
    mlx_hook(sp->mlx->window, 2, 0, key_press, sp);
    mlx_hook(sp->mlx->window, 17, 0, close_prog, sp);
}

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    sp->mlx = (t_head *)malloc(sizeof(t_head));
    if (ac == 2)
    {
        sp->a = 0.3;
        sp->b = 0.2;
        sp->c_x = 550;
        sp->c_y = 1200 / 3.5;
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
