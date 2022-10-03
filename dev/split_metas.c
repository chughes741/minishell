/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:39 by malord            #+#    #+#             */
/*   Updated: 2022/10/03 17:01:12 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/minishell.h"

// Returns the number of sub strings in between sep chars for calloc
static int	wordcount(char const *str, char *metas)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		j = 0;
		while (metas[j])
		{
			if ((str[i] == metas[j] && str[i + 1] != metas[j])
				|| (str[i] != metas[j] && str[i + 1] == '\0'))
			{
				words++;
				break ;
			}
			else
				j++;
		}
		i++;
	}
	return (words);
}

// Returns the length of a sub string for calloc
static int	wordlen(char const *str, char *metas, int cpt)
{
	int	len;
	int	i;

	len = 0;
	while (str[cpt])
	{
		i = 0;
		while (metas[i])
		{
			if (str[cpt] == metas[i])
				return (len);
			else
				i++;
		}
		len++;
		cpt++;
	}
	return (len);
}

// Returns the sub string itself
static	char	*ft_trimword(char const *str, char *metas, int cpt)
{
	int		j;
	int		i;
	int		flag;
	char	*nstr;

	i = 0;
	flag = 0;
	nstr = ft_calloc(wordlen(str, metas, cpt) + 1, sizeof(char));
	if (!nstr)
		return (NULL);
	while (str[cpt])
	{
		j = 0;
		while (metas[j])
		{
			if (str[cpt] != metas[j])
				j++;
			else
			{
				flag = 1;
				break ;
			}
		}
		if (flag == 1)
			break ;
		nstr[i] = str[cpt];
		i++;
		cpt++;
	}
	nstr = ft_strtrim(nstr, " ");
	return (nstr);
}

/* Takes a string and return a 2D array, containing each string contained
	between one separating character contained in a charset*/
char	**split_metas(char const *str, char *metas)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	if (!str)
		return (NULL);
	result = ft_calloc(sizeof(char *), wordcount(str, metas) + 1);
	i = 0;
	j = 0;
	index = -1;
	if (!result)
		return (NULL);
	while (i <= (int)ft_strlen(str))
	{
		if (!ft_strchr(metas, str[i]) && index < 0)
			index = i;
		if (ft_strchr(metas, str[i])
			|| (i == (int)ft_strlen(str) && index >= 0))
		{
			result[j++] = ft_trimword(str, metas, index);
			index = -1;
		}
		i++;
	}
	return (result);
}

int main(void)
{
	char	*str = "fuck | teawith milk\" minishellIhateyou";
	int		i = 0;
	char	 **split = split_metas(str, "|>\"");
	while (split[i])
	{
		printf("contenu de split[i] = %s\n", split[i]);
		i++;
	}
}
