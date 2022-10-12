/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/12 14:25:15 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*count_quotes(char *arg)
{
	int	index;
	int	j;
	int	*quotes;
	int	size;

	index = 0;
	j = 0;
	size = 1;
	quotes = ft_calloc(sizeof(int), size);
	while (arg[index])
	{
		if (arg[index] == '\"')
		{
			quotes[j] = index;
			j++;
			size++;
			quotes = int_realloc(quotes, size);
		}
		index++;
	}
	return (quotes);
}

char	*extract_string(char *arg, int start, int end)
{
	char	*extracted;
	int		i;

	i = 0;
	extracted = ft_substr(arg, start, (end - start) - 1);
	printf("Extracted contient : %s\n", extracted);
	return (extracted);
}

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

// Splits a string at the index
char	**strnsplit(char *str, int index)
{
	char	**split;

	if (!str)
		return (NULL);
	split = (char **)ft_calloc(3, sizeof(char *));
	if (index == 0)
		split[0] = ft_strdup("");
	else
		split[0] = ft_strndup(str, index);
	split[1] = ft_strdup(&str[index]);
	xfree(str);
	return (split);
}

// Finds and substitutes variables from envp
char	*sub_vars(char *arg)
{
	//TODO fix leaks
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
		// xfree(arg);
		arg = join_free_both(split_str[0], split_str[1]);
		xfree(split_str);
	}
	return (arg);
}

// Inserts env variables into arguments
void	insert_vars(char **args)
{
	int	i;

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
		start = end + 1;
	}
	xfree(temp);
	return (rtn);
}
