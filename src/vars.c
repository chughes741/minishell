/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:13:49 by chughes           #+#    #+#             */
/*   Updated: 2022/10/20 13:40:21 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		var_name = xfree(var_name);
		var_name = ft_itoa(WEXITSTATUS(data->exit_status));
		return (var_name);
	}
	position = env_var_exists(var_name);
	if (position >= 0)
		var_value = ft_strdup(&data->envp[position][ft_strlen(var_name) + 1]);
	else
		var_value = ft_strdup("");
	var_name = xfree(var_name);
	return (var_value);
}

// Finds and substitutes variables from envp
char	*sub_vars(char *arg)
{
	char	**splitstr;
	char	**var_name;
	int		i_arg;

	i_arg = 0;
	if (ft_strncmp(arg, "$", 2) == 0)
		return (arg);
	while (arg)
	{
		i_arg += ft_strlen_before(&arg[i_arg], "$");
		if (!arg[i_arg])
			break ;
		splitstr = strnsplit(arg, i_arg);
		splitstr[1] = strpop(splitstr[1], 0);
		var_name = strnsplit(splitstr[1], ft_strlen_before(splitstr[1], " $"));
		var_name[0] = get_var(var_name[0]);
		if (var_name[0])
			i_arg += ft_strlen(var_name[0]);
		splitstr[1] = join_free_both(var_name[0], var_name[1]);
		xfree(var_name);
		arg = join_free_both(splitstr[0], splitstr[1]);
		xfree(splitstr);
	}
	return (arg);
}

// Inserts env variables into arguments
void	insert_vars(char **args)
{
	int		i;

	i = 0;
	while (args && args[i])
	{
		args[i] = ft_strtrim_free(args[i], " ");
		if (args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\'')
			args[i] = ft_strtrim_free(args[i], "\'");
		else
		{
			args[i] = ft_strtrim_free(args[i], "\"");
			args[i] = sub_vars(args[i]);
		}
		++i;
	}
	return ;
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
