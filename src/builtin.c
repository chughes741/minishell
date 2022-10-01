/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/01 14:06:16 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	run_builtin(t_params *params)
{
	if (ft_strncmp(params->exec_arg[0], "echo", 5) == 0)
		builtin_echo(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "cd", 3) == 0)
		builtin_cd(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "pwd", 4) == 0)
		printf("%s\n", builtin_pwd());
	else if (ft_strncmp(params->exec_arg[0], "export", 7) == 0)
		builtin_export(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "unset", 6) == 0)
		builtin_unset(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "env", 4) == 0)
		builtin_env();
	else if (ft_strncmp(params->exec_arg[0], "exit", 5) == 0)
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
	{
		perror("cd: ");
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
	buf = ft_calloc(size, sizeof(char));
	while (getcwd(buf, size) == NULL)
	{
		xfree(buf);
		size++;
		buf = ft_calloc(size, sizeof(char));
	}
	return (buf);
}

// Replicates variable exporting
void	builtin_export(char *new_var)
{
	t_data	*data;
	if (!new_var)
	{
		builtin_env(); //TODO print env with "declare -x" at the start of each line
	}
	data = get_data();
	data->envp = (char**)array_realloc((void**)data->envp, arraylen(data->envp) + 1);
	data->envp[arraylen(data->envp) - 1] = ft_strdup(new_var);
	return ;
}


//? Unsets from both env and export, 
// Replicates variable unset
void	builtin_unset(char *var_name)
{
	printf("%s\n", var_name); //TODO unset env var
	return ;
}

// Replicates the UNIX command env
void	builtin_env(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	while (data->envp[++i])
	{
		printf("%s\n", data->envp[i]);
	}
	return ;
}

void	builtin_exit(void)
{
	t_data	*data;

	data = get_data();
	data->run = false;
	return ;
}
