/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:43:50 by chughes           #+#    #+#             */
/*   Updated: 2022/10/05 12:34:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Calls readline and logs
char	*prompter(void)
{
	char	*cmd;

	cmd = readline(MSH_PROMPT);
	add_history(cmd);
	return (cmd);
}
