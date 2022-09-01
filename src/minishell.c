/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/01 11:30:00 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	char	*cmd;

	cmd = ft_strdup("Welcome to Marc and Cole's minishell");
	while (ft_strncmp(cmd, "exit", 4))
	{
		if (!ft_strncmp(cmd, "^D", 2))
			exit(0);
		//TODO Handle \\ and ^C exits, might need to use .inputrc and ENV for this
		printf("%s\n", cmd);
		free(cmd);
		cmd = readline("> ");
	}
	return (0);
}
