#include "ft_fdf.h"

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
    while (hld[y++])
        sp->hold[count++] = hld[y];
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

void parse_fdf(t_fdf *sp)
{
    int y = 0;
    char **ret;
    char **tmo;
    ret = ft_strsplit(sp->hold, '\n');
    sp->real = (int **)malloc(sizeof(int *) * (count_2d(ret)));
    sp->line->max_y = count_2d(ret);
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
        sp->line->max_x = x;
        y++;
    }
}