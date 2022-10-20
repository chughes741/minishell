/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 14:42:22 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int realloc with new value to set
int	*int_add(int *old, int size, int new)
{
	int	*new_array;

	new_array = int_realloc(old, size, size + 1);
	new_array[size] = new;
	return (new_array);
}

// Returns an array of integers containing the positions of quotes in a string
int	*get_split_indices(char *arg)
{
	int	index;
	int	len;
	int	*quotes;

	index = 0;
	len = 1;
	quotes = ft_calloc(len + 1, sizeof(int));
	while (arg[index])
	{
		if (arg[index] == '\"' || arg[index] == '\'')
		{
			if (quote_skip(&arg[index]) == -1)
				return (xfree(quotes));
			index += (quote_skip(&arg[index]));
		}
		else if (arg[index] == '|')
		{
			quotes = int_add(quotes, len, index);
			len++;
		}
		index++;
	}
	quotes = int_add(quotes, len, index);
	quotes[len + 1] = -1;
	return (quotes);
}

// Returns number of ints in an int*, until first -1
int	intlen(int *intstr)
{
	int	len;

	len = 0;
	while (intstr && intstr[len] != -1)
		len++;
	return (len);
}

// Returns array of strings, splits cmd on | and <<, accounts for quotes
char	**split_command_groups(char *cmd)
{
	char	**cmd_strs;
	char	*temp;
	int		*idxs;
	int		i;

	temp = ft_strtrim(cmd, " ");
	if (temp == NULL || temp[0] == '\0')
		return (xfree(temp));
	idxs = get_split_indices(temp);
	if (idxs == NULL)
	{
		temp = xfree(temp);
		return (NULL);
	}
	cmd_strs = (char **)ft_calloc(intlen(idxs) + 1, sizeof(char *));
	i = 0;
	while (idxs && idxs[i + 1] >= 0)
	{
		cmd_strs[i] = ft_substr(temp, idxs[i], idxs[i + 1] - idxs[i] + 1);
		++i;
	}
	temp = xfree(temp);
	idxs = xfree(idxs);
	return (cmd_strs);
}
