/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/04 18:47:32 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Parse return from rl into t_params structs
t_params	**parse_args(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	data = get_data();
	cmds = ft_split(cmd, '|');
	data->n_cmds = arraylen((void **)cmds);
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds[i] != NULL)
	{
		params[i] = cmd_parse(cmds[i]);
		params[i]->fd_in = data->fd_io[i * 2];
		params[i]->fd_out = data->fd_io[(i * 2) + 1];
		i++;
	}
	return (params);
}

// Finds and substitutes variables from envp
void	sub_vars(char *arg)
{
	t_data	*data;

	data = get_data();
	(void)data;
	(void)arg;
	return ;
}

// Inserts env variables into arguments
void	insert_vars(char **args)
{
	for (int i = 0; args[i]; ++i)
	{
		if (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\'')
			ft_strtrim(args[i], "\'");
		else
		{
			ft_strtrim(args[i], "\"");
			sub_vars(args[i]);
		}
	}
	return ;
}

// Parses commands into struct ready to be executed
t_params	*cmd_parse(char *line)
{
	t_data		*data;
	t_params	*params;

	data = get_data();
	params = (t_params *)ft_calloc(1, sizeof(t_params));
	params->exec_arg = split_args(line);
	//TODO Setup files and remove from exec_args
	insert_vars(params->exec_arg);
	params->path = get_path(params->exec_arg[0]);
	params->envp = data->envp;
	return (params);
}

// Returns index of next chr match in str
int	find_next(char *str, char *chr)
{
	int i;

	i = 0;
	while(str[i] != NULL && ft_strchr(chr, str[i]) == NULL)
		++i;
	return (i);
}

// Splits arguments keeping quoted sections together
char	**split_args(char *str)
{
	char	**rtn;
	int		start;
	int		end;

	rtn = (char **)ft_calloc(1, sizeof(char *));
	start = 0;
	str = ft_strtrim(str, " ");
	while (str[start] != NULL)
	{
		if (ft_strchr(" \"\'", str[start]) == NULL)
			end = find_next(&str[start], " ") + start;
		else if (str[start] == ' ')
			;
		else if (ft_strchr("\'", str[start]) != NULL)
			end = find_next(&str[start + 1], "\'") + start + 2;
		else if (ft_strchr("\"", str[start]) != NULL)
			end = find_next(&str[start + 1], "\"") + start + 2;
		else
			end = ft_strlen(&str[start] - 1);
		if (end > start && start < (int)ft_strlen(str) - 1)
		{
			rtn = (char **)array_realloc((void **)rtn, arraylen((void **)rtn) + 1);
			rtn[arraylen((void **)rtn)] = ft_substr(str, start, end - start);
		}
		start = end + 1;
	}
	return (rtn);
}
