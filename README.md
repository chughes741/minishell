# minishell
An interactive shell


## Allowed functions
###	Memory management
	malloc, free

###	File operations
	access, open, read, write, close
	dup
	dup2
	pipe

### Process operations
	fork, wait, waitpid, wait3, wait4
	signal, sigaction, sigemptyset, sigaddset
	kill
	exit
	execve

### Error handling
	strerror, perror

	readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
	printf
	getcwd
	chdir
	stat
	lstat
	fstat
	unlink
	opendir, readdir, closedir
	isatty, ttyname, ttyslot
	ioctl
	getenv
	tcsetattr
	tcgetattr
	tgetent
	tgetflag
	tgetnum
	tgetstr
	tgoto
	tputs