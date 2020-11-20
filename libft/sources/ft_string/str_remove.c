/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 08:22:00 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/25 13:46:54 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	str_remove(t_string *str, int from, int n)
{
	if (from < 0 || from >= (int)str->len)
		return ;
	if (from + n >= (int)str->len)
	{
		n = str->len - from;
		ft_bzero(str->s + from, n);
	}
	else
	{
		ft_memmove(str->s + from, str->s + from + n, str->len - n - from);
		ft_bzero(str->s + str->len - n, n);
	}
	str->len -= n;
}
