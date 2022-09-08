/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:42:42 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 12:43:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Executes program specified in params
int	exe(t_params *params)
{
	int	id;

	id = fork();
	if (id != 0)
		return (0);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_in, STDOUT_FILENO);
	execve(params->path, params->exec_arg, params->envp);
	return (1);
}
