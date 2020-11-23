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

#include "task_master.h"

static void		add_my_list(t_pars **tmp_list, t_pars local_job)
{
	t_pars *new;

	new = (t_pars*)malloc(sizeof(t_pars));
	new->next = (*tmp_list);
	new->name = local_job.name;
	new->path = local_job.path;
	new->status = isFileExist(local_job.path);
	(*tmp_list) = new;
}

void		parser_mth(int fd, char *buf, char **env)
{
	char	**tmp;
	t_pars  local_job;

	// [program:prog_name] check
	if (!(ft_strncmp(&buf[1], "program", 7)))
	{
		buf[ft_strlen(buf) - 2]	= '\0';
		if (buf[10] == '\0')
		{
			// name check
			write(1, "Program hasnt name!\n", 20);
			free(buf);
			return ;
		}

		local_job.name = ft_strdup(&buf[10]);
		free(buf);

		get_next_line(fd, &buf);
		tmp = ft_strsplit(buf, '=');
		tmp[1][ft_strlen(tmp[1]) - 1] = '\0';

        local_job.path = ft_strdup(tmp[1]);
        local_job.env = env;

        arrayCharCleaner(tmp);
		add_my_list(&list, local_job);
	}
}
