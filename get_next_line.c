/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:18:07 by jterry            #+#    #+#             */
/*   Updated: 2019/07/15 20:46:09 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "task_master.h"

static	int			ft_creatline(char **line, char *hvost)
{
	int				i;
	char			str[BUFF_SIZE + 1];
	char			*memstr;

	i = 0;
	memstr = ft_strdup(hvost);
	free(hvost);
	while (memstr[i])
	{
		if (memstr[i] == '\n')
		{
			str[i] = '\0';
			i++;
			break ;
		}
		str[i] = memstr[i];
		i++;
	}
	if (memstr[i] != '\0')
		hvost = ft_strdup(memstr + i);
	free(memstr);
	(*line) = ft_strrejoin((*line), str, 1);
	return (i);
}

int					ft_readstr(const int fd, char **line, char *hvost)
{
	int				rdbuf;
	char			tmp[BUFF_SIZE + 1];

	if (!hvost || !(ft_strchr(hvost, '\n')))
	{
		if (hvost)
		{
			*line = ft_strrejoin(*line, hvost, 3);
			*hvost = '\0';
		}
		while (((rdbuf = read(fd, tmp, BUFF_SIZE)) > 0))
		{
			tmp[rdbuf] = '\0';
			if (ft_strchr(tmp, '\n'))
			{
				if ((hvost = ft_strdup(tmp)) == NULL)
					return (-1);
				break ;
			}
			(*line) = ft_strrejoin((*line), tmp, 1);
		}
	}
	if (hvost)
		ft_creatline(line, hvost);
	return ((ft_strlen(*line) == 0) && (!hvost) ? 0 : 1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*hvost;
	int				chk;

	chk = 0;
	if (!line || read(fd, *line, 0) < 0)
		return (-1);
	if (((*line = ft_strnew(0)) == NULL))
		return (-1);
	if ((chk = ft_readstr(fd, line, hvost)) == -1)
		free(hvost);
	return (chk);
}
