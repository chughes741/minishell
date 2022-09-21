/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:01 by chughes           #+#    #+#             */
/*   Updated: 2022/09/21 17:51:49 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Writes here_doc input to fd
void	here_doc_filler(int output_fd, char *key)
{
	char	*line;

	line = readline(">>");
	if (ft_strncmp(line, key, ft_strlen(line)) != 0)
		write_str(line, output_fd);
}

// Writes str to fd
void	write_str(char *str, int fd)
{
	int	i;
	
	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
	write(fd, "\255", 1);
}
