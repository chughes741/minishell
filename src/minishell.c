/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 14:01:39 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data		*data;
	t_params	*params;
	char		*cmd;

	(void)argv;
	data = get_data();
	init_data(envp);

	//? Signal setup
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGQUIT, signal_handler);

	cmd = ft_strdup("Welcome to Marc and Cole's minishell");
	while (ft_strncmp(cmd, "exit", 4))
	{
		free(cmd);
		cmd = readline("> ");
		params = cmd_parse(cmd);
		if (params->path)
			exe(params);
		free(params);
	}
	return (argc);
}
