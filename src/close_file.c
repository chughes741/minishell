/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:26:46 by chughes           #+#    #+#             */
/*   Updated: 2022/10/17 10:45:44 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Calls close on fd if fd is not STDIN, STDOUT, or STDERR
void	close_file(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
	return ;
}
