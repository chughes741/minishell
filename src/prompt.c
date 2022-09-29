/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:43:50 by chughes           #+#    #+#             */
/*   Updated: 2022/09/29 17:03:37 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Calls readline and logs
char	*prompter(void)
{
	char	*cmd;

	cmd = readline(PROMPT);
	#ifdef DEBUG
	log_history(cmd);
	#endif
	return (cmd);
}
