/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/10/09 18:51:33 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Sets 
void	init_signals(void)
{
	signal(SIGINT, handle_interupt);
	signal(SIGABRT, handle_abort);
	signal(SIGQUIT, SIG_IGN);
	return ;
}

// Handles SIGINT (^C)
void	handle_interupt(int signum)
{
	t_data	*data;
	int		i;

	(void)signum;
	data = get_data();
	i = 0;
	while (data->params[i])
	{
		if (data->params[i]->id != 0
			&& cmd_index(data->params[i]->exec_arg[i]) == 8)
			kill(data->params[i]->id, 0); //TODO check leaks from killed child
		++i;
	}
	return ; //TODO Handle how this returns prompt
}

// Handles SIGABRT (^D)
void	handle_abort(int signum)
{
	(void)signum;
	builtin_exit(NULL);
}
