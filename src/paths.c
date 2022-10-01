/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 16:45:03 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Uses access to find the correct path 
char	*get_path(char *command)
{
	char	*path;
	char	**paths;
	int		i;

	if (access(command, F_OK) == 0)
		return (command);
	i = -1;
	paths = split_paths();
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
	t_data	*data;
	char	**paths;
	int		i;

	data = get_data();
	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			paths = ft_split(data->envp[i], ':');
	}
	if (paths)
	{
		paths = (char **)array_realloc((void **)paths, arraylen(paths) + 1);
		paths[arraylen(paths)] = builtin_pwd();
		return (paths);
	}
	return (NULL);
}
