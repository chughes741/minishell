/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:18:21 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 12:30:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Writes here_doc input to fd
void	here_doc(char *eof, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(HD_PROMPT);
		if (ft_strncmp(line, &eof[2], ft_strlen(line)) == 0)
			break ;
		else if (fd > 2)
			ft_putstr_fd(line, fd);
	}
	return ;
}
