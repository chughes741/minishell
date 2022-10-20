/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:42:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:37:16 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns index of cmd to call cmd function pointer from cmd array
int	cmd_idx(char *arg)
{
	t_data	*d;
	int		i;

	d = get_data();
	i = 0;
	if (!arg)
		return (0);
	while (d->cmd_names[i])
	{
		if (!ft_strncmp(arg, d->cmd_names[i], ft_strlen(d->cmd_names[i]) + 1))
			break ;
		++i;
	}
	return (i);
}

// Executes program specified in param
void	exe(t_params *param)
{
	t_data	*data;

	data = get_data();
	if (param->path == NULL)
	{
		data->exit_status = 127 << 8;
		return ;
	}
	param->id = fork();
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
