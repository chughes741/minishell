/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:46:23 by chughes           #+#    #+#             */
/*   Updated: 2022/10/13 15:39:46 by chughes          ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == '\'' && quote != 1)
		{
			quote = 1;
			nest_level++;
		}
		else if (str[i] == '\"' && quote != 2)
		{
			quote = 2;
			nest_level++;
		}
		else if (str[i] == '\'' && quote == 1)
		{
			quote = 2;
			nest_level--;
		}
		else if (str[i] == '\"' && quote == 2)
		{
			quote = 1;
			nest_level--;
		}
		if (nest_level == 0 || str[i] == '\0')
			return (i);
		i++;
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
			index += (quote_skip(&arg[index]));
		else if (arg[index] == '|' || (ft_strncmp(&arg[index], "<<", 2) == 0 
			&& index != 0))
		{
			quotes = int_realloc(quotes, len, len + 1);
			quotes[len] = index;
			len++;
		}
		else if (ft_strncmp(&arg[index], "<<", 2) == 0)
		{
			quotes = int_realloc(quotes, len, len + 1);
			index += find_next(&arg[index], " ");
			quotes[len] = index;
			len++;
		}
		index++;
	}
	quotes = int_realloc(quotes, len, len + 1);
	quotes[len] = index;
	quotes[len + 1] = -1;
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
	xfree(indices);
	return (cmd_strs);
}

// Parse return from rl into t_params structs
t_params	**parse_args(char *cmd)
{ //TODO error for invalid cmds
	//SIGSEGV on only spaces
	t_data		*data;
	t_params	**params;
	char		**cmds;
	int			i;

	data = get_data();
	if (cmd[0] == '\0')
		return (NULL);
	cmds = need_a_better_name(cmd);
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

// Parses commands into struct ready to be executed
t_params	*cmd_parse(char *line)
{
	t_params	*params;

	params = (t_params *)ft_calloc(1, sizeof(t_params));
	params->exec_arg = split_args(line);
	//TODO var sub need to happen before command is checked?
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
	temp = ft_strtrim(str, " |");
	while (temp[start])
	{
		if (ft_strchr(" \"\'", temp[start]) == NULL)
			end = find_next(&temp[start], " ") + start; //TODO check if <> are needed here
		else if (temp[start] == ' ')
			end++;
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
	temp = xfree(temp);
	return (rtn);
}
