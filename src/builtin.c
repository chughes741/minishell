/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 17:19:47 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	run_builtin(t_params *params)
{
	if (ft_strncmp(params->exec_arg[0], "echo", 5))
		builtin_echo(params->exec_arg[1]);
	else if (ft_strncmp(params->envp[0], "cd", 5))
		builtin_cd(params->exec_arg[1]);
	else if (ft_strncmp(params->envp[0], "pwd", 5))
		builtin_pwd();
	else if (ft_strncmp(params->envp[0], "export", 5))
		builtin_export(params->exec_arg[1]);
	else if (ft_strncmp(params->envp[0], "unset", 5))
		builtin_unset(params->exec_arg[1]);
	else if (ft_strncmp(params->envp[0], "env", 5))
		builtin_env();
	else if (ft_strncmp(params->envp[0], "exit", 5))
		builtin_exit();
	else
		return (false);
	return (true);
}

// Replicates the UNIX program echo
void	builtin_echo(char *str)
{
	printf("%s\n", str);
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
void	builtin_export(char *new_var)
{
	printf("%s\n", new_var); //TODO set env var
	return ;
}

// Replicates variable unset
void	builtin_unset(char *var_name)
{
	printf("%s\n", var_name); //TODO unset env var
	return ;
}

// Replicates the UNIX command env
void	builtin_env(void)
{
	return ;
}

void	builtin_exit(void)
{
	t_data	*data;

	data = get_data();
	data->run = false;
	return ;
}
