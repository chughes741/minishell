/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 11:33:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			quotes = int_realloc(quotes, len, len + 1);
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

// Returns index of 
int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] == ' ')
		++i;
	while (str && (str[i] == '<' || str[i] == '>'))
		++i;
	while (str && str[i] == ' ')
		++i;
	return (i);
}

// strpop without allocation
static void	strpopmove(char *str, int position)
{
	int	i;

	i = 0;
	while (str && str[i] && i < position)
		++i;
	while (str && str[i])
	{
		str[i] = str[i + 1];
		++i;
	}
	return ;
}

//! TESTING
int	*get_arg_indices(char *arg)
{
	int	index;
	int	len;
	int	*quotes;

	index = 0;
	len = 1;
	quotes = ft_calloc(len + 1, sizeof(int));
	while (arg[index])
	{
		while (arg[index] == ' ')
			++index;
		quotes = int_realloc(quotes, len, len + 1);
		quotes[len] = index;
		len++;
		if (ft_strncmp(&arg[index], ">>", 2) == 0
			|| ft_strncmp(&arg[index], "<<", 2) == 0)
			++index;
		if ((arg[index] == '>' || arg[index] == '<') && arg[index + 1] == ' ')
		{
			while (arg[index + 1] == ' ')
				strpopmove(arg, index + 1);
		}
		if (arg[index] == '\'' || arg[index] == '\"')
			index += quote_skip(&arg[index]);
		while (arg[index] && arg[index] != ' ')
		{
			++index;
			if (arg[index] == '<' || arg[index] == '>')
				break;
		}
	}
	quotes = int_realloc(quotes, len, len + 1);
	quotes[len] = index;
	quotes[len + 1] = -1;
	return (quotes);
	exit(0);
}

//! TESTING
char	**split_args(char *cmd)
{
	char	**args;
	char	*temp;
	int		*indices;
	int		i;

	temp = ft_strtrim(cmd, " |");
	if (temp == NULL || temp[0] == '\0')
	{
		perror("Syntax error");
		temp = xfree(temp);
		return ((char **)ft_calloc(1, sizeof(char *)));
	}
	indices = get_arg_indices(temp);
	if (indices == NULL)
		return (NULL);
	args = (char **)ft_calloc(intlen(indices) + 1, sizeof(char *));
	i = 0;
	while (indices && indices[i + 1] >= 0)
	{
		args[i] = ft_substr(temp, indices[i], indices[i + 1] - indices[i]);
		++i;
	}
	if (indices[1] == 0)
		args = array_del_one(args, 0);
	temp = xfree(temp);
	indices = xfree(indices);
	return (args);
}
