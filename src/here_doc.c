/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:18:21 by chughes           #+#    #+#             */
/*   Updated: 2022/10/13 13:18:31 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Writes here_doc input to fd
void	here_doc(t_params *params)
{
	char	*line;

	while (1)
	{
		line = readline(HD_PROMPT);
		if (ft_strncmp(line, params->exec_arg[1], ft_strlen(line)) != 0)
		{
			if (params->fd_out > 2)
				ft_putstr_fd(line, params->fd_out);
			xfree(line);
		}
		else
		{
			xfree(line);
			break ;
		}
	}
	close_file(params->fd_in);
	close_file(params->fd_out);
	return ;
}
