/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:16:01 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 12:18:04 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Frees all pointers in array and array
void	*free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		xfree(array[i]);
	xfree(array);
	return (NULL);
}
