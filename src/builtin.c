/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 18:55:03 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**envp;

// Returns index of cmd to call cmd function pointer from cmd array
int	cmd_idx(char *arg)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	if (!arg)
		return (0);
	while (data->cmd_names[i])
	{
		if (!ft_strncmp(arg, data->cmd_names[i], ft_strlen(data->cmd_names[i]) + 1))
			break ;
		++i;
	}
	return (i);
}

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

// Checks is variable name is valid
static bool	valid_name(char *name)
{
	int		i;
	int		j;
	char	**split_name;

	split_name = ft_split(name, '=');
	if (ft_isalpha(name[0]) == false && name[0] != '_')
	{
		split_name = free_array(split_name);
		return (false);
	}
	j = 0;
	i = 1;
	while (split_name[i])
	{
		if (ft_isalnum(split_name[0][j]) == true || split_name[0][j] == '_')
			i++;
		else
		{
			split_name = free_array(split_name);
			return (false);
		}
	}
	split_name = free_array(split_name);
	return (true);
}

// Returns position of var in envp, -1 if it does not exist
int	env_var_exists(char *new_var)
{
	char	*new_var_name;
	int		pos;

	pos = 0;
	new_var_name = strcdup(new_var, "=");
	while (envp[pos])
	{
		if (ft_strncmp(envp[pos], new_var_name, ft_strlen(new_var_name)) == 0)
		{
			new_var_name = xfree(new_var_name);
			return (pos);
		}
		pos++;
	}
	new_var_name = xfree(new_var_name);
	return (-1);
}

// Inserts new_var at pos, appends if pos is -1
void	insert_new_var(char *new_var, int pos)
{
	if (pos == -1)
	{
		pos = arraylen(envp);
		envp = array_realloc(envp, pos + 1);
	}
	else
		envp[pos] = xfree(envp[pos]);
	envp[pos] = ft_strdup(new_var);
}

// Replicates variable exporting
void	builtin_export(t_params *params)
{
	int		i;
	int		pos;

	if (params->exec_arg[1] == NULL)
	{
		builtin_env(params);
		return ;
	}
	i = 1;
	while (params->exec_arg[i])
	{
		if (valid_name(params->exec_arg[i]) == false)
		{
			perror("Not a valid variable name: ");
			break ;
		}
		pos = env_var_exists(params->exec_arg[i]);
		insert_new_var(params->exec_arg[i], pos);
		++i;
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

// Replicates variable unset
void	builtin_unset(t_params *params)
{
	int		pos;
	int		i;

	i = 1;
	if (params->exec_arg[1] == NULL)
		return ;
	while (params->exec_arg[i])
	{
		if (valid_name(params->exec_arg[i]) == false)
		{
			perror("Not a valid variable name: ");
			break ;
		}
		pos = env_var_exists(params->exec_arg[i]);
		if (pos != -1)
			envp = array_del_one(envp, pos);
		++i;
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

// Replicates the UNIX command env
void	builtin_env(t_params *params)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		ft_putstr_fd(envp[i], params->fd_out);
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
