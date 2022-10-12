/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/12 17:27:46 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// Returns index of closing quote, skips nested quotes
int	quote_skip(char *str)
{	//TODO make this shorter
	int	i;
	int	nest_level;
	int	quote;

	i = 0;
	nest_level = 0;
	quote = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && quote != 1)
		{
			quote = 1;
			nest_level += 1;
		}
		else if (str[i] == '\"' && quote != 2)
		{
			quote = 2;
			nest_level += 1;
		}
		else if (str[i] == '\'' && quote == 1)
		{
			quote = 2;
			nest_level -= 1;
		}
		else if (str[i] == '\"' && quote == 2)
		{
			quote = 1;
			nest_level -= 1;
		}
		if (nest_level == 0)
			return (i) ;
		++i;
	}
	return (-1);
}

// Returns an array of integers containing the positions of quotes in a string
int	*get_split_indices(char *arg)
{	//TODO handle -1 return from quote skip
	int	index;
	int	len;
	int	*quotes;

	index = 0;
	len = 1;
	quotes = ft_calloc(len + 1, sizeof(int));
	while (arg[index])
	{
		if (arg[index] == '\"' || arg[index] == '\'')
			index += quote_skip(&arg[index]) - 1;
		else if (arg[index] == '|' || !ft_strncmp(&arg[index], "<<", 2)
			|| arg[index + 1] == '\0')
		{
			quotes = int_realloc(quotes, len + 1);
			quotes[len] = index;
			len++;
		}
		if (!ft_strncmp(&arg[index], "<<", 2))
			index++;
		index++;
	}
	quotes[len] = -1;
	return (quotes);
}

// Returns number of ints in an int*, until first -1
int	intlen(int *intstr)
{
	int	len;

	len = 0;
	while (intstr && intstr[len] != -1)
		len++;
	return (len);
}

// Returns array of strings, splits cmd on | and <<, accounts for quotes
char	**need_a_better_name(char *cmd)
{
	char	**cmd_strs;
	int		*indices;
	int		i;

	indices = get_split_indices(cmd);
	cmd_strs = (char **)ft_calloc(intlen(indices) + 1, sizeof(char *));
	i = 0;
	while (indices && indices[i + 1] >= 0)
	{
		cmd_strs[i] = ft_substr(cmd, indices[i], indices[i + 1] - indices[i] + 1);
		++i;
	}
	for (int i = 0; cmd_strs[i]; ++i) {
		;
	}
	return (cmd_strs);
}

// Parse return from rl into t_params structs
t_params	**parse_args(char *cmd)
{
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	data = get_data();
	cmds = need_a_better_name(cmd);
	for (int i = 0; cmds[i]; ++i)
			printf("cmd[%i]: |%s|\n", i, cmds[i]);
	data->n_cmds = arraylen(cmds);
	data->fd_io = init_io(data->n_cmds, data->fd_io);
	params = ft_calloc(data->n_cmds + 1, sizeof(t_params *));
	i = 0;
	while (cmds[i] != NULL)
	{
		params[i] = cmd_parse(cmds[i]);
		params[i]->fd_in = data->fd_io[i * 2];
		params[i]->fd_out = data->fd_io[(i * 2) + 1];
		open_outfiles(params[i]);
		open_infiles(params[i]);
		i++;
	}
	free_array(cmds);
	return (params);
}

// Returns allocated copy of contents of var_name, frees var_name
char	*get_var(char *var_name)
{
	t_data	*data;
	char	*var_value;
	int		position;

	data = get_data();
	var_name = ft_strtrim_free(var_name, " ");
	if (ft_strncmp("?", var_name, 2) == 0)
	{
		xfree(var_name);
		var_name = ft_itoa(data->exit_status);
		return (var_name);
	}
	position = env_var_exists(var_name);
	if (position >= 0)
		var_value = ft_strdup(&data->envp[position][ft_strlen(var_name) + 1]);
	else
		var_value = ft_strdup("");
	xfree(var_name);
	return (var_value);
}

// Finds and substitutes variables from envp
char	*sub_vars(char *arg)
{
	t_data	*data;
	char	**split_str;
	char	**var_name;
	int		i_arg;

	i_arg = 0;
	data = get_data();
	while (arg)
	{
		i_arg += ft_strlen_before(&arg[i_arg], "$");
		if (!arg[i_arg])
			break ;
		split_str = strnsplit(arg, i_arg);
		split_str[1] = strpop(split_str[1], 0);
		var_name = strnsplit(split_str[1], ft_strlen_before(split_str[1], " $"));
		var_name[0] = get_var(var_name[0]);
		if (var_name[0])
			i_arg += ft_strlen(var_name[0]);
		split_str[1] = join_free_both(var_name[0], var_name[1]);
		xfree(var_name);
		arg = join_free_both(split_str[0], split_str[1]);
		xfree(split_str);
	}
	return (arg);
}

// Inserts env variables into arguments
void	insert_vars(char **args)
{
	int		i;

	i = 1;
	while (args && args[i])
	{
		if (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\'')
		{
			args[i] = ft_strtrim_free(args[i], "\'");
		}
		else
		{
			args[i] = ft_strtrim_free(args[i], "\"");
			args[i] = sub_vars(args[i]);
		}
		++i;
	}
	return ;
}

// Parses commands into struct ready to be executed
t_params	*cmd_parse(char *line)
{
	t_params	*params;

	params = (t_params *)ft_calloc(1, sizeof(t_params));
	params->exec_arg = split_args(line);
	insert_vars(params->exec_arg);
	params->path = get_path(params->exec_arg[0]);
	return (params);
}

// Splits arguments keeping quoted sections together
char	**split_args(char *str)
{
	char	**rtn;
	char	*temp;
	int		start;
	int		end;

	rtn = (char **)ft_calloc(1, sizeof(char *));
	start = 0;
	temp = ft_strtrim(str, " ");
	while (temp[start])
	{
		if (ft_strchr(" \"\'", temp[start]) == NULL)
			end = find_next(&temp[start], " <>") + start;
		else if (temp[start] == ' ')
			;
		else if (ft_strchr("\'", temp[start]) != NULL)
			end = find_next(&temp[start + 1], "\'") + start + 2;
		else if (ft_strchr("\"", temp[start]) != NULL)
			end = find_next(&temp[start + 1], "\"") + start + 2;
		else
			end = ft_strlen(&temp[start] - 1);
		if (end > start && start < (int)ft_strlen(temp) - 1)
		{
			rtn = array_realloc(rtn, arraylen(rtn) + 1);
			rtn[arraylen(rtn)] = ft_substr(temp, start, end - start);
		}
		start = end;
	}
	temp = xfree(temp);
	return (rtn);
}
