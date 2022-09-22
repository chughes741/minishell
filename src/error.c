/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:04:12 by chughes           #+#    #+#             */
/*   Updated: 2022/09/22 14:34:38 by chughes          ###   ########.fr       */
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
	t_data	*data;

	data = get_data();
	perror("Testing");
	#ifdef DEBUG
		fprintf(data->error_log_fd, "%i\n", perror(""));
	#endif
	return ;
}
