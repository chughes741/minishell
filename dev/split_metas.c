/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_metas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:38:39 by malord            #+#    #+#             */
/*   Updated: 2022/09/30 13:28:41 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"

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
/*static int	ft_wordlen(char const *s, char *metas, int cpt)
{
	int	len;

	len = 0;
	while (s[cpt] != metas && s[cpt] != '\0')
	{
		len++;
		cpt++;
	}
	return (len);
}*/

// Returns the sub string itself
static	char	*ft_trimword(char const *s, char *metas, int cpt)
{
	int		j;
	char	*nstr;

	j = 0;
	nstr = ft_calloc(ft_wordlen(s, metas, cpt) + 1, sizeof(char));
	if (!nstr)
		return (NULL);
	while (s[cpt])
	{
		if (s[cpt] != metas)
		{
			nstr[j] = s[cpt];
			if (s[cpt + 1] == metas || s[cpt + 1] == '\0')
				break ;
			else
			{
				cpt++;
				j++;
			}	
		}
		else
			cpt++;
	}
	return (nstr);
}

/* Takes a string and return a 2D array, containing each string contained
	between one separating character contained in a charset*/
char	**split_metas(char const *s, char *metas)
{
	char	**result;
	int		i;
	int		j;
	int		index;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), ft_wordcount(s, metas));
	i = 0;
	j = 0;
	index = -1;
	if (!result)
		return (NULL);
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] != metas && index < 0)
			index = i;
		else if ((s[i] == metas || i == (int)ft_strlen(s)) && index >= 0)
		{
			result[j++] = ft_trimword(s, metas, index);
			index = -1;
		}
		i++;
	}
	return (result);
}

int main(void)
{
	char	*str = "echo f > file # bonjour";
	char	**result;
	result = split_metas(str);
	int i = 0;
	while (result[i])
	{
		printf("Contenu de result[i] = %s\n", result[i]);
		i++;
	}
}