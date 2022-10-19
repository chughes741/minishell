/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/18 20:32:09 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!ft_strchr(name, '='))
		return (false);
	split_name = ft_split(name, '=');
	/*for (int i = 0; split_name[i]; i++)
		printf("split_name[i] = %s\n", split_name[i]);*/
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
	t_data	*data;
	char	*new_var_name;
	int		pos;

	data = get_data();
	pos = 0;
	new_var_name = strcdup(new_var, "=");
	while (data->envp[pos])
	{
		if (ft_strncmp(data->envp[pos], new_var_name,
				ft_strlen(new_var_name)) == 0)
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
	t_data	*data;

	data = get_data();
	if (pos == -1)
	{
		pos = arraylen(data->envp);
		data->envp = array_realloc(data->envp, pos + 1);
	}
	else
		xfree(data->envp[pos]);
	data->envp[pos] = ft_strdup(new_var);
}

// Replicates variable exporting
void	builtin_export(t_params *params)
{	//TODO string with spaces doesn't work properly, quotes or not
	int		i;
	int		pos;
	bool	invalid;

	if (params->exec_arg[1] == NULL)
	{
		builtin_env(params);
		return ;
	}
	i = 1;
	invalid = false;
	while (params->exec_arg[i])
	{
		if (valid_name(params->exec_arg[i]) == false)
		{
			if (ft_strchr(params->exec_arg[i - 1], '=') && ft_strchr(params->exec_arg[i], '='))
				;
			else
			{
				perror("Not a valid variable name: ");
				invalid = true;
			}
		}
		if (invalid == false)
		{
			pos = env_var_exists(params->exec_arg[i]);
			insert_new_var(params->exec_arg[i], pos);
		}
		else
			invalid = false;
		++i;
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}

// Replicates variable unset
void	builtin_unset(t_params *params)
{
	t_data	*data;
	int		pos;
	int		i;

	data = get_data();
	i = 1;
	if (params->exec_arg[1] == NULL)
		return ;
	while (params->exec_arg[i])
	{
		pos = env_var_exists(params->exec_arg[i]);
		if (pos != -1)
			data->envp = array_del_one(data->envp, pos);
		++i;
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
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
