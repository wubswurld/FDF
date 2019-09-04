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

void read_file(char *str, t_fdf *sp)
{
    int fd;
    int x;
    struct stat *buf;
    char *hld;

    x = 0;
    buf = malloc(sizeof(struct stat));
    lstat(str, buf);
    hld = (char *)malloc(sizeof(char) * (buf->st_size));
    fd = open(str, O_RDONLY);
    while ((x = read(fd, hld, buf->st_size)) > 0)
    {
        hld[x] = '\0';
        if (!(check_valid(hld)))
            sp->hold = ft_strdup(hld);
        else
        {
            ft_putstr("invalid file contents");
            exit(1);
        }
    }
    free(buf);
    free(hld);
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

// void parse_fdf(t_fdf *sp)
// {
//     int x = 0;
//     // while (sp->hold[x])
//     // {
//     // printf("%c", sp->hold[x]);
//     // x++;
//     // }
// }

// void fdf(t_fdf *sp)
// {
//     parse_fdf(sp);
// }

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    if (ac == 2)
    {
        check_arg(av[1]);
        read_file(av[1], sp);
        // printf("%s\n", sp->hold);
        // fdf(sp);
    }
    else
        ft_putstr("usage: ./ft_fdf <map>");
    return (0);
}