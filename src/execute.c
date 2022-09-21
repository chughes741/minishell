/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:42:42 by chughes           #+#    #+#             */
/*   Updated: 2022/09/21 12:26:53 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Executes program specified in params
int	exe(void)
{
	t_data	*data;

	data = get_data();
	data->params->id = fork();
	if (data->params->id != 0)
		return (0);
	dup2(data->params->fd_in, STDIN_FILENO);
	dup2(data->params->fd_out, STDOUT_FILENO);
	execve(data->params->path, data->params->exec_arg, data->params->envp);
	return (1);
}
