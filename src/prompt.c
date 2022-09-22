/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:43:50 by chughes           #+#    #+#             */
/*   Updated: 2022/09/22 14:08:23 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Calls readline and logs
void	prompter(void)
{
	t_data	*data;

	data = get_data();

	data->last_cmd = readline(PROMPT);
	log_history(data->last_cmd);
	return ;
}
