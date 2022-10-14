/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:25:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/14 13:34:16 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Parse return from rl into t_params structs
t_params	**init_params(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	if (cmd[0] == '\0')
		return (NULL);
	data = get_data();
	cmds = split_command_groups(cmd);
	data->n_cmds = arraylen(cmds);
	if (data->n_cmds == 0)
		return (error_handler("Syntax error: "));
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds && cmds[i] != NULL)
	{
		params[i] = init_cmd(i, cmds[i]);
		i++;
	}
	free_array(cmds);
	return (params);
}

// Parses commands into struct ready to be executed
t_params	*init_cmd(int i, char *line)
{
	t_data		*data;
	t_params	*params;

	data = get_data();
	params = (t_params *)ft_calloc(1, sizeof(t_params));
	params->exec_arg = split_args(line);
	insert_vars(params->exec_arg);
	params->fd_in = data->fd_io[i * 2];
	params->fd_out = data->fd_io[(i * 2) + 1];
	open_outfiles(params);
	open_infiles(params);
	params->path = get_path(params->exec_arg[0]);
	return (params);
}
