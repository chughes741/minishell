/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:16:09 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 14:49:24 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Returns number of elements in array
int	arraylen(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

// Returns clone of array
char	**arraydup(char **array)
{
	char	**newarray;
	int		i;

	if (array == NULL)
		return (NULL);
	newarray = ft_calloc(arraylen(array) + 1, sizeof(char *));
	i = -1;
	while (array[++i])
		newarray[i] = ft_strdup(array[i]);
	return (newarray);
}

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

// Deletes item in array, negative numbers start from end of array
void	**array_del_one(void **array, int position)
{
	void	**new_array;
	int		i;
	int		j;

	new_array = ft_calloc(arraylen((char **)array), sizeof(void *));
	if (position < 0)
		position += arraylen((char **)array) - 1;
	i = 0;
	j = 0;
	while (array[i])
	{
		if (i == position)
			xfree(array[i]);
		else
		{
			new_array[j] = array[i];
			j++;
		}
		i++;
	}
	return (new_array);
}

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