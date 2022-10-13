/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:13:49 by chughes           #+#    #+#             */
/*   Updated: 2022/10/13 10:14:05 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	//t_data	*data;
	char	**split_str;
	char	**var_name;
	int		i_arg;

	i_arg = 0;
	//data = get_data();
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
