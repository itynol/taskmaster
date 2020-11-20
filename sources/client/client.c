#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include "task_master.h"

int			msgHendler(char *msg)
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
	int				fds, i;
	struct sockaddr	sockAddress;
	char			*pathToSocket = SOCKET_ADDRESS;
	char			*msg, *rawMsg;
	char			buf[1024];

    i = -1;
    sockAddress.sa_family = AF_UNIX;
    while (pathToSocket[++i]) {
        sockAddress.sa_data[i] = pathToSocket[i];
    }
    sockAddress.sa_data[i] = '\0';
	while (1)
	{
		rawMsg = readline(">");
		msg = ft_strtrim(rawMsg);
		free(rawMsg);
		i = msgHendler(msg);
		if (i < 0)
			break ;
		else if (i == 1)
		{
			fds = socket(AF_UNIX, SOCK_STREAM, 0);
			connect(fds, &sockAddress, 8);
			if ((i = send(fds, msg, 8, 0)) < 0)
			    printf("server error - code: %d\n", i);
			recv(fds, buf, 1024, 0);
			printf ("%s", buf);
			ft_bzero(buf, 1024);
		}
		else if (i != 2)
			write(1, "command not found\n", 18);
        free(msg);
    }
	free(msg);
	close(fds);
	return (0);
}
