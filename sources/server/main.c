/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:57:46 by jterry            #+#    #+#             */
/*   Updated: 2019/07/15 20:46:23 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../task_master.h"

void		config_reader(char **av, char **env)
{
	int		fd;
	char	*buf;
	int g;
 //hello mothered
	g = 0;
	list = NULL;
	buf = NULL;
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		write(1, "File ", 4);
		write(1, av[1], ft_strlen(av[1]));
		write(1, " not found", 10);
		return ;
	}
	while (get_next_line(fd, &buf))
	{
		//looking for '[' element
		if (*buf != '#' && *buf != ' ' && *buf && *buf == '[')
			parser_mth(fd, ft_strdup(buf));
		free(buf);
	}
	start(env, list);
	ft_server_listner();
}

void		signals(int signal)
{
	pid_t tmp;
	int siglog;
	t_pars	*first;

	first = list;
	if (signal == SIGCHLD)
	{
		tmp = wait(&siglog);
		while(tmp != list->PID && list)
			list = list->next;
		if (list->PID == tmp)
			list->status = (short int)siglog;
	}
	list = first;
}

int		 main(int ac, char **av, char **env)
{
	signal(SIGCHLD, signals);
	if (ac < 2)
		write(1, "Please select conf file\n", 25);
	else if (ac > 2)
		write(1, "So many args\n", 14);
	else
		config_reader(av, env);
	return (0);
}
