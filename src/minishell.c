/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/19 18:43:40 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_minishell(t_data *dat)
{
	int	i;

	while (1)
	{
		init_signals(INTERACTIVE);
		dat->last_cmd = readline(MSH_PROMPT);
		while (dat->last_cmd[0] == '\0')
			dat->last_cmd = readline(MSH_PROMPT);
		add_history(dat->last_cmd);
		dat->params = init_params(dat->last_cmd);
		i = 0;
		init_signals(RUNTIME);
		while (i < dat->n_cmds && dat->params[i]->exec_arg[0] != NULL)
		{
			if (dat->params[i]->err == false)
				dat->run_cmd[cmd_idx(dat->params[i]->exec_arg[0])](dat->params[i]);
			i++;
		}
		wait_all(dat);
		dat->params = free_params(dat->params);
		dat->n_cmds = 0;
	}
}

int	main(void)
{
	t_data	*data;

	data = get_data();
	init_data();
	run_minishell(data);
	builtin_exit(NULL);
	return (0);
}
