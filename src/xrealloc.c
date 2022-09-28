/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xrealloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:59 by chughes           #+#    #+#             */
/*   Updated: 2022/09/28 16:20:15 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Reallocates new array of void* of size bytes
void	*xrealloc(void *ptr, size_t size)
{
	void	*new_array;

	new_array = (void*)ft_calloc(size, sizeof(void *));	
	ft_memcpy(new_array, ptr, sizeof(void*));
	return (NULL);
}
