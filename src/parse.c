/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/02 15:05:00 by chughes          ###   ########.fr       */
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
	data->fd_io = setup_io(data->n_cmds);
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
	return (params);
}

// Returns an array with the fds of n pipes
int	*setup_io(int n_cmds)
{
	int	*fd_io;
	int	i;

	fd_io = (int *)ft_calloc(n_cmds * 2, sizeof(int));
	i = 1;
	while (i < n_cmds)
	{
		pipe(fd_io[(i * 2) + 1]); //! RD/WR are reversed
		++i;
	}
	return (fd_io);
}

void	close_io(int *fd_io, int n_cmds)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < n_cmds * 2)
	{
		if (fd_io[i] > 1)
			close(fd_io[i]);
		++i;
	}
	xfree(fd_io);
	return ;
}
