/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 10:11:49 by chughes          ###   ########.fr       */
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
static void	run_minishell(t_data *d)
{
	int	i;

	while (1)
	{
		init_signals(INTERACTIVE);
		d->last_cmd = call_prompt();
		if (d->last_cmd == NULL)
			break ;
		d->params = init_params(d->last_cmd);
		i = 0;
		init_signals(RUNTIME);
		while (i < d->n_cmds && d->params[i]->exec_arg[0] != NULL)
		{
			if (d->params[i]->err == false)
				d->run_cmd[cmd_idx(d->params[i]->exec_arg[0])](d->params[i]);
			i++;
		}
		wait_all(d);
		d->params = free_params(d->params);
		d->n_cmds = 0;
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
