/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:18:58 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 10:47:20 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fuck norminette
static void	fuck_norm(int *level, int *quote, int i_lvl, int new_quote)
{
	*level += i_lvl;
	*quote = new_quote;
}

/* Checks the number of single and double quotes, returns true if equal and
	more than 3 overall*/
bool	check_quotes(char *str)
{
	int	i;
	int	singles;
	int	doubles;

	i = 0;
	singles = 0;
	doubles = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			doubles++;
		else if (str[i] == '\'')
			singles++;
		i++;
	}
	if (doubles + singles == 3 || (doubles % 2 == 0 && singles % 2 == 0))
		return (true);
	return (false);
}

// Returns index of closing quote, skips nested quotes
int	quote_skip(char *str)
{
	int	i;
	int	nest_level;
	int	quote;

	i = 0;
	nest_level = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote != 1)
			fuck_norm(&nest_level, &quote, 1, 1);
		else if (str[i] == '\"' && quote != 2)
			fuck_norm(&nest_level, &quote, 1, 2);
		else if (str[i] == '\'' && quote == 1)
			fuck_norm(&nest_level, &quote, -1, 2);
		else if (str[i] == '\"' && quote == 2)
			fuck_norm(&nest_level, &quote, -1, 1);
		if (nest_level == 0)
			return (i);
		i++;
	}
	if (str[0] == str[i - 1] && check_quotes(str) == true)
		return (i);
	perror("Syntax error: ");
	return (-1);
}
