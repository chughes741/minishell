/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 08:55:02 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../include/minishell.h"

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
		else if (arg[index] == '|' 
			|| (ft_strncmp(&arg[index], "<<", 2) == 0 && index != 0))
		{
			quotes = int_realloc(quotes, len, len + 1);
			quotes[len] = index;
			len++;
		}
		else if (ft_strncmp(&arg[index], "<<", 2) == 0)
		{
			quotes = int_realloc(quotes, len, len + 1);
			index += find_next(&arg[index], " ");
			quotes[len] = index;
			len++;
		}
		index++;
	}
	quotes = int_realloc(quotes, len, len + 1);
	quotes[len] = index;
	quotes[len + 1] = -1;
	return (quotes);
}

// Returns number of ints in an int*, until first -1
static int	intlen(int *intstr)
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
	int		*indices;
	int		i;

	temp = ft_strtrim(cmd, " ");
	if (temp == NULL || temp[0] == '\0')
		return (xfree(temp));
	indices = get_split_indices(temp);
	if (indices == NULL)
		return (NULL);
	cmd_strs = (char **)ft_calloc(intlen(indices) + 1, sizeof(char *));
	i = 0;
	while (indices && indices[i + 1] >= 0)
	{
		cmd_strs[i] = ft_substr(temp, indices[i], indices[i + 1] - indices[i] + 1);
		++i;
	}
	temp = xfree(temp);
	indices = xfree(indices);
	return (cmd_strs);
}

// Splits arguments keeping quoted sections together
char	**split_args(char *str)
{
	char	**rtn;
	char	*temp;
	int		start;
	int		end;

	rtn = (char **)ft_calloc(1, sizeof(char *));
	start = 0;
	temp = ft_strtrim(str, " |");
	while (temp[start])
	{
		// TODO invalid read on temp
		if (ft_strchr(" \"\'", temp[start]) == NULL)
			end = find_next(&temp[start], " ") + start;
		else if (temp[start] == ' ')
			end++;
		else if (ft_strchr("\'\"", temp[start]))
			end = quote_skip(&temp[start]) + start;
		else
			end = ft_strlen(&temp[start] - 1);
		if (end > start && start < (int)ft_strlen(temp) - 1)
		{
			rtn = array_realloc(rtn, arraylen(rtn) + 1);
			rtn[arraylen(rtn)] = ft_substr(temp, start, end - start + 1);
		}
		if (!temp[end + 1]) // Couldn't be if (!temp[start + end])
			break ;
		start = end + 1;
	}
	temp = xfree(temp);
	return (rtn);
}
