/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/14 08:23:37 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	run_minishell(t_data *dat)
{
	int	i;

	while (1)
	{
		i = 0;
		init_signals(INTERACTIVE);
		dat->n_cmds = 0;
		dat->last_cmd = readline(MSH_PROMPT);
		if (dat->last_cmd == NULL)
			break ;
		add_history(dat->last_cmd);
		while (ft_isspace(dat->last_cmd[i]) == 1)
			i++;
		dat->params = parse_args(&dat->last_cmd[i]);
		i = 0;
		init_signals(RUNTIME);
		while (i < dat->n_cmds)
		{
			dat->run_cmd[cmd_idx(dat->params[i]->exec_arg[0])](dat->params[i]);
			i++;
		}
		wait_all(dat);
		dat->params = free_params(dat->params);
		xfree(dat->last_cmd);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = get_data();
	init_data(envp);
	if (argc != 1 || argv[0] == NULL)
		data->run = false;
	run_minishell(data);
	del_data();
	return (0);
}
