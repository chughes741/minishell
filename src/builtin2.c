/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:45:18 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 15:24:11 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	builtin_exit(t_params *params)
{
	(void)params;
	del_data();
	printf("exit\n");
	exit(0);
}
