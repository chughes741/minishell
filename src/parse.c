/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 11:56:18 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Parses commands into struct ready to be executed
t_params	*cmd_parse(char *line)
{
	t_data		*data;
	t_params	*params;

	data = get_data();
	params = ft_calloc(1, sizeof(t_params));
	params->exec_arg = ft_split(line, ' ');
	params->path = get_path(data->paths, ft_strdup(params->exec_arg[0]));
	params->envp = 	data->envp;
	params->fd_in = STDIN_FILENO;
	params->fd_out = STDOUT_FILENO;
	params->fd_err = STDERR_FILENO;
	
	return (params);
}

t_params	**parse_args(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	data = get_data();
	cmds = ft_split(cmd, '|');
	data->n_cmds = 0;
	while (cmds[data->n_cmds])
		++data->n_cmds;
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params*));
	i = 0;
	while (cmds[i])
	{
		params[i] = cmd_parse(cmds[i]);
		i++;
	}
	return (params);
}
