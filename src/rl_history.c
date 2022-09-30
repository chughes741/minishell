/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:04:49 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 18:04:46 by chughes          ###   ########.fr       */
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

// Adds cmd to rl_history and history log if in debug
void	log_history(char *cmd)
{
	#ifdef DEBUG
	t_data	*data;

	data = get_data();
	dprintf(data->rl_history_fd, "%s\n", cmd); //! Can't use dprintf for this
	#endif
	add_history(cmd);
	return ;
}
