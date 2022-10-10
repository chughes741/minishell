/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/10/10 15:20:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Handles signals
void	sig_int_handler(int signum)
{
	(void)signum;
    return ;
}

// Handles quit signal
void	sig_quit_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

