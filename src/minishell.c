/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/21 13:44:36 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	data = get_data();
	init_data(envp);
	while (1)
	{
		prompter();
		parse_args();
		while (1) //TODO change while condition
		{
			exe();
			waitpid(data->params->id, &data->exit_status, 0);
			if (WIFEXITED(data->exit_status) != 0)
				error_handler();
		}
	}
	cleanup();
	exit(0);
}
