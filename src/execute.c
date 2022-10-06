/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:42:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/06 16:25:12 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Executes program specified in param
void	exe(t_params *param)
{
	t_data	*data;

	param->id = fork();
	data = get_data();
	if (param->id != 0)
	{
		close_file(param->fd_in);
		close_file(param->fd_out);
		return ;
	}
	if (param->in_path != NULL)
		param->fd_in = open(param->in_path, O_RDONLY);
	if (param->out_path != NULL)
		param->fd_out = open(param->out_path, O_WRONLY | O_CREAT | O_APPEND);
	close_io(data->fd_io, data->n_cmds, param->fd_in, param->fd_out);
	dup2(param->fd_in, STDIN_FILENO);
	dup2(param->fd_out, STDOUT_FILENO);
	execve(param->path, param->exec_arg, data->envp);
}
