/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/05 15:31:34 by chughes          ###   ########.fr       */
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
	data->n_cmds = arraylen(cmds);
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds[i] != NULL)
	{
		params[i] = cmd_parse(cmds[i]);
		params[i]->fd_in = data->fd_io[i * 2];
		params[i]->fd_out = data->fd_io[(i * 2) + 1];
		setup_files(params[i]);
		i++;
	}
	return (params);
}

// Gets the value of a variable from envp
/*char	*find_var(char *var_name)
{
	t_data	*data;
	char	*var_value;
	int		pos;

	data = get_data();
	while (data->envp[pos] != NULL
		&& ft_strncmp(var_name, data->envp[pos], ft_strlen(var_name)))
		pos++;
	if (data->envp[pos] == NULL)
		return (NULL);
	return (ft_strdup(&data->envp[pos][ft_strlen(var_name) + 1]));
}*/

// Finds and substitutes variables from envp
/*char	*sub_vars(char *arg)
{
	char	**split_tokens;
	char	*var_name;
	char	*var_value;
	char	*result_str;
	int		i;

	i = 1;
	if (arg[0] == '$')
		i = 0;
	split_tokens = ft_split(arg, '$');
	xfree(arg);
	while (split_tokens[i])
	{
		//TODO Get var name
		var_value = find_var(var_name);
		//TODO Remove var name from split_tokens[i]
		split_tokens[i] = join_free_both(var_value, split_tokens[i]);
		++i;
	}
	result_str = array_join(split_tokens);
	return (result_str);
}*/

// Inserts env variables into arguments
/*void	insert_vars(char **args)
{
	for (int i = 0; args[i]; ++i)
	{
		if (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\'')
			ft_strtrim(args[i], "\'");
		else
		{
			ft_strtrim(args[i], "\"");
			args[i] = sub_vars(args[i]);
		}
	}
	return ;
}*/

// Sets file paths from arguments
void setup_files(t_params *param)
{
	int	i;

	i = 0;
	while (param->exec_arg[i] != NULL)
	{
		if (param->exec_arg[i][0] == '<' 
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '<')
		{
			xfree(param->in_path);
			param->in_path = ft_strtrim(param->exec_arg[i], "<");
			param->exec_arg = array_del_one(param->exec_arg, i);
		}
		else if (param->exec_arg[i][0] == '>' 
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '>')
		{
			xfree(param->out_path);
			param->out_path = ft_strtrim(param->exec_arg[i], ">");
			param->exec_arg = array_del_one(param->exec_arg, i);	
		}
		else
			++i;
	}
	if (param->in_path != NULL)
	{
		close_file(param->fd_in);
		param->fd_in = open(param->in_path, O_RDONLY);
	}
	if (param->out_path != NULL)
	{
		close_file(param->fd_out);
		param->fd_out = open(param->out_path, WRFLAGS, WRMODE);
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
	//insert_vars(params->exec_arg);
	params->path = get_path(params->exec_arg[0]);
	params->envp = data->envp;
	return (params);
}

// Returns index of next chr match in str
int	find_next(char *str, char *chr)
{
	int i;

	i = 0;
	while(str[i] && ft_strchr(chr, str[i]) == NULL)
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
	while (str[start])
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
			rtn = array_realloc(rtn, arraylen(rtn) + 1);
			rtn[arraylen(rtn)] = ft_substr(str, start, end - start);
		}
		start = end + 1;
	}
	return (rtn);
}
