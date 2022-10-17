/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:05:16 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 10:48:38 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Splits a string at the index
char	**strnsplit(char *str, int index)
{
	char	**split;

	if (!str)
		return (NULL);
	split = (char **)ft_calloc(3, sizeof(char *));
	if (index == 0)
		split[0] = ft_strdup("");
	else
		split[0] = ft_strndup(str, index);
	split[1] = ft_strdup(&str[index]);
	str = xfree(str);
	return (split);
}
