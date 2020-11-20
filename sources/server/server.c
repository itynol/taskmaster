#include "task_master.h"

static char		*msg_status(t_pars *listm)
{
	char	*tmpMsg;
	char	*msg;

	if (listm)
		msg = ft_strnew(0);
	while(listm)
	{
		tmpMsg = ft_strrejoin(listm->name, ft_itoa(listm->PID), 2);
		if (listm->status == 1)  // online monitor
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tWORK\n", 1);
		else if (listm->status == 0)
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tEND\n", 1);
		else if (listm->status == -1)
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tCANT OPEN DIR\n", 1);
		else if (listm->status == -2)
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tNOT FOUND\n", 1);
		else if (listm->status == -3)
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tCAT OPEN FILE\n", 1);
		else if (listm->status == 15 || listm->status == 9)
			tmpMsg = ft_strrejoin(tmpMsg, "\t\tWAS KILLED\n", 1)
;		msg = ft_strrejoin(msg, tmpMsg, 3);
		listm = listm->next;
	}
	return (msg);
}

static void	hendler(int sock, char *buf, int fds)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strdup(buf);
	if (ft_strcmp(tmp, "status") == 0)
	{
		msg = msg_status(list);
		send(sock, msg, ft_strlen(msg), 0);
	}
	else if (ft_strcmp(tmp, "shutdown") == 0)
	{
		free(tmp);
		close(fds);
		remove(SOCKET_ADDRESS);
		exit(0);
	}
	else
	{
		msg = ft_strdup("So young\n");
		send(sock, msg, ft_strlen(msg), 0);
	}
	free(tmp);
	free(msg);
	msg = NULL;
}

int			ft_server_listner()
{
	int	fds, sock, i, listenStatus;
	struct sockaddr sockAddress;
	char	*pathToSocket = SOCKET_ADDRESS;
	char	buf[4096];

	i = -1;
    sockAddress.sa_family = AF_UNIX;
	while (pathToSocket[++i])
		sockAddress.sa_data[i] = pathToSocket[i];
    sockAddress.sa_data[i] = '\0';
	fds = socket(AF_UNIX, SOCK_STREAM, 0);
	i = bind(fds, &sockAddress, 8);
    listenStatus = listen(fds, 1);
	printf("Hello, your taskmaster has started:"
        "\nfds - %d"
        "\nbind - %d"
        "\nlistenStatus - %d"
        "\nsockAddress - %s\n", fds, i, listenStatus, sockAddress.sa_data);
    while (1)
	{
		sock = accept(fds, NULL, NULL);
		i = recv(sock, buf, 8, 0);
		if (i > 0)
		{
			printf ("git it\n");
			hendler(sock, buf, fds);
		}
		sleep(1);
		close(sock);
	}
	return (0);
}
