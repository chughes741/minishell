/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:01 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 13:55:12 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Initializes data struct
void	init_data(char *envp[])
{
	t_data	*data;

	data = get_data();
	data->paths = split_paths(envp);
	data->envp = envp;
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
	if (data)
		free(data);
	return ;
}
