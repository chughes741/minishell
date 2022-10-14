/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:18:58 by chughes           #+#    #+#             */
/*   Updated: 2022/10/14 13:19:11 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Fuck norminette
static void	fuck_norm(int *level, int *quote, int i_lvl, int new_quote)
{
	*level += i_lvl;
	*quote = new_quote;
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
		if (nest_level == 0 || str[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
