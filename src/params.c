/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:25:42 by chughes           #+#    #+#             */
/*   Updated: 2022/10/19 18:47:14 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parse return from rl into t_params structs
t_params	**init_params(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	i = 0;
	data = get_data();
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	cmds = split_command_groups(cmd);
	if (cmds == NULL)
		return (NULL);
	data->n_cmds = arraylen(cmds);
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds && cmds[i] != NULL)
	{
		params[i] = init_cmd(i, cmds[i]);
		i++;
	}
	free_array(cmds);
	return (params);
}

/*void	switch_chevrons(t_params **params)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while ((*params)->exec_arg[i])
	{
		if ((*params)->exec_arg[i][ft_strlen((*params)->exec_arg[i]) - 2] == '>')
		{
			(*params)->exec_arg[i] = strpop((*params)->exec_arg[i], ft_strlen((*params)->exec_arg[i]) - 2);
			temp = ft_strdup((*params)->exec_arg[i + 1]);
			(*params)->exec_arg[i + 1] = ft_calloc(ft_strlen((*params)->exec_arg[i + 1]) + 1, sizeof(char));
			(*params)->exec_arg[i + 1] = str_prepend(">", temp);
			break;
		}
		else if (ft_strchr((*params)->exec_arg[i], '>') && (*params)->exec_arg[i + 1] == NULL && (*params)->exec_arg[i][0] != '>')
		{
			j = 0;
			while ((*params)->exec_arg[i][j] != '>')
				j++;
			temp = ft_strdup(&(*params)->exec_arg[i][j]);
			(*params)->exec_arg[i] = strcdup((*params)->exec_arg[i], ">");
			(*params)->exec_arg[i + 1] = ft_calloc(ft_strlen(temp), sizeof(char));
			ft_strlcpy((*params)->exec_arg[i + 1], temp, ft_strlen(temp) + 1);
			break ;
		}
		i++;
	}
}*/

// Parses commands into struct ready to be executed
t_params	*init_cmd(int i, char *line)
{
	t_data		*data;
	t_params	*params;

	data = get_data();
	params = (t_params *)ft_calloc(1, sizeof(t_params));
	params->exec_arg = split_args(line);
	//switch_chevrons(&params);
	insert_vars(params->exec_arg);
	params->fd_in = data->fd_io[i * 2];
	params->fd_out = data->fd_io[(i * 2) + 1];
	open_outfiles(params);
	open_infiles(params);
	params->path = get_path(params->exec_arg[0]);
	return (params);
}
