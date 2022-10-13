/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/10/13 15:54:04 by chughes          ###   ########.fr       */
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
		return (ft_strdup(command));
	i = -1;
	paths = split_paths();
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		path = str_append(path, command);
		if (access(path, F_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		path = xfree(path);
	}
	free_array(paths);
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
	while (data->envp[++i] != NULL)
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
			paths = ft_split(data->envp[i], ':');
	}
	return (paths);
}
