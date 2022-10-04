/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:39 by malord            #+#    #+#             */
/*   Updated: 2022/10/03 20:08:32 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/minishell.h"

// Returns the number of sub strings in between sep chars for calloc
static int	wordcount(char *str, char *metas)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((ft_strchr(metas, str[i]) && !ft_strchr(metas, str[i + 1]))
			|| (!ft_strchr(metas, str[i]) && str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

// Returns the sub string itself
static	char	*ft_trimword(char *str, char *metas, int index)
{
	int		i;
	char	*nstr;

	i = 0;
	nstr = ft_calloc(ft_strlen_before(str, metas) + 1, sizeof(char));
	if (!nstr)
		return (NULL);
	while (str[index])
	{
		if (ft_strchr(metas, str[index]))
			break ;
		nstr[i] = str[index];
		i++;
		index++;
	}
	nstr = ft_strtrim(nstr, " ");
	return (nstr);
}

/* Takes a string and return a 2D array, containing each string contained
	between one separating character contained in a charset*/
char	**split_metas(char *str, char *metas)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	if (!str)
		return (NULL);
	result = ft_calloc(sizeof(char *), wordcount(str, metas) + 1);
	i = -1;
	j = 0;
	index = -1;
	if (!result)
		return (NULL);
	while (++i <= (int)ft_strlen(str))
	{
		if (!ft_strchr(metas, str[i]) && index < 0)
			index = i;
		if (ft_strchr(metas, str[i])
			|| (i == (int)ft_strlen(str) && index >= 0))
		{
			result[j++] = ft_trimword(str, metas, index);
			index = -1;
		}
	}
	return (result);
}
