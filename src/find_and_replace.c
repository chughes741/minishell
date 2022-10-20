/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:55:39 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:36:18 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Finds and replaces all chrs in str with replace for len number of chars
void	find_and_replace(char *str, char *chrs, char replace, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (ft_strchr(chrs, str[i]) != NULL)
			str[i] = replace;
		++i;
	}
	return ;
}

// Returns index of first chrs in str
int	find_first(char *str, char *chrs)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(chrs, str[i]) == NULL)
		++i;
	return (i);
}

// Returns index of last chrs in str
int	find_last(char *str, char *chrs)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_strchr(chrs, str[i]) == NULL)
		++i;
	return (i);
}
