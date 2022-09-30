/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/09/30 11:45:38 by chughes          ###   ########.fr       */
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

// Extra includes
# include <errno.h> // errno
# include <stdbool.h>

// Libft
# include "../libft/include/libft.h"

// Prompt Macro
#define PROMPT "> "


// Struct for storing initialization info for exec
typedef struct s_params {
	pid_t	id;
	char	*path;
	char	**exec_arg;
	char	**envp;
	int		fd_in;
	int		fd_out;
	int		fd_err;
}			t_params;

// Singleton struct for program data
typedef struct s_data {
	bool		run;
	char		**envp;
	char		**paths;
	t_params	**params;
	char		*last_cmd;
	int			n_cmds;
	int			exit_status;
	int			rl_history_fd;
	int			error_log_fd;
}		t_data;


// Data struct functions
void	init_data(char	*envp[]);
t_data	*get_data(void);
void	del_data(void);

// Error handling
void	error_handler(void);

// Signal handling
void	init_signals(void);
void	handle_interupt(int signum);
void	handle_quit(int signum);
void	handle_abort(int signum);

// Parsing functions
t_params	**parse_args(char *cmd);

// Runtime loop functions
char	*prompter(void);
void	log_history(char *cmd);
void	load_history(void);

// Exec setup functions
char		**split_paths(char *envp[]);
char		*get_path(char **paths, char *command);
int			exe(t_params *params);
t_params	*cmd_parse(char *line);

// I/O functions
void	open_pipe(void);
void	here_doc_filler(int output_fd, char *key);
void	write_str(char *str, int fd);

// Standard Library like functions
char	*strcdup(char *basestr, char *matchchrs);
void	*xfree(void *ptr);
void	*xrealloc(void *ptr, size_t size);

// Builtins
bool	run_builtin(t_params *params);
void	builtin_echo(char *str);
void	builtin_cd(char *new_dir);
char	*builtin_pwd(void);
void	builtin_export(char *new_var);
void	builtin_unset(char *var_name);
void	builtin_env(void);
void	builtin_exit(void);


#endif // MINISHELL_H
