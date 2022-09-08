/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 12:05:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Handling for interupts and quits
void	signal_handler(int signal)
{
	if (signal == SIGINT)
		return ;
	if (signal == SIGQUIT)
		return ;
	exit(0);
}
