/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:17:10 by chughes           #+#    #+#             */
/*   Updated: 2022/10/06 21:36:54 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Frees all param structs in an array, returns NULL
void	free_params(t_params **params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		xfree(params[i]->path);
		free_array(params[i]->exec_arg);
		xfree(params[i]->in_path);
		xfree(params[i]->out_path);
		++i;
	}
	free_array((char **)params);
	params = NULL;
	return ;
}
