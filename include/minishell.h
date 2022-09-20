/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/20 13:17:34 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// STDLIB Includes
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <stdio.h> // readline, printf, perror
# include <stdlib.h> // malloc, free, exit, getenv, 
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <fcntl.h> // open
# include <sys/wait.h> // wait, wait3, wait4
# include <sys/types.h> // waitpid, wait3, opendir, closedir
# include <sys/wait.h> // waitpid
# include <sys/time.h> // wait3
# include <sys/resource.h> // wait3
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <dirent.h> // opendir, readdir, closedir
# include <string.h> // strerror
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// Libft
#include "../libft/include/libft.h"

typedef struct s_var {
	char	*name;
	char	*val;
	t_var	*next;
}		t_var;

typedef struct s_data {
	char	**envp;
	char	**paths;
	t_var	*vars;
}		t_data;

typedef struct s_params {
	pid_t	id;
	char	*path;
	char	**exec_arg;
	char	**envp;
	int		fd_in;
	int		fd_out;
}			t_params;

// Data struct functions
void	init_data(char	*envp[]);
t_data	*get_data(void);
void	del_data(void);

// Error handling
void	exit_error(char *message);

// Signal handling
void	signal_handler(int signal);

// Exec setup functions
char		**split_paths(char *envp[]);
char		*get_path(char **paths, char *command);
int			exe(t_params *params);
t_params	*cmd_parse(char *line);

// I/O functions
void	open_pipe(void);

// LibC functions
char	*strcdup(char *basestr, char *matchchrs);

// t_var functions
void	t_var_new_node(char *name, char *val);
t_var	*t_var_search(char *name);
void	t_var_del_all(void);


#endif