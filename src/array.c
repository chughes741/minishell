/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:16:09 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 15:26:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns number of elements in array
int	arraylen(char **array)
{
	int	len;

	len = 0;
	while (array && array[len])
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
	newarray = (char **)ft_calloc(arraylen(array) + 1, sizeof(char *));
	i = -1;
	while (array[++i] != NULL)
		newarray[i] = ft_strdup(array[i]);
	return (newarray);
}

// Allocs new array of void* of size bytes and copies ptrs from **ptr
char	**array_realloc(char **ptr, int size)
{
	char	**new_array;
	int		i;

	new_array = (char **)ft_calloc(size + 1, sizeof(char *));
	i = -1;
	while (ptr[++i] != NULL && i < size)
		new_array[i] = ptr[i];
	ptr = xfree(ptr);
	return (new_array);
}

// Deletes item in array, negative numbers start from end of array
char	**array_del_one(char **array, int position)
{
	char	**new_array;
	int		i;
	int		j;

	new_array = (char **)ft_calloc(arraylen(array), sizeof(char *));
	if (position < 0)
		position += arraylen(array) - 1;
	i = 0;
	j = 0;
	while (array[i] != NULL)
	{
		if (i != position)
		{
			new_array[j] = ft_strdup(array[i]);
			j++;
		}
		i++;
	}
	array = free_array(array);
	return (new_array);
}

// Frees all pointers in array and array
char	**free_array(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return (NULL);
	while (array[++i] != NULL)
		xfree(array[i]);
	xfree(array);
	return (NULL);
}
