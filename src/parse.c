/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/02 21:46:33 by chughes          ###   ########.fr       */
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
		params[i]->fd_in = data->fd_io[i * 2];
		params[i]->fd_out = data->fd_io[(i * 2) + 1];
		i++;
	}
	return (params);
}

// Removes any files from cmd line
char**	remove_files(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '>') || ft_strchr(args[i], '<'))
			args = (char **)array_del_one((void **)args, i);
		else
			++i;
	}
	return (args);
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
	if (ft_strchr(temp, '<'))
		params->in_path = strcdup(ft_strchr(temp, '<') + 1, " ");
	if (ft_strchr(temp, '>'))
		params->out_path = strcdup(ft_strchr(temp, '>') + 1, " ");
	params->exec_arg = ft_split(temp, ' ');
	params->exec_arg = remove_files(params->exec_arg);
	xfree(temp);
	params->path = get_path(params->exec_arg[0]);
	params->envp = data->envp;
	return (params);
}
