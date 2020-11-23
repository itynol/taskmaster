/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:23:36 by jterry            #+#    #+#             */
/*   Updated: 2019/07/15 18:54:35 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "task_master.h"

static int			execut(char *path, char **env)
{
	char	**tmp;
	int		i;
	
	i = 0;
	tmp = ft_strsplit(path, ' ');
	i = execve(path, tmp, env);
	return (i);
}

void		start(t_pars *list_start)
{
//	int		fd_op;

//	fd_op = open("logs", O_CREAT | O_RDWR, S_IRWXU);
//	dup2(fd_op, 1);
	while(list_start)
	{
		if (list_start->status == 1)
		{
			list_start->PID = fork();
			if (list_start->PID == 0)
			{
				if (execut(list_start->path, list_start->env) < 0)
				{
					list_start->status = -3;
					exit(0);
				}
			}
		}
		list_start = list_start->next;
	}
}
