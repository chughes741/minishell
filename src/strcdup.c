/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:44:50 by chughes           #+#    #+#             */
/*   Updated: 2022/09/20 12:55:06 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Returns dupe of basestring until first char in match or \0
char	*strcdup(char *basestr, char *matchchrs)
{
	char	*dupstr;
	int		i;

	i = 0;
	while (ft_strchr(matchchrs, basestr[i]) == 0)
		++i;
	dupstr = (char *)ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(dupstr, basestr, i);
	return (dupstr);
}
