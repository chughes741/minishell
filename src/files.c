/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:28:51 by chughes           #+#    #+#             */
/*   Updated: 2022/10/19 19:53:06 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if a file is accessible
bool	check_file_perm(char *file, int access_type)
{
	if (access(file, access_type) != 0)
	{
		perror(file);
		return (true);
	}
	return (false);
}

// Opens all output files needed by program to be run
void	open_outfiles(t_params *param)
{
	int	i;

	i = 0;
	while (param->exec_arg && param->exec_arg[i])
	{
		if (param->exec_arg[i][0] == '>')
		{
			param->out_path = xfree(param->out_path);
			param->out_path = ft_strtrim(param->exec_arg[i], "> ");
			close_file(param->fd_out);
			if (param->exec_arg[i][1] == '>')
				param->fd_out = open(param->out_path, WRAPPEND, WRMODE);
			else
				param->fd_out = open(param->out_path, WRFLAGS, WRMODE);
			param->exec_arg = array_del_one(param->exec_arg, i);
			if (check_file_perm(param->out_path, W_OK) == true)
				param->err = true;
		}
		else
			++i;
	}
	return ;
}

/*
	Need to use farthest one to the right as the input
*/

// Opens all input files needed by program to be run
void	open_infiles(t_params *param)
{
	int	i;

	i = 0;
	while (param->exec_arg && param->exec_arg[i])
	{
		if (param->exec_arg[i][0] == '<')
		{
			close_file(param->fd_in);
			param->in_path = xfree(param->in_path);
			if (param->exec_arg[i][1] == '<')
				param->fd_in = here_doc(param->exec_arg[i]);
			else
			{
				param->in_path = ft_strtrim(param->exec_arg[i], "< ");
				if (check_file_perm(param->in_path, R_OK) == true)
					param->err = true;
				param->fd_in = open(param->in_path, O_RDONLY);
			}
			param->exec_arg = array_del_one(param->exec_arg, i);
		}
		else
			++i;
	}
	return ;
}
