#*-----------------------------------------------------------------------------#
#*                                 GENERICS                                    #
#*-----------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re debug test

# Hide calls
export VERBOSE	=	FALSE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I./librl
DFLAG	=	-g -D DEBUG -Wall -Werror -Wextra
RM		=	rm -rf


#*-----------------------------------------------------------------------------#
#*                                LIBRARIES                                    #
#*-----------------------------------------------------------------------------#

LFTDIR	=	libft/
LIBFT	=	libft.a 
LIBRL	=	librl/libreadline.a librl/libhistory.a -lcurses

# Generates libft.a
$(LFTDIR)/$(LIBFT):
	$(HIDE)$(MAKE) -C $(LFTDIR)

readline:
ifeq (,$(wildcard ./readline-8.1/config.log))
	$(HIDE)cd librl && ./configure --silent && $(MAKE) -s
endif


#*-----------------------------------------------------------------------------#
#*                                TARGETS                                      #
#*-----------------------------------------------------------------------------#

# Dir and file names
NAME	=	minishell
DEBUG	=	minishell_debug
SRCDIR	=	src/
OBJDIR	=	bin/
SRCS	=	$(wildcard $(SRCDIR)*.c) #! RBS
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): readline $(LFTDIR)/$(LIBFT) $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) $(LFTDIR)$(LIBFT) $(LIBRL) -o $@ 

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

# Creates binary directory
$(OBJDIR):
	$(HIDE)mkdir -p $(OBJDIR)

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
#!	$(HIDE)$(MAKE) -C $(LFTDIR) $(MAKE) clean

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME) $(DEBUG)
#!	$(HIDE)$(MAKE) -C $(LFTDIR) $(MAKE) fclean

# Removes objects and executables and remakes
re: fclean all


#*-----------------------------------------------------------------------------#
#*                                TESTING                                      #
#*-----------------------------------------------------------------------------#

$(DEBUG): fclean
	$(HIDE)$(CC) $(DFLAG) $(LIBS) -o $(DEBUG) $(SRCS) $(LFTDIR)$(LIBFT)

debug: $(DEBUG)
	$(HIDE)leaks --atExit -- ./$(DEBUG)

test:
	$(HIDE)$(MAKE) -C test
