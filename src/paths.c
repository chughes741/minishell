/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/09/08 12:32:53 by chughes          ###   ########.fr       */
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
	free(path);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_str_prepend(path, command);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	exit_error("Cannot find path to program: ");
	return (NULL);
}

// Returns a new string with the PATH from envp
char	**find_path(char *envp[])
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_strdup(&envp[i][5]);
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}
