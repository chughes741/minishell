/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:01 by chughes           #+#    #+#             */
/*   Updated: 2022/09/22 14:37:30 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define RL_HIST "log/rl_history.log"
#define ERROR_LOG "log/error.log"

// Initializes data struct
void	init_data(char *envp[])
{
	t_data	*data;

	data = get_data();
	data->paths = split_paths(envp);
	data->envp = envp;
	data->rl_history_fd = open(RL_HIST, O_RDWR | O_APPEND | O_CREAT);
	#ifdef DEBUG
	data->error_log_fd = open(ERROR_LOG, O_RDONLY | O_APPEND | O_CREAT);
	#endif
	return ;
}

// Singleton constructor for data struct
t_data	*get_data(void)
{
	static	t_data	*data = NULL;

	if (data == NULL)
		data = ft_calloc(1, sizeof(t_data));
	return (data);
}

// Deletes data struct
void	del_data(void)
{
	t_data	*data;

	data = get_data();
	close(data->rl_history_fd);
	#ifdef DEBUG
	close(data->error_log_fd);
	#endif
	if (data)
		free(data);
	return ;
}
