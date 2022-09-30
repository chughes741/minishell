/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:59 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 12:14:36 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Allocs new array of void* of size bytes and copies ptrs from **ptr
void	**array_realloc(void **ptr, int size)
{
	void	**new_array;
	int		i;

	new_array = ft_calloc(size + 1, sizeof(void *));	
	i = -1;
	while (ptr[++i] && i < size)
		new_array[i] = ptr[i];
	ptr = xfree(ptr);
	return (new_array);
}
