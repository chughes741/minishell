/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:26:46 by chughes           #+#    #+#             */
/*   Updated: 2022/10/05 15:30:28 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Calls close on fd if fd is not STDIN, STDOUT, or STDERR
void	close_file(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
	return ;
}
