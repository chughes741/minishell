/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:59 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 14:06:32 by chughes          ###   ########.fr       */
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
