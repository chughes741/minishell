/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 18:43:18 by chughes          ###   ########.fr       */
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
	data->fd_pipes = open_pipes(data->n_cmds - 1);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds[i])
	{
		params[i] = cmd_parse(cmds[i]);
		if (i == 0)
			params[i]->fd_in = STDIN_FILENO;
		else
			params[i]->fd_in = data->fd_pipes[i - 1][0];
		if (i == data->n_cmds - 1)
			params[i]->fd_out = STDOUT_FILENO;
		else
			params[i]->fd_out = data->fd_pipes[i][1];
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
int	**open_pipes(int n_pipes)
{
	int	**fd_pipes;
	int	i;

	if (n_pipes < 1)
		return (NULL);
	fd_pipes = (int **)ft_calloc(n_pipes + 1, sizeof(int *));
	i = -1;
	while (++i < n_pipes)
	{
		fd_pipes[i] = (int *)ft_calloc(2, sizeof(int));
		pipe(fd_pipes[i]);
	}
	return (fd_pipes);
}

void	close_pipes(int **fd_pipes)
{
	t_data	*data;
	int		i;

	data = get_data();
	if (data->n_cmds < 2)
		return ;
	i = -1;
	while (fd_pipes[++i])
	{
		close(fd_pipes[i][0]);
		close(fd_pipes[i][1]);
	}
	free_array((void **)fd_pipes);
}
