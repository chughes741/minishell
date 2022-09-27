#*-----------------------------------------------------------------------------#
#*                                 GENERICS                                    #
#*-----------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

# Hide calls
export VERBOSE	=	TRUE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
DFLAG	=	-D DEBUG -Wall -Werror -Wextra
RM		=	rm -rf


#*-----------------------------------------------------------------------------#
#*                                LIBRARIES                                    #
#*-----------------------------------------------------------------------------#

LIBS	=	-lreadline

LDIR	=	libft/
LIBFT	=	libft.a

# Generates libft.a
$(LDIR)/$(LIBFT):
	$(HIDE)$(MAKE) -C $(LDIR)


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

all: inputrc $(LDIR)/$(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LDIR)/$(LIBFT)
	$(HIDE)$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(LDIR)$(LIBFT) -o $@

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	$(HIDE)mkdir -p $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

inputrc:
	$(HIDE)cp .inputrc ~/

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
#!	$(HIDE)$(MAKE) -C $(LDIR) $(MAKE) clean

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(RM) ~/.inputrc
#!	$(HIDE)$(MAKE) -C $(LDIR) $(MAKE) fclean

# Removes objects and executables and remakes
re: fclean all


#*-----------------------------------------------------------------------------#
#*                                TESTING                                      #
#*-----------------------------------------------------------------------------#

$(DEBUG): fclean
	$(HIDE)$(CC) $(DFLAG) $(LIBS) -o $(DEBUG) $(SRCS) $(LDIR)$(LIBFT)

debug: $(DEBUG)
