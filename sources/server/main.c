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

# define EX
#include "task_master.h"

static void		config_reader(char **av, char **env)
{
	int		fd;
	char	*buf;

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
			parser_mth(fd, ft_strdup(buf), env);
		free(buf);
	}
}

void		    signals(int signal)
{
	pid_t tmp;
	int siglog;
	t_pars	*first;

    if (signal == SIGCHLD)
    {
        first = list;
		tmp = wait(&siglog);
        printf("PID %d - SIG %d\n", tmp, siglog);
        while(tmp != list->PID && list)
			list = list->next;
		if (list->PID == tmp)
			list->status = (short int)siglog;
	    list = first;
	} else if (signal == SIGQUIT)
    {
        printf ("Quit (core dumped)\n");
        remove(SOCKET_ADDRESS);
        exit(0);
    }
}

void              init(char **av, char **env)
{
    char *sockAdr;

    sockAdr = SOCKET_ADDRESS;
    signal(SIGCHLD, signals);
    signal(SIGQUIT, signals);
    if (isFileExist(sockAdr) > 0) {
        remove(sockAdr);
    }
    config_reader(av, env);
    startAllJobs(list);
    ft_server_listner();
}

int		          main(int ac, char **av, char **env)
{
    if (ac < 2)
		write(1, "Please select conf file\n", 25);
	else if (ac > 2)
		write(1, "So many args\n", 14);
	else
		init(av, env);
	return (0);
}
