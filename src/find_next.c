/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:04:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 10:46:14 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns index of next chr match in str
int	find_next(char *str, char *chr)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(chr, str[i]) == NULL)
		++i;
	return (i);
}
