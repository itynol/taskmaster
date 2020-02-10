#include "../../task_master.h"


static char		*msg_status(t_pars *listm)
{
	char	*tmp;
	char	*msg;

	if (listm)
		msg = ft_strnew(0);
	while(listm)
	{
		tmp = ft_strrejoin(listm->name, "\t", 0);
		tmp = ft_strrejoin(tmp, ft_itoa(listm->PID), 3);
		if (listm->status == 1)  // online monitor
			tmp = ft_strrejoin(tmp, "\t\tWORK\n", 1);
		else if (listm->status == 0)
			tmp = ft_strrejoin(tmp, "\t\tEND\n", 1);
		else if (listm->status == -1)
			tmp = ft_strrejoin(tmp, "\t\tCANT OPEN DIR\n", 1);
		else if (listm->status == -2)
			tmp = ft_strrejoin(tmp, "\t\tNOT FOUND\n", 1);
		else if (listm->status == -3)
			tmp = ft_strrejoin(tmp, "\t\tCAT OPEN FILE\n", 1);
		else if (listm->status == 15 || listm->status == 9)
			tmp = ft_strrejoin(tmp, "\t\tWAS KILLED\n", 1)
;		msg = ft_strrejoin(msg, tmp, 3);
		listm = listm->next;
	}
	return (msg);
}

static void	hendler(int sock, char *buf, int fds)
{
	char	*tmp;
	char	*msg;

	fds = 1;
	tmp = ft_strtrim(buf);
	if (ft_strcmp(tmp, "status") == 0)
	{
		msg = msg_status(list);
		send(sock, msg, ft_strlen(msg), 0);
	}
	else if (ft_strcmp(tmp, "shutdown") == 0)
	{
		send(sock, NULL, 0, 0);
		free(tmp);
		close(fds);
		remove("./mysocket");
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
	int	fds, sock;
	struct sockaddr mysocket;
	char	*adr = "./mysocket";
	int		i;
	char	buf[4096];

	i = -1;
	mysocket.sa_family = AF_UNIX;
	while (adr[++i])
		mysocket.sa_data[i] = adr[i];
	fds = socket(AF_UNIX, SOCK_STREAM, 0);
	i = bind(fds, &mysocket, 8);
	listen(fds, 1);
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
