/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_master.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:06:32 by jterry            #+#    #+#             */
/*   Updated: 2019/07/15 20:09:48 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASK_MASTER_H
# define TASK_MASTER_H

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "jobs_status.h"
#include <stdbool.h>

# define BUFF_SIZE 1
# define SOCKET_ADDRESS "tm_s"
# define MSG_BUFF 64

typedef struct		s_pars
{
	char			*name;
	bool            launch_from_start;
	char			*path;
	int				number_of_process;
	char			restart;
	int				how_long;
	int				hm_wait;
	char			*signal;
	int				grasefull;
	char			pipe;
	char			**env;
	char			*path_to_workdir;
	char			*umask;
	int				PID;
	short int		status;		
	struct s_pars	*next;
}					t_pars;

#ifndef EX
# define EX extern
#endif
EX t_pars *list;

int			ft_server_listner();
void		startAllJobs(t_pars *list_start);
void		parser_mth(int fd, char *buf, char **env);
int			help_handler();
void        arrayCharCleaner(char **arr);
t_pars      *jobFinderByName(char *name);
int			isFileExist(char *path);
char		*statusCommand(t_pars *listm);
char        *stopCommand(char **command);
char        *restartCommand(char **command);
char        *startCommand(char **command);
int			execut(t_pars *list);

#endif
