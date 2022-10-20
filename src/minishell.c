/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 10:09:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles readline and history for prompt
static char	*call_prompt(void)
{
	char	*line;

	line = readline(MSH_PROMPT);
	while (line && line[0] == '\0')
		line = readline(MSH_PROMPT);
	if (line)
		add_history(line);
	return (line);
}

// Runtime loop
static void	run_minishell(t_data *dat)
{
	int	i;

	while (1)
	{
		init_signals(INTERACTIVE);
		dat->last_cmd = call_prompt();
		if (dat->last_cmd == NULL)
			break ;
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
