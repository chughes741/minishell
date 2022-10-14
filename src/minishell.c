/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/14 13:24:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

void	run_minishell(t_data *dat)
{
	int	i;

	while (1)
	{
		i = 0;
		init_signals(INTERACTIVE);
		dat->last_cmd = readline(MSH_PROMPT);
		if (dat->last_cmd == NULL)
			return ;
		add_history(dat->last_cmd);
		while (ft_isspace(dat->last_cmd[i]) == 1)
			i++;
		dat->params = init_params(&dat->last_cmd[i]);
		i = 0;
		init_signals(RUNTIME);
		while (i < dat->n_cmds)
		{
			dat->run_cmd[cmd_idx(dat->params[i]->exec_arg[0])](dat->params[i]);
			i++;
		}
		wait_all(dat);
		dat->params = free_params(dat->params);
	}
}

int	main(void)
{
	t_data	*data;

	data = get_data();
	init_data(environ);
	run_minishell(data);
	builtin_exit(NULL);
	return (0);
}
