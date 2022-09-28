/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:04:49 by chughes           #+#    #+#             */
/*   Updated: 2022/09/28 12:55:30 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Loads and adds rl_history from log file
void	load_history(void)
{
	t_data	*data;
	char	*log_str;

	data = get_data();
	log_str = get_next_line(data->rl_history_fd);
	while (log_str)
	{
		add_history(log_str);
		xfree(log_str);
		log_str = get_next_line(data->rl_history_fd);
	}
	return ;
}

// Adds cmd to rl_history and history log
void	log_history(char *cmd)
{
	t_data	*data;

	data = get_data();
	add_history(cmd);
	dprintf(data->rl_history_fd, "%s\n", cmd); //! Can't use dprintf for this
	return ;
}
