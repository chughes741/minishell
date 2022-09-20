/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/09/20 15:06:20 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Sets 
void	init_signals(void)
{
	signal(SIGINT, handle_interupt);
	signal(SIGQUIT, handle_quit);
	signal(SIGABRT, handle_abort);
	return ;
}

// Handles SIGINT (^C)
void	handle_interupt(int signum)
{
	t_data	*data;

	data = get_data();
	if (data->params->id != 0)
		kill(data->params->id); //TODO check leaks from killed child
	return ; //TODO Handle how this returns prompt
}

// Handles SIGQUIT (^D)
void	handle_quit(int signum)
{
	exit(0);
}

// Handles SIGABRT (^\)
void	handle_abort(int signum)
{
	return ;
}
