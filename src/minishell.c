/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/11 10:20:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	int		i;

	data = get_data();
	init_data(envp);
	if (argc != 1 || argv[0] == NULL)
		data->run = false;
	while (1)
	{
		init_signals(INTERACTIVE);
		data->n_cmds = 0;
		data->last_cmd = readline(MSH_PROMPT);
		if (data->last_cmd == NULL)
			break ;
		add_history(data->last_cmd);
		data->params = parse_args(data->last_cmd);
		i = 0;
		init_signals(RUNTIME);
		while (i < data->n_cmds)
		{
			data->run_cmd[cmd_index(data->params[i]->exec_arg[0])](data->params[i]);
			i++;
		}
		wait_all(data);
		free_params(data->params);
		xfree(data->last_cmd);
	}
	del_data();
}
