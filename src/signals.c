/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 14:54:29 by chughes          ###   ########.fr       */
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

	(void)signum;
	data = get_data();
	if (data->params[0]->id != 0) //! Need a different way to check if child
		kill(data->params[0]->id, 0); //TODO check leaks from killed child
	return ; //TODO Handle how this returns prompt
}

// Handles SIGQUIT (^D)
void	handle_quit(int signum)
{
	(void)signum;
	exit(0);
}

// Handles SIGABRT (^\)
void	handle_abort(int signum)
{
	(void)signum;
	return ;
}
