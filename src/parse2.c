/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:27:48 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:31:46 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				break ;
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
