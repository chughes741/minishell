/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:04:12 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 11:45:27 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Manages errors from children, writes to debug file
void	error_handler(void)
{
	perror("Testing");
	#ifdef DEBUG
	t_data	*data = get_data();
	dprintf(data->error_log_fd, "%i\n", data->exit_status);
	#endif
	return ;
}
