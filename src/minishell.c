/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/10 15:23:30 by chughes          ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;
	int		i;

	data = get_data();
	init_data(envp);
	if (argc != 1 || argv[0] == NULL)
		data->run = false;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	while (data->run == true)
	{
		reset_sig();
		data->n_cmds = 0;
		xfree(data->last_cmd);
		data->last_cmd = readline(MSH_PROMPT);
		if (data->last_cmd != NULL)
		{
			add_history(data->last_cmd);
			data->params = parse_args(data->last_cmd);
			i = 0;
			while (i < data->n_cmds)
			{
				data->run_cmd[cmd_index(data->params[i]->exec_arg[0])](data->params[i]);
				i++;
			} //TODO wc isn't hanging, prompt is just returned
			wait_all(data);
			free_params(data->params);
		}
	}
}
