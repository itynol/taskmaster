/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:07:53 by jterry            #+#    #+#             */
/*   Updated: 2019/07/14 19:59:43 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "task_master.h"

int					help_handler()
{
	ft_putstr("\ndefault commands:\n=========================\n");
	ft_putstr("start\texit\tadd\nstop\tshutdown\tremove");
	ft_putstr("restart\thelp\tstatus\nreserv");
	return (2);
}
