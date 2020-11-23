//
// Created by ninem on 11/23/2020.
//

#include "task_master.h"

void            arrayCharCleaner(char **arr) {
    int i;

    i = 0;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static char		**name_and_path(char *path)
{
    char	**tmp;
    int		i;

    tmp = (char**)ft_memalloc(sizeof(char*) * 3);
    i = ft_strlen(path);
    while (i >= 0 && path[i] != '/')
        i--;
    if (i < 0) {
        tmp[0] = ft_strdup("./");
    }
    else {
        tmp[0] = (char *) malloc(i + 1);
        tmp[0][i] = '\0';
        tmp[0] = ft_strncpy(tmp[0], path, i);
    }
    tmp[1] = ft_strdup(&path[i + 1]);
    return (tmp);
}

int			isFileExist(char *path)
{
    DIR				*dirent;
    struct dirent	*entry;
    char			**tmp;

    tmp = name_and_path(path);
    if (!(dirent = opendir(tmp[0])))
    {
        arrayCharCleaner(tmp);
        return(-1);
    }
    while((entry = readdir(dirent)))
    {
        if (ft_strcmp(entry->d_name, tmp[1]) == 0)
        {
            arrayCharCleaner(tmp);
            closedir(dirent);
            return(1);
        }
    }
    closedir(dirent);
    arrayCharCleaner(tmp);
    return (-2);
}