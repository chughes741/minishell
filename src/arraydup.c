/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraydup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:16:09 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 12:22:15 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Returns number of elements in array
int arraylen(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return 0;
}

// Returns clone of array
char	**arraydup(char **array)
{
	char	**newarray;
	int		i;

	if (array == NULL)
		return (NULL);
	newarray = (char**)ft_calloc(arraylen(array) + 1, sizeof(char*));
	i = -1;
	while (array[++i])
		newarray[i] = ft_strdup(array[i]);
	return (newarray);
}
