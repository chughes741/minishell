/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:28:51 by chughes           #+#    #+#             */
/*   Updated: 2022/10/06 10:35:07 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_outfiles(t_params *param)
{
	int	i;

	i = 0;
	while (param->exec_arg[i])
	{
		if (param->exec_arg[i][0] == '>'
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '>')
		{
			xfree(param->out_path);
			param->out_path = ft_strtrim(param->exec_arg[i], ">");
			param->exec_arg = array_del_one(param->exec_arg, i);
			close_file(param->fd_out);
			if (param->exec_arg[i][1] == '>')
				param->fd_out = open(param->out_path, WRAPPEND, WRMODE);
			else
				param->fd_out = open(param->out_path, WRFLAGS, WRMODE);
		}
		else
			++i;
	}
	return ;
}

void	open_infiles(t_params *param)
{
	int	i;

	i = 0;
	while (param->exec_arg[i])
	{
		if (param->exec_arg[i][0] == '<'
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '<')
		{
			if (access(param->exec_arg[i], R_OK) != 0)
			{
				perror(param->exec_arg[i]);
				return ;
			}
		}
		++i;
	}
	i = 0;
	while (param->exec_arg[i])
	{
		if (param->exec_arg[i][0] == '<'
			|| param->exec_arg[i][ft_strlen(param->exec_arg[i]) - 1] == '<')
		{
			xfree(param->in_path);
			param->in_path = ft_strtrim(param->exec_arg[i], "<");
			param->exec_arg = array_del_one(param->exec_arg, i);
			close_file(param->fd_in);
			param->fd_in = open(param->in_path, O_RDONLY);
		}
		++i;
	}
	return ;
}