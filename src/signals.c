/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:35:23 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// Initialize signals for interactive or runtime
void	init_signals(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGINT, sigint_interactive);
		signal(SIGQUIT, sigquit_interactive);
	}
	else if (mode == RUNTIME)
	{
		signal(SIGINT, sigint_runtime);
		signal(SIGQUIT, sigquit_runtime);
	}
	return ;
}

// Handles interupt signal "^C" during interactive mode
void	sigint_interactive(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

// Handles quit signal "^\" during interactive mode
void	sigquit_interactive(int signum)
{
	(void)signum;
	rl_redisplay();
	return ;
}

// Handles interupt signal "^C" while programs are running
void	sigint_runtime(int signum)
{
	(void)signum;
	kill(0, 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	return ;
}

// Handles quit signal "^\" while programs are running
void	sigquit_runtime(int signum)
{
	t_data	*data;

	data = get_data();
	(void)signum;
	kill(0, 0);
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(data->exit_status, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	return ;
}
