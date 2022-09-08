/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/07 20:00:41 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		return ;
	if (signal == SIGQUIT)
		return ;
	exit(0);
}

int	main()
{
	char	*cmd;

	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGQUIT, signal_handler);
	cmd = ft_strdup("Welcome to Marc and Cole's minishell");
	while (ft_strncmp(cmd, "exit", 4))
	{
		free(cmd);
		cmd = readline("> ");
	}
	return (0);
}
