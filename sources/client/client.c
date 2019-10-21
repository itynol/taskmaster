#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include "../../task_master.h"

int			msg_hendler(char *msg)
{
	if (ft_strcmp(msg, "exit") == 0)
		return (-1);
	else if (!(ft_strcmp(msg, "status")) ||
			!(ft_strcmp(msg, "add")) ||
			!(ft_strcmp(msg, "remove")) ||
			!(ft_strcmp(msg, "restart")) ||
			!(ft_strcmp(msg, "start")) ||
			!(ft_strcmp(msg, "stop")) ||
			!(ft_strcmp(msg, "reserv")) ||
			!(ft_strcmp(msg, "shutdown")))
		return(1);
	else if (!(ft_strcmp(msg, "help")))
		return (help_hendler());
	else
		return(0);

}

int main()
{
	int				fds;
	struct sockaddr	lol;
	char			*adr = "./lol";
	char			*msg;
	char			buf[1024];
	int				i;

	i = -1;
	lol.sa_family = AF_UNIX;
	while (adr[++i])
		lol.sa_data[i] = adr[i];
	while (1)
	{
		msg = readline(">");
		i = msg_hendler(msg);
		if (i < 0)
			break ;
		else if (i == 1)
		{
			fds = socket(AF_UNIX, SOCK_STREAM, 0);
			connect(fds, &lol, 8);
			if (send(fds, msg, 8, 0) < 0)
				write(1, "server error\n", 13);
			recv(fds, buf, 1024, 0);	
			printf ("%s", buf);
			ft_bzero(buf, 1024);
			free(msg);
		}
		else if (i != 2)
			write(1, "command not found\n", 18);
	}
	free(msg);
	close(fds);
	return (0);
}
