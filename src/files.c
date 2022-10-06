/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:28:51 by chughes           #+#    #+#             */
/*   Updated: 2022/10/05 21:02:24 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Sets file paths from arguments
void setup_files(t_params *param)
{
	open_outfiles(param, param->exec_arg);
	open_infiles(param, param->exec_arg);
	return ;
}

void	open_outfiles(t_params *param, char	**args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((param->exec_arg[i][0] == '>' && param->exec_arg[i][1] != '>')
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '>')
		{
			xfree(param->out_path);
			param->out_path = ft_strtrim(param->exec_arg[i], ">");
			param->exec_arg = array_del_one(param->exec_arg, i);
			close_file(param->fd_out);
			param->fd_out = open(param->out_path, WRFLAGS, WRMODE);
		}
		else if (param->exec_arg[i][0] == '>' && param->exec_arg[i][1] == '>')
		{
			xfree(param->out_path);
			param->out_path = ft_strtrim(param->exec_arg[i], ">");
			param->exec_arg = array_del_one(param->exec_arg, i);
			close_file(param->fd_out);
			param->fd_out = open(param->out_path, WRAPPEND, WRMODE);
		}
		else
			++i;
	}
	return ;
}

void	open_infiles(t_params *param, int i)
{
	int	index;

	index = 0;
	while (param->exec_arg[index])
	{
		if ((param->exec_arg[index][0] == '<' && param->exec_arg[index][1] != '<')
			|| param->exec_arg[index][ft_strlen(param->exec_arg[index]) - 1] == '<')
		{
			if (access(param->exec_arg[index], F_OK) != 0)
			{
				perror(param->exec_arg[index]);
				return ;
			}
		}
	}
	if ((param->exec_arg[i][0] == '<' && param->exec_arg[i][1] != '<')
		|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '<')
	{
		xfree(param->in_path);
		param->in_path = ft_strtrim(param->exec_arg[i], "<");
		param->exec_arg = array_del_one(param->exec_arg, i);
		close_file(param->fd_in);
		param->fd_in = open(param->in_path, O_RDONLY);
	}
	return ;
}