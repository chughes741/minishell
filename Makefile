#*-----------------------------------------------------------------------------#
#*                                 GENERICS                                    #
#*-----------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re test valgrind

# Hide calls
export VERBOSE	=	TRUE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I./include -I./librl
RM		=	rm -rf


#*-----------------------------------------------------------------------------#
#*                                LIBRARIES                                    #
#*-----------------------------------------------------------------------------#

LFTDIR	=	libft/
LIBFT	=	libft.a
LFTDEP	=	libft/include/libft.h
LIBRL	=	librl/libreadline.a librl/libhistory.a -lcurses

# Generates libft.a
$(LFTDIR)/$(LIBFT): $(LFTDEP)
	$(HIDE)$(MAKE) -C $(LFTDIR)

# Readline library targetes
RLCONF	=	librl/config.log

$(RLCONF):
	$(HIDE)cd librl && ./configure --silent

$(LIBRL): $(RLCONF)
	$(HIDE)$(MAKE) -s -C librl/


#*-----------------------------------------------------------------------------#
#*                                TARGETS                                      #
#*-----------------------------------------------------------------------------#

# Dir and file names
NAME	=	minishell
SRCDIR	=	src/
OBJDIR	=	bin/
SRCS	=	src/array.c				\
			src/builtin.c			\
			src/close_file.c		\
			src/data.c				\
			src/error.c				\
			src/execute.c			\
			src/files.c				\
			src/find_and_replace.c	\
			src/find_next.c			\
			src/free_params.c		\
			src/here_doc.c			\
			src/io.c				\
			src/minishell.c			\
			src/params.c			\
			src/parse.c				\
			src/paths.c				\
			src/quotes.c			\
			src/signals.c			\
			src/strnsplit.c			\
			src/vars.c				\
			src/wait.c
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))
DEP		=	include/minishell.h

all: $(NAME)

$(NAME): $(OBJDIR) $(LIBRL) $(LFTDIR)/$(LIBFT) $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) $(LFTDIR)$(LIBFT) $(LIBRL) -o $@ 

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(DEP)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

# Creates binary directory
$(OBJDIR):
	$(HIDE)mkdir -p $(OBJDIR)

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
	$(HIDE)$(MAKE) -C $(LFTDIR) $(MAKE) clean

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(MAKE) -C $(LFTDIR) $(MAKE) fclean

# Removes objects and executables and remakes
re: fclean all


#*-----------------------------------------------------------------------------#
#*                                TESTING                                      #
#*-----------------------------------------------------------------------------#

valgrind: all
	$(HIDE)valgrind									\
			--leak-check=full						\
			--show-leak-kinds=all					\
			--track-fds=yes							\
			--show-reachable=yes					\
			--error-limit=no						\
			--suppressions=./config/minishell.supp	\
			./minishell
