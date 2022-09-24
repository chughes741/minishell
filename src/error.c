/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:04:12 by chughes           #+#    #+#             */
/*   Updated: 2022/09/23 22:27:37 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Writes message to stderr and exits
void	exit_error(char *message)
{
	del_data();
	perror(message);
	exit(1);
}

// Manages errors from children, writes to debug file
void	error_handler(void)
{
	perror("Testing");
	#ifdef DEBUG
	t_data	*data = get_data();
	dprintf(data->error_log_fd, "%i\n", perror(""));
	#endif
	return ;
}
