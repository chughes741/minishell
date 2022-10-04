/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/04 13:52:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	int		i;

	data = get_data();
	init_data(envp);
	if (argc != 1 || !argv[0])
		data->run = false;
	while (data->run == true)
	{
		data->n_cmds = 0;
		data->last_cmd = prompter();
		data->params = parse_args(data->last_cmd);
		i = 0;
		while (i < data->n_cmds)
		{
			if (run_builtin(data->params[i]) == false)
			{
				exe(data->params[i], i);
				// if (WIFEXITED(data->exit_status) != 0)
					// error_handler();
			}
			++i;
		}
		wait(&data->exit_status);
	}
	del_data();
	exit(0);
}
