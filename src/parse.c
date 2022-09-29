/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 17:31:51 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_params	**parse_args(char *cmd)
{
	t_data		*data;
	t_params	**params;

	data = get_data();
	params = ft_calloc(2, sizeof(t_params*));
	params[0] = cmd_parse(cmd);
	data->n_cmds = 1;
	return (params);
}
