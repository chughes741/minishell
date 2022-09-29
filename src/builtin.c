/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 16:29:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Replicates the UNIX program echo
void	builtin_echo(void)
{
	return ;
}

// Replicates the UNIX command cd
void	builtin_cd(char *new_dir)
{
	int	success;

	success = chdir(new_dir);
	if (success == -1)
	{ // cd: no such file or directory: $new_dir
		perror("cd: no such file or directory: "); //TODO handle cd errors
	}
	return ;
}

// Replicated the UNIX command pwd
char	*builtin_pwd(void)
{
	char	*buf;
	int		size;

	buf = NULL;
	size = 0;
	while (buf == NULL)
	{
		xfree(buf);
		size++;
		buf = ft_calloc(size, sizeof(char));
		getcwd(buf, size);
	}
	return (buf);
}

// Replicates variable exporting
void	builtin_export(void)
{
	return ;
}

// Replicates variable unset
void	builtin_unset(void)
{
	return ;
}

// Replicates the UNIX command env
void	builtin_env(void)
{
	return ;
}
