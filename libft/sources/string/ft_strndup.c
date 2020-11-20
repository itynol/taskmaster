/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 05:45:54 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/24 18:15:18 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int j)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	if (!src)
		return (NULL);
	while (src[len] != '\0')
		len++;
	if (j < len)
		len = j;
	str = (char*)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
