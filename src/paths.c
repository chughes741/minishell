/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 18:55:42 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Uses access to find the correct path 
char	*get_path(char **paths, char *command)
{
	char	*path;
	int		i;

	i = -1;
	path = ft_strdup(command);
	if (access(path, F_OK) == 0)
		return (path);
	path = ft_strjoin("./", command);
	if (access(path, F_OK) == 0)
		return (path);
	xfree(path);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_str_prepend(path, command);
		if (access(path, F_OK) == 0)
			return (path);
		xfree(path);
	}
	return (NULL);
}

// Returns a new string with the PATH from env
char	**split_paths(void)
{
	char	*path;
	char	**paths;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	return (paths);
}
