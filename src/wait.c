/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:20:57 by chughes           #+#    #+#             */
/*   Updated: 2022/10/11 10:21:07 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Waits for all children to return
void	wait_all(t_data	*data)
{
	int i;

	i = 0;
	while (i < data->n_cmds)
	{
		if (cmd_index(data->params[i]->exec_arg[0]) == 8)
			waitpid(data->params[i]->id, &data->exit_status, 0);
		++i;
	}
	return ;
}
