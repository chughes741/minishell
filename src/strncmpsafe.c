/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmpsafe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:27:16 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 17:40:47 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	strncmpsafe(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (true);
		if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
			return (false)
		++i;
	}
	return (true);
}
