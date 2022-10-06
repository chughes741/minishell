/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/06 10:48:17 by chughes          ###   ########.fr       */
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

// Struct for storing initialization info for exec
typedef struct s_params {
	pid_t	id;
	char	*path;
	char	**exec_arg;
	char	*in_path;
	char	*out_path;
	int		fd_in;
	int		fd_out;
	bool	err;
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
}		t_data;

// Macros
# define MSH_PROMPT "msh > "
# define HD_PROMPT "> "
# define WRFLAGS O_WRONLY | O_CREAT |O_TRUNC
# define WRAPPEND O_WRONLY | O_CREAT | O_APPEND
# define WRMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

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
t_params	**parse_args(char *cmd);
int			find_next(char *str, char *chr);
char		**split_args(char *str);
void		setup_files(t_params *param);

// Exec setup functions
char		**split_paths(void);
char		*get_path(char *command);
int			exe(t_params *params, int i_child);
t_params	*cmd_parse(char *line);

// I/O functions
int			*init_io(int n_cmds, int *fd_io);
void		close_io(int *fd_io, int n_cmds, int i_child);
void		close_file(int fd);
void		open_outfiles(t_params *param);
void		open_infiles(t_params *param);

// Standard Library like functions
char		*strcdup(char *basestr, char *matchchrs);
void		*xfree(void *ptr);
char		**array_realloc(char **ptr, int size);
char		*free_array(char **array);
int 		arraylen(char **array);
char		**arraydup(char **array);
char		**array_del_one(char **array, int position);
void		find_and_replace(char *str, char *chrs, char replace, int len);
int			find_first(char *str, char *chrs);
int			find_last(char *str, char *chrs);
char		*join_free_both(char *s1, char *s2);

// Builtins
bool		run_builtin(t_params *params);
void		builtin_echo(char **args, int fd_write);
void		builtin_cd(char *new_dir);
void		builtin_pwd(int fd_write);
void		builtin_export(char **new_vars);
void		builtin_unset(char *var_name);
void		builtin_env(int fd_write);
void		builtin_exit(void);
void		here_doc(char *key, int output_fd);

#endif // MINISHELL_H
