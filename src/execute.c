/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:42:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/02 16:50:14 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Executes program specified in params
int	exe(t_params *params, int i_child)
{
	t_data	*data;

	params->id = fork();
	data = get_data();
	if (params->id != 0)
	{
		if (data->fd_io[i_child * 2] > 2)
			close(data->fd_io[i_child * 2]);
		if (data->fd_io[(i_child * 2) + 1] > 2)
			close(data->fd_io[(i_child * 2) + 1]);
		return (0);
	}
	close_io(data->fd_io, data->n_cmds, i_child);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
	execve(params->path, params->exec_arg, params->envp);
	return (1);
}
