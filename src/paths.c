/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 15:08:47 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Uses access to find the correct path 
char	*get_path(char *command)
{
	// SIGSEGV when $PATH is unset
	char	*path;
	char	**paths;
	int		i;

	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	i = -1;
	path = get_var(ft_strdup("PATH"));
	paths = ft_split(path, ':');
	path = xfree(path);
	while (paths && paths[++i] != NULL)
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
	if (paths == NULL || cmd_idx(command) == 8)
		perror("Command not found");
	free_array(paths);
	return (NULL);
}
