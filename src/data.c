/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:01 by chughes           #+#    #+#             */
/*   Updated: 2022/10/03 21:27:25 by chughes          ###   ########.fr       */
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
	data->run = true;
	data->envp = (char **)arraydup((void **)envp);
	#ifdef DEBUG
	data->rl_history_fd = open(RL_HIST, O_RDWR | O_APPEND | O_CREAT);
	data->error_log_fd = open(ERROR_LOG, O_RDONLY | O_APPEND | O_CREAT);
	load_history();
	#endif
	return ;
}

// Singleton constructor for data struct
t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (data == NULL)
		data = ft_calloc(1, sizeof(t_data));
	return (data);
}

// Deletes data struct
void	del_data(void)
{
	t_data	*data;

	data = get_data();
	#ifdef DEBUG
	close(data->rl_history_fd);
	close(data->error_log_fd);
	#endif
	//TODO Loop to xfree params array
	free_array((void **)data->envp);
	xfree(data->last_cmd);
	xfree(data);
	return ;
}
