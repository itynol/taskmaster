/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:20:57 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/22 21:37:06 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static t_string	*create(t_string *str, const char *s, size_t size)
{
	*str = str_create(size);
	if (!str->alloc)
		return (NULL);
	ft_memcpy(str->s, s, size);
	return (str);
}

t_string		*str_insert(t_string *str, int to, const char *s, size_t size)
{
	size_t	newalloc;
	size_t	copy;

	if (!str || !s || !size)
		return (str);
	to = (to > (int)str->len) ? str->len : to;
	to = (to < 0) ? 0 : to;
	if (!str->alloc)
		return (create(str, s, size));
	if (str->len + size >= str->alloc)
	{
		newalloc = str->alloc * 2;
		while (str->len + size >= newalloc)
			newalloc *= 2;
		if (!ft_realloc((void **)&str->s, str->len, newalloc))
			return (NULL);
		str->alloc = newalloc;
	}
	copy = size;
	ft_memmove(str->s + to + copy, str->s + to, str->len - to);
	ft_memcpy(str->s + to, s, size);
	str->len += size;
	return (str);
}
