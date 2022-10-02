/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/02 17:29:13 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Parse return from rl into t_params structs
t_params	**parse_args(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	data = get_data();
	cmds = ft_split(cmd, '|');
	data->n_cmds = arraylen(cmds);
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds[i])
	{
		params[i] = cmd_parse(cmds[i]);
		set_child_io(params[i], i);
		i++;
	}
	return (params);
}

// Parses commands into struct ready to be executed
t_params	*cmd_parse(char *line)
{
	t_data		*data;
	t_params	*params;
	char		*temp;

	data = get_data();
	params = ft_calloc(1, sizeof(t_params));
	temp = ft_strtrim(line, " ");
	params->exec_arg = ft_split(temp, ' ');
	xfree(temp);
	params->path = get_path(params->exec_arg[0]);
	params->envp = data->envp;
	params->in_path = NULL; //TODO Figure out infile parsing
	params->out_path = NULL; //TODO Figure out outfile parsing
	return (params);
}
