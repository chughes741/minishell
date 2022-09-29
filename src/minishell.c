/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 17:01:42 by chughes          ###   ########.fr       */
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
		data->last_cmd = prompter();
		data->params = parse_args(data->last_cmd);
		i = -1;
		while (++i < data->n_cmds)
		{
			exe(data->params[i]);
			waitpid(data->params[i]->id, &data->exit_status, 0);
			if (WIFEXITED(data->exit_status) != 0)
				error_handler();
		}
	}
	cleanup();
	exit(0);
}
