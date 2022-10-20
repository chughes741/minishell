/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:58:01 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 14:15:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RL_HIST "log/rl_history.log"
#define ERROR_LOG "log/error.log"

extern char	**environ;

// Initializes data struct
void	init_data(void)
{
	t_data	*data;

	data = get_data();
	data->run_cmd[0] = builtin_echo;
	data->run_cmd[1] = builtin_cd;
	data->run_cmd[2] = builtin_pwd;
	data->run_cmd[3] = builtin_export;
	data->run_cmd[4] = builtin_unset;
	data->run_cmd[5] = builtin_env;
	data->run_cmd[6] = builtin_exit;
	data->run_cmd[7] = exe;
	data->cmd_names = init_cmd_names();
	data->envp = arraydup(environ);
	return ;
}

// Itializes key values for cmd_names
char	**init_cmd_names(void)
{
	char	**cmd_names;

	cmd_names = (char **)ft_calloc(8, sizeof(char *));
	cmd_names[0] = ft_strdup("echo");
	cmd_names[1] = ft_strdup("cd");
	cmd_names[2] = ft_strdup("pwd");
	cmd_names[3] = ft_strdup("export");
	cmd_names[4] = ft_strdup("unset");
	cmd_names[5] = ft_strdup("env");
	cmd_names[6] = ft_strdup("exit");
	return (cmd_names);
}

// Singleton constructor for data struct
t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (data == NULL)
		data = (t_data *)ft_calloc(1, sizeof(t_data));
	return (data);
}

// Deletes data struct
void	del_data(void)
{
	t_data	*data;

	data = get_data();
	free_array(data->envp);
	free_params(data->params);
	xfree(data->last_cmd);
	xfree(data->fd_io);
	free_array(data->cmd_names);
	xfree(data);
	return ;
}
