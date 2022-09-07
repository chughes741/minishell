/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/07 17:10:33 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	return ;
}

int	main()
{
	char	*cmd;

	cmd = ft_strdup("Welcome to Marc and Cole's minishell");
	signal(SIGINT, signal_handler);
	while (ft_strncmp(cmd, "exit", 4))
	{
		free(cmd);
		cmd = readline("> ");
	}
	return (0);
}
