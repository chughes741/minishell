/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:51:33 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 14:00:05 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_params	*cmd_parse(char *line)
{
	t_data		*data;
	t_params	*params;

	data = get_data();
	params = ft_calloc(1, sizeof(t_params));
	params->exec_arg = ft_split(line, ' ');
	params->path = get_path(data->paths, ft_strdup(params->exec_arg[0]));
	params->envp = 	data->envp;
	params->fd_in = STDIN_FILENO;
	params->fd_out = STDOUT_FILENO;
	
	return (params);
}
