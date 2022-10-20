/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:23:31 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:24:24 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks is variable name is valid
static bool	valid_name(char *name)
{
	int		i;
	int		j;
	char	**split_name;

	split_name = ft_split(name, '=');
	if (!split_name[1] || (ft_isalpha(name[0]) == false && name[0] != '_'))
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
				ft_strlen_before(data->envp[pos], "=")) == 0
			&& ft_strlen_before(data->envp[pos], "=")
			== ft_strlen_before(new_var_name, "="))
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
{	
	int		i;
	int		pos;

	if (params->exec_arg[1] == NULL)
		builtin_env(params);
	i = 1;
	while (params->exec_arg[i])
	{
		if (valid_name(params->exec_arg[i]) == false)
			perror("Not a valid variable name: ");
		else
		{
			pos = env_var_exists(params->exec_arg[i]);
			insert_new_var(params->exec_arg[i], pos);
		}
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
