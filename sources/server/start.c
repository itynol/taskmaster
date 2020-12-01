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

int			execut(t_pars *list)
{
	char	**arrgs;
	int		i;

    list->PID = fork();
    if (list->PID == 0)
    {
        i = 0;
        //TODO not fd hardcode like a shit
        tcsetpgrp(10, list->PID);
        arrgs = ft_strsplit(list->path, ' ');
        i = execve(list->path, arrgs, list->env);
        if (i < 0)
            exit(ERR_CANT_OPEN_FILE);
        else
            exit(i);
    }
    return 0;
}

void		startAllJobs(t_pars *list_start)
{
//	int		fd_op;

//	fd_op = open("logs", O_CREAT | O_RDWR, S_IRWXU);
//	dup2(fd_op, 1);
	while(list_start)
	{
		if (list_start->status == STAT_WORK)
		    execut(list_start);
		list_start = list_start->next;
	}
}
