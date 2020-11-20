/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:22:17 by jterry            #+#    #+#             */
/*   Updated: 2019/07/15 20:29:36 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../task_master.h"

static char		**name_and_path(char *path)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char**)ft_memalloc(sizeof(char*) * 3);
	 i = ft_strlen(path);
	 while (path[i] != '/')
		 i--;
	 tmp[0] = (char*)malloc(i + 1);
	 tmp[0][i] = '\0';
	 tmp[0] = ft_strncpy(tmp[0], path, i);
	 tmp[1] = ft_strdup(&path[i + 1]);
	 return (tmp);
}

static void			fred(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

static int			status_def(char *path)
{
	DIR				*dirent;
	struct dirent	*entry;
	char			**tmp;

	tmp = name_and_path(path);
	if (!(dirent = opendir(tmp[0])))
	{
		fred(tmp);
		return(-1);
	}
	while((entry = readdir(dirent)))
	{
		if (ft_strcmp(entry->d_name, tmp[1]) == 0)
		{
			fred(tmp);
			closedir(dirent);
			return(1);
		}
	}
	closedir(dirent);
	fred(tmp);
	return (-2);
}

static void		add_my_list(t_pars **tmp_list, char *name, char *path)
{
	t_pars *new;

	new = (t_pars*)malloc(sizeof(t_pars));
	new->next = (*tmp_list);
	new->name = name;
	new->path = path;
	new->status = status_def(path);
	(*tmp_list) = new;
}

void		parser_mth(int fd, char *buf)
{
	char	*name;
	char	*path;
	char	**tmp;

	// [program:prog_name] check
	if (!(ft_strncmp(&buf[1], "program", 7)))
	{
		buf[ft_strlen(buf) - 1]	= '\0';
		if (buf[10] == '\0')
		{
			// name cheack
			write(1, "Program hasnt name!\n", 20);
			free(buf);
			return ;
		}
		name = ft_strdup(&buf[9]);
		free(buf);
		get_next_line(fd, &buf);
		tmp = ft_strsplit(buf, '=');
		tmp[1][ft_strlen(tmp[1]) - 1] = '\0';
		path = ft_strdup(tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		add_my_list(&list, name, path);
	//	free(path);
	}
}
