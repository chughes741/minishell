/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/06 16:32:44 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_builtin(char *arg)
{
	if (ft_strncmp(arg, "echo", 5) == 0
		|| ft_strncmp(arg, "cd", 3) == 0
		|| ft_strncmp(arg, "pwd", 4) == 0
		|| ft_strncmp(arg, "export", 7) == 0
		|| ft_strncmp(arg, "unset", 6) == 0
		|| ft_strncmp(arg, "env", 4) == 0
		|| ft_strncmp(arg, "exit", 5) == 0
		|| ft_strncmp(arg, ">>", 3) == 0)
		return (true);
	else
		return (false);
}

void	run_builtin(t_params *params)
{
	if (ft_strncmp(params->exec_arg[0], "echo", 5) == 0)
		builtin_echo(params->exec_arg, params->fd_out);
	else if (ft_strncmp(params->exec_arg[0], "cd", 3) == 0)
		builtin_cd(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "pwd", 4) == 0)
		builtin_pwd(params->fd_out);
	else if (ft_strncmp(params->exec_arg[0], "export", 7) == 0)
		builtin_export(params->exec_arg);
	else if (ft_strncmp(params->exec_arg[0], "unset", 6) == 0)
		builtin_unset(params->exec_arg[1]);
	else if (ft_strncmp(params->exec_arg[0], "env", 4) == 0)
		builtin_env(params->fd_out);
	else if (ft_strncmp(params->exec_arg[0], "exit", 5) == 0)
		builtin_exit();
	else if (ft_strncmp(params->exec_arg[0], ">>", 3) == 0)
		here_doc(params->exec_arg[1], params->fd_out);
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

// Replicates the UNIX program echo
void	builtin_echo(char **args, int fd_write)
{
	bool	newline;
	int		i;

	i = 0;
	newline = true;
	if (args[1] != NULL && ft_strncmp(args[1], "-n\0", 3) == 0)
	{
		newline = false;
		i += 1;
	}
	while (args[++i] != NULL)
	{
		ft_putstr_fd(args[i], fd_write);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', fd_write);
	}
	if (newline == true)
		ft_putchar_fd('\n', fd_write);
	return ;
}

// Replicates the UNIX command cd
void	builtin_cd(char *new_dir)
{
	if (chdir(new_dir) == -1)
	{
		perror("cd: ");
	}
	return ;
}

// Replicated the UNIX command pwd
void	builtin_pwd(int fd_write)
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
	ft_putstr_fd(buf, fd_write);
	ft_putchar_fd('\n', fd_write);
	xfree(buf);
	return ;
}

// Checks is variable name is valid
static bool	valid_name(char *name)
{
	int	i;

	if (ft_isalpha(name[0]) == false && name[0] != '_')
		return (false);
	i = 1;
	while (name[i] != '=')
	{
		if (ft_isalnum(name[i]) == true || name[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

bool	env_var_exists(char *new_var, int i)
{
	t_data	*data;

	data = get_data();
	if (ft_strncmp(data->envp[i], new_var, ft_strlen_until(new_var, '=')) == 0)
		return (true);
	return (false);
}

void	insert_new_var(char *new_var)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = arraylen(data->envp);
	data->envp = array_realloc(data->envp, i + 1);
	data->envp[i] = ft_strdup(new_var);
}

// Replicates variable exporting
void	builtin_export(char **new_vars) //!Works flawlessly but too long
{
	t_data	*d;
	int		i;
	int		j;

	i = 0;
	if (new_vars == NULL)
	{
		builtin_env(STDOUT_FILENO);
		return ;
	}
	d = get_data();
	while (d->envp[i])
	{
		j = 1;
		while (new_vars[j])
		{
			if (valid_name(new_vars[j]) == false)
			{
				perror("Not a valid variable name: ");
				return ;
			}
			if (env_var_exists(new_vars[j], i) == true)
			{
				free(d->envp[i]);
				d->envp[i] = ft_strdup(new_vars[j]);
				i++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	j = 1;
	while (new_vars[j])
	{
		i = 0;
		while (env_var_exists(new_vars[j], i) == false)
		{
			i++;
			if (d->envp[i] == NULL)
				insert_new_var(new_vars[j]);
		}
		j++;
	}
}

// Replicates variable unset
void	builtin_unset(char *var_name)
{
	t_data	*data;
	int		pos;

	data = get_data();
	pos = 0;
	while (data->envp[pos] != NULL
		&& ft_strncmp(var_name, data->envp[pos], ft_strlen(var_name)))
		pos++;
	if (pos >= arraylen(data->envp))
		return ;
	data->envp = array_del_one(data->envp, pos);
	return ;
}

// Replicates the UNIX command env
void	builtin_env(int fd_write)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	while (data->envp[++i] != NULL)
	{
		ft_putstr_fd(data->envp[i], fd_write);
		ft_putchar_fd('\n', fd_write);
	}
	return ;
}

void	builtin_exit(void)
{
	del_data();
	exit(0);
}

// Writes here_doc input to fd
void	here_doc(char *key, int output_fd)
{
	char	*line;

	while (1)
	{
		line = readline(HD_PROMPT);
		if (ft_strncmp(line, key, ft_strlen(line)) != 0)
		{
			if (output_fd > 2)
				ft_putstr_fd(line, output_fd);
			xfree(line);
		}
		else
		{
			xfree(line);
			break ;
		}
	}
	return ;
}
