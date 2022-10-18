/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:17:10 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 15:19:26 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Frees all param structs in an array, returns NULL
t_params	**free_params(t_params **params)
{
	int	i;

	i = 0;
	if (params)
	{
		while (params[i])
		{
			params[i]->path = xfree(params[i]->path);
			params[i]->exec_arg = free_array(params[i]->exec_arg);
			params[i]->in_path = xfree(params[i]->in_path);
			params[i]->out_path = xfree(params[i]->out_path);
			params[i] = xfree(params[i]);
			++i;
		}
		params = xfree(params);
	}
	return (NULL);
}
