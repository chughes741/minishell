/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/04 18:49:44 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// STDLIB Includes
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink,
					//execve, dup, dup2, pipe, isatty, ttyname, ttyslot
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
# include <stdbool.h> // true, false, bool

// Libft
# include "../libft/include/libft.h"

// Prompt Macro
# define PROMPT "minishell> "

// Struct for storing initialization info for exec
typedef struct s_params {
	pid_t	id;
	char	*path;
	char	**exec_arg;
	char	**envp;
	char	*in_path;
	char	*out_path;
	int		fd_in;
	int		fd_out;
}			t_params;

// Singleton struct for program data
typedef struct s_data {
	bool		run;
	char		**envp;
	t_params	**params;
	char		*last_cmd;
	int			n_cmds;
	int			*fd_io;
	int			exit_status;
	int			fd_rl_history;
	int			fd_error_log;
}		t_data;

// Data struct functions
void		init_data(char	*envp[]);
t_data		*get_data(void);
void		del_data(void);

// Error handling
void		error_handler(void);

// Signal handling
void		init_signals(void);
void		handle_interupt(int signum);
void		handle_quit(int signum);
void		handle_abort(int signum);

// Parsing functions
char		*prompter(void);
t_params	**parse_args(char *cmd);
int			find_next(char *str, char *chr);
char		**split_args(char *str);

// Exec setup functions
char		**split_paths(void);
char		*get_path(char *command);
int			exe(t_params *params, int i_child);
t_params	*cmd_parse(char *line);

// I/O functions
int			*init_io(int n_cmds, int *fd_io);
void		close_io(int *fd_io, int n_cmds, int i_child);
void		here_doc_filler(int output_fd, char *key);
void		write_str(char *str, int fd);

// Standard Library like functions
char		*strcdup(char *basestr, char *matchchrs);
void		*xfree(void *ptr);
void		**array_realloc(void **ptr, int size);
void		*free_array(void **array);
int 		arraylen(void **array);
void		**arraydup(void **array);
void		**array_del_one(void **array, int position);
void		find_and_replace(char *str, char *chrs, char replace, int len);
int			find_first(char *str, char *chrs);
int			find_last(char *str, char *chrs);

// Builtins
bool		run_builtin(t_params *params);
void		builtin_echo(char **args, int fd_write);
void		builtin_cd(char *new_dir);
void		builtin_pwd(int fd_write);
void		builtin_export(char *new_var);
void		builtin_unset(char *var_name);
void		builtin_env(int fd_write);
void		builtin_exit(void);

#endif // MINISHELL_H
