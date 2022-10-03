/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:40:01 by chughes           #+#    #+#             */
/*   Updated: 2022/10/02 21:46:43 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Returns an array with the fds of n pipes
int	*init_io(int n_cmds, int *fd_io)
{
	// int	*fd_io;
	int	temp[2];
	int	i;

	xfree(fd_io);
	fd_io = (int *)ft_calloc(n_cmds * 2, sizeof(int));
	i = 1;
	while (i < n_cmds)
	{
		pipe(temp);
		fd_io[i * 2] = temp[0];
		fd_io[(i * 2) - 1] = temp[1];
		++i;
	}
	fd_io[0] = STDIN_FILENO;
	fd_io[(i * 2) - 1] = STDOUT_FILENO;
	return (fd_io);
}

// Closes all fds except those used by child[i] and any STD IN, OUT, ERR
void	close_io(int *fd_io, int n_cmds, int i_child)
{
	int	i;

	i = 0;
	while (i < n_cmds * 2)
	{
		if (fd_io[i] > 2 && (i != (i_child * 2) && i != (i_child * 2) + 1))
			close(fd_io[i]);
		++i;
	}
	return ;
}
