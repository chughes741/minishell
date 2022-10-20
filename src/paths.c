/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:35 by chughes           #+#    #+#             */
/*   Updated: 2022/10/19 19:58:54 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Uses access to find the correct path 
char	*get_path(char *command)
{
	char	*path;
	char	**paths;
	int		i;

	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	path = get_var(ft_strdup("PATH"));
	paths = ft_split(path, ':');
	path = xfree(path);
	i = -1;
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
	if (cmd_idx(command) == 7)
		perror("Command not found");
	free_array(paths);
	return (NULL);
}
