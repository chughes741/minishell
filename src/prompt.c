/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:43:50 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 11:42:17 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Calls readline and logs
char	*prompter(void)
{
	char	*cmd;

	cmd = readline(PROMPT);
	log_history(cmd);
	return (cmd);
}
