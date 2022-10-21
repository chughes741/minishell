/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:25:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/21 11:35:03 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parse return from rl into t_params structs
t_params	**init_params(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	i = 0;
	data = get_data();
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	cmds = split_command_groups(cmd);
	if (cmds == NULL)
		return (NULL);
	data->n_cmds = arraylen(cmds);
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
	params->fd_in = data->fd_io[i * 2];
	params->fd_out = data->fd_io[(i * 2) + 1];
	open_outfiles(params);
	open_infiles(params);
	insert_vars(params->exec_arg);
	if (params->exec_arg && params->exec_arg[0])
		params->path = get_path(params->exec_arg[0]);
	else
		params->err = true;
	return (params);
}
