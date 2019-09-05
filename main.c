#include "ft_fdf.h"
#include <stdio.h>
#include <sys/stat.h>
#include "libft/libft.h"

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
        // store_file(sp, hld);
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

void parse_fdf(t_fdf *sp)
{
    int x = 0;
    int count;
    char **ret;
    char **tmo;
    int **real;
    ret = (char **)malloc(sizeof(char *));
    tmo = (char **)malloc(sizeof(char *));
    ret = ft_strsplit(sp->hold, '\n');
    real = (int **)malloc(sizeof(int *) * (count_2d(ret)));
    while (ret[x])
    {
        tmo = ft_strsplit(ret[x], ' ');
        real[x] = (int *)malloc(sizeof(int) * (count_2d(tmo)));
        count = 0;
        int q = 0;
        while (tmo[count])
        {
            real[x][q++] = ft_atoi(tmo[count]);
            count++;
        }
        x++;
    }
    printf("%d\n", real[0][0]);
}

void fdf(t_fdf *sp)
{
    parse_fdf(sp);
}

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    if (ac == 2)
    {
        check_arg(av[1]);
        read_file(av[1], sp);
        fdf(sp);
    }
    else
        ft_putstr("usage: ./ft_fdf <map>");
    return (0);
}