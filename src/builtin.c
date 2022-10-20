/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 15:29:38 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Replicates the UNIX program echo
void	builtin_echo(t_params *params)
{
	bool	newline;
	int		i;

	i = 0;
	newline = true;
	if (params->exec_arg[1] != NULL
		&& ft_strncmp(params->exec_arg[1], "-n\0", 3) == 0)
	{
		newline = false;
		i += 1;
	}
	while (params->exec_arg[++i] != NULL)
	{
		ft_putstr_fd(params->exec_arg[i], params->fd_out);
		if (params->exec_arg[i + 1] != NULL)
			ft_putchar_fd(' ', params->fd_out);
	}
	if (newline == true)
		ft_putchar_fd('\n', params->fd_out);
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

// If you think this is a trick to pass norminette, you're right
static void	end_cd(char *buf, int pos)
{
	buf = str_prepend("PWD=", buf);
	pos = env_var_exists(buf);
	insert_new_var(buf, pos);
	buf = xfree(buf);
}

// Replicates the UNIX command cd
void	builtin_cd(t_params *params)
{
	char	*buf;
	int		size;
	int		pos;

	size = 0;
	pos = 0;
	if (params->exec_arg[1] == NULL)
		return ;
	buf = (char *)ft_calloc(size, sizeof(char));
	if (chdir(params->exec_arg[1]) == -1)
	{
		perror("cd: ");
		buf = xfree(buf);
	}
	else
	{
		while (getcwd(buf, size) == NULL)
		{
			xfree(buf);
			size++;
			buf = (char *)ft_calloc(size, sizeof(char));
		}
		end_cd(buf, pos);
	}
}

// Replicated the UNIX command pwd
void	builtin_pwd(t_params *params)
{	
	char	*buf;
	int		size;

	buf = NULL;
	size = 1;
	buf = (char *)ft_calloc(size, sizeof(char));
	while (getcwd(buf, size) == NULL)
	{
		xfree(buf);
		size++;
		buf = (char *)ft_calloc(size, sizeof(char));
	}
	ft_putstr_fd(buf, params->fd_out);
	ft_putchar_fd('\n', params->fd_out);
	close_file(params->fd_in);
	close_file(params->fd_out);
	xfree(buf);
	return ;
}
