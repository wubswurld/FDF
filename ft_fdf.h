#ifndef FT_FDF_H
#define FT_FDF_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct s_fdf
{
    char *hold;
    struct stat *buf;
} t_fdf;

#endif