#include "task_master.h"

static void	handler(int sock, char *buf, int fds)
{
    char **rawMsg;
	char	*msg;

	printf("message: |%s|\n", buf);
    rawMsg = ft_strsplit(buf, ' ');
    if (ft_strcmp(rawMsg[0], "status") == 0)
        msg = statusCommand(list);
    else if (ft_strcmp(rawMsg[0], "shutdown") == 0) {
        arrayCharCleaner(rawMsg);
        close(fds);
        remove(SOCKET_ADDRESS);
        exit(0);
    }
    else if (ft_strcmp(rawMsg[0], "stop") == 0)
        msg = stopCommand(rawMsg);
    else
        msg = ft_strdup("So young\n");
    arrayCharCleaner(rawMsg);
    send(sock, msg, ft_strlen(msg), 0);
	free(msg);
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
	i = bind(fds, &sockAddress, MSG_BUFF);
    listenStatus = listen(fds, 1);
	printf("Hello, your taskmaster has started:"
        "\nfds - %d"
        "\nbind - %d"
        "\nlistenStatus - %d"
        "\nsockAddress - %s\n", fds, i, listenStatus, sockAddress.sa_data);
    while (1)
	{
		sock = accept(fds, NULL, NULL);
		i = recv(sock, buf, MSG_BUFF, 0);
		if (i > 0)
			handler(sock, buf, fds);
		sleep(1);
		close(sock);
	}
	return (0);
}
