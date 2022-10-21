/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malord <malord@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:18:21 by chughes           #+#    #+#             */
/*   Updated: 2022/10/21 11:26:36 by malord           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Writes here_doc input to fd, takes eof with <<
int	here_doc(char *eof)
{
	char	*line;
	int		fd_pipe[2];

	pipe(fd_pipe);
	while (1)
	{
		line = readline(HD_PROMPT);
		if (!line || ft_strncmp(line, &eof[2], ft_strlen(line)) == 0)
			break ;
		else
			ft_putstr_fd(line, fd_pipe[1]);
		write(fd_pipe[1], "\n", 1);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
