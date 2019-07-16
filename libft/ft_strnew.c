/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:41:35 by dwisoky           #+#    #+#             */
/*   Updated: 2019/06/15 19:01:25 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char *)ft_memalloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}
