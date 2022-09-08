/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 12:49:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data		*data;
	char		*cmd;
	t_params	prms;

	data = get_data();
	init_data(envp);
	signal(SIGINT, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGQUIT, signal_handler);

	if (!argv[0])
		exit(0);

	prms.path = get_path(data->paths, "echo");
	prms.envp = envp;
	prms.exec_arg = ft_split("echo hello", ' ');
	prms.fd_in = STDIN_FILENO;
	prms.fd_out = STDOUT_FILENO;

	cmd = ft_strdup("Welcome to Marc and Cole's minishell");
	while (ft_strncmp(cmd, "exit", 4))
	{
		free(cmd);
		cmd = readline("> ");
		exe(&prms);
	}
	return (argc);
}
