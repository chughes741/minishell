/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:24:42 by chughes          ###   ########.fr       */
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

// Replicates the UNIX command cd
void	builtin_cd(t_params *params)
{
	char	*buf;
	int		size;
	int		pos;

	size = 0;
	if (params->exec_arg[1] == NULL)
		return ;
	buf = (char *)ft_calloc(size, sizeof(char));
	if (chdir(params->exec_arg[1]) == -1)
		perror("cd: ");
	else
	{
		while (getcwd(buf, size) == NULL)
		{
			xfree(buf);
			size++;
			buf = (char *)ft_calloc(size, sizeof(char));
		}
		buf = str_prepend("PWD=", buf);
		pos = env_var_exists(buf);
		insert_new_var(buf, pos);
		buf = xfree(buf);
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

// Replicates the UNIX command env
void	builtin_env(t_params *params)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	while (data->envp[++i] != NULL)
	{
		ft_putstr_fd(data->envp[i], params->fd_out);
		ft_putchar_fd('\n', params->fd_out);
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

void	builtin_exit(t_params *params)
{
	(void)params;
	del_data();
	printf("exit\n");
	exit(0);
}
