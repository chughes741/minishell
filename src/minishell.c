/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 18:01:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = get_data();
	init_data(envp);
	if (argc != 1 || !argv[0])
		data->run = false;
	while (data->run == true)
	{
		data->last_cmd = prompter();
		data->params = parse_args(data->last_cmd);
		while (--data->n_cmds >= 0)
		{
			if (run_builtin(data->params[data->n_cmds]) == false)
			{
				exe(data->params[data->n_cmds]);
				waitpid(data->params[data->n_cmds]->id, &data->exit_status, 0);
				// if (WIFEXITED(data->exit_status) != 0)
					// error_handler();
			}
		}
	}
	cleanup();
	exit(0);
}
