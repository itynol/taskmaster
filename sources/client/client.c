#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include "task_master.h"

int			msgHandler(char *rawMsg)
{
    char **msgArr;
    char *msg;

    msgArr = ft_strsplit(rawMsg, ' ');
    msg = msgArr[0];
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
		return (help_handler());
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
		if (ft_strlen(rawMsg) == 0)
            continue;
		msg = ft_strtrim(rawMsg);
		free(rawMsg);
		i = msgHandler(msg);
		if (i < 0)
			break ;
		else if (i == 1)
		{
			fds = socket(AF_UNIX, SOCK_STREAM, 0);
			connect(fds, &sockAddress, MSG_BUFF);
			if ((i = send(fds, msg, MSG_BUFF, 0)) < 0) {
                printf("server error - code: %d\n", i);
                free(msg);
                continue;
            }
			recv(fds, buf, 1024, 0);
			write(1, buf, ft_strlen(buf));
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
