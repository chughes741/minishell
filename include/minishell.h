/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:30:00 by chughes           #+#    #+#             */
/*   Updated: 2022/10/11 10:09:22 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// STDLIB Includes
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink,
					//execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <stdio.h> // readline, printf, perror
# include <stdlib.h> // malloc, free, exit, getenv, 
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

// Libs
# include "../librl/readline.h" // readline
# include "../librl/history.h" // readline
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
	void		(*run_cmd[9])(t_params *);
	char		**cmd_names;
	int			exit_status;
}		t_data;

// Macros
# define MSH_PROMPT "msh > "
# define HD_PROMPT "> "
# define WRFLAGS O_WRONLY | O_CREAT |O_TRUNC
# define WRAPPEND O_WRONLY | O_CREAT | O_APPEND
# define WRMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define INTERACTIVE 1
# define RUNTIME 2

// Data struct functions
void		init_data(char	*envp[]);
char		**init_cmd_names(void);
t_data		*get_data(void);
void		del_data(void);
void		free_params(t_params **params);

// Error handling
void		error_handler(void);

// Signal handling
void		init_signals(int mode);
void		sigint_interactive(int signum);
void		sigquit_interactive(int signum);
void		sigint_runtime(int signum);
void		sigquit_runtime(int signum);

// Parsing functions
t_params	**parse_args(char *cmd);
int			find_next(char *str, char *chr);
char		**split_args(char *str);
void		setup_files(t_params *param);

// Exec setup functions
char		**split_paths(void);
char		*get_path(char *command);
void		exe(t_params *params);
t_params	*cmd_parse(char *line);

// I/O functions
int			*init_io(int n_cmds, int *fd_io);
void		close_io(int *fd_io, int n_cmds, int fd_in, int fd_out);
void		close_file(int fd);
void		open_outfiles(t_params *param);
void		open_infiles(t_params *param);
bool		check_file_perm(char *file, int access_type);

// Standard Library like functions
char		*strcdup(char *basestr, char *matchchrs);
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
int			cmd_index(char *arg);
void		builtin_echo(t_params *params);
void		builtin_cd(t_params *params);
void		builtin_pwd(t_params *params);
void		builtin_export(t_params *params);
void		builtin_unset(t_params *params);
void		builtin_env(t_params *params);
void		builtin_exit(t_params *params);
void		here_doc(t_params *params);

#endif // MINISHELL_H
