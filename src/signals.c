/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:05:28 by chughes           #+#    #+#             */
/*   Updated: 2022/10/10 20:19:09 by chughes          ###   ########.fr       */
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
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	return ;
}

