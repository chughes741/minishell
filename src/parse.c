/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 14:04:59 by chughes          ###   ########.fr       */
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
	int		*idxs;
	int		i;

	temp = ft_strtrim(cmd, " ");
	if (temp == NULL || temp[0] == '\0')
		return (xfree(temp));
	idxs = get_split_indices(temp);
	if (idxs == NULL)
		return (NULL);
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

// A garbage function to get around norm
void	increment(char *arg, int *i)
{
	if (ft_strncmp(&arg[*i], ">>", 2) == 0
		|| ft_strncmp(&arg[*i], "<<", 2) == 0)
		*i += 1;
	if ((arg[*i] == '>' || arg[*i] == '<') && arg[*i + 1] == ' ')
	{
		while (arg[*i + 1] == ' ')
			strpopmove(arg, *i + 1);
	}
	if (arg[*i] == '\'' || arg[*i] == '\"')
		*i += quote_skip(&arg[*i]);
	while (arg[*i] && arg[*i] != ' ')
	{
		*i += 1;
		if (arg[*i] == '<' || arg[*i] == '>')
			break ;
	}
}

// Generates a int str of indexs to split args
int	*get_arg_indices(char *arg)
{
	int	i;
	int	len;
	int	*quotes;

	i = 0;
	len = 1;
	quotes = ft_calloc(len + 1, sizeof(int));
	while (arg[i])
	{
		while (arg[i] == ' ')
			++i;
		quotes = int_add(quotes, len, i);
		len++;
		increment(arg, &i);
	}
	quotes = int_add(quotes, len, i);
	quotes[len + 1] = -1;
	return (quotes);
	exit(0);
}

// Splits arguments into an array of strs
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
	i = -1;
	while (indices && indices[++i + 1] >= 0)
		args[i] = ft_substr(temp, indices[i], indices[i + 1] - indices[i]);
	if (indices[1] == 0)
		args = array_del_one(args, 0);
	temp = xfree(temp);
	indices = xfree(indices);
	return (args);
}
