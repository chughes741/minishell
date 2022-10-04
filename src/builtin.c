/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/03 21:27:01 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	run_builtin(t_params *params)
{
	if (ft_strncmp(params->exec_arg[0], "echo", 5) == 0)
		builtin_echo(params->exec_arg[1], params->exec_arg[2]);
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
void	builtin_echo(char *str, char *opt)
{
	if (opt)
		printf("%s", opt);
	else
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

// Checks is variable name is valid
static bool	valid_name(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i] != '=')
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

// Replicates variable exporting
void	builtin_export(char *new_var)
{
	t_data	*d;

	if (!new_var)
		builtin_env();
	if (!valid_name(new_var))
	{
		perror("Not a valid variable name: ");
		return ;
	}
	d = get_data();
	d->envp = (char **)array_realloc((void **)d->envp, arraylen((void **)d->envp) + 1);
	d->envp[arraylen((void **)d->envp) - 1] = ft_strdup(new_var);
	return ;
}

// Replicates variable unset
void	builtin_unset(char *var_name)
{
	t_data	*data;
	int		pos;

	data = get_data();
	pos = 0;
	while (data->envp[pos]
		&& ft_strncmp(var_name, data->envp[pos], ft_strlen(var_name)))
		pos++;
	if (pos >= arraylen((void **)data->envp))
		return ;
	data->envp = (char **)array_del_one((void **)data->envp, pos);
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
