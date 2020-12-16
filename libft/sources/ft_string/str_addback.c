/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:07:33 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/22 21:36:47 by gmelisan         ###   ########.fr       */
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

t_string		*str_addback_char(t_string *str, const char c)
{
	char		buf[] = " ";

	if (!str)
		return str;
	
	buf[0] = c;
	if (!str->alloc)
		return (create(str, buf, 1));
	if (str->len + 1 >= str->alloc)
	{
		if (!ft_realloc((void **)&str->s, str->len, str->alloc * 2))
			exit(-1);
		str->alloc = str->alloc * 2;
	}
	str->s[str->len] = c;
	str->len++;
	return (str);
}

t_string		*str_addback(t_string *str, const char *s, size_t size)
{
	size_t	newalloc;

	if (!str || !s || !size)
		return (str);
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
	ft_memcpy(str->s + str->len, s, size);
	str->len += size;
	return (str);
}
