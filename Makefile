
SRCS = 		   srcs/ft_echo.c		    \
			   srcs/ft_cd.c             \
			   srcs/ft_env.c			\
			   srcs/ft_exec_cmd.c		\
			   srcs/ft_exit.c			\
			   srcs/ft_export.c			\
			   srcs/ft_export_concat.c	\
			   srcs/ft_export_print.c	\
			   srcs/ft_free_mem.c		\
			   srcs/ft_history.c		\
			   srcs/ft_history2.c		\
			   srcs/ft_init_prms.c		\
			   srcs/ft_keys1.c			\
			   srcs/ft_keys2.c			\
			   srcs/ft_own_func.c		\
			   srcs/ft_parse_env.c		\
			   srcs/ft_parse_str.c		\
			   srcs/ft_parse_str2.c		\
			   srcs/ft_parse_utils.c	\
			   srcs/ft_pipes.c			\
			   srcs/ft_pwd.c			\
			   srcs/ft_redirect.c		\
			   srcs/ft_signals.c		\
			   srcs/ft_split_cmd.c		\
			   srcs/ft_term_redaktor.c	\
			   srcs/ft_unset.c			\
			   srcs/ft_utils1.c			\
			   srcs/ft_utils2.c			\
			   srcs/ft_utils3.c			\
			   srcs/ft_utils4.c			\
			   srcs/ft_utils5.c			\
			   srcs/ft_utils_env.c		\
			   srcs/ft_utils_env2.c		\
			   srcs/main.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -Wno-unused-command-line-argument -Iincludes
#-Wall -Wextra -Werror

.PHONY: 	clean fclean all re

all:		$(NAME)

#.c.o:
#			gcc $(CFLAGS) -c $< -o $@

includes = $(wildcard includes/*.h)

%.o: %.c ${includes}
			@gcc $(CFLAGS) -ltermcap -Iincludes -c $< -o $@

$(NAME):	$(OBJS)
			@gcc -o $(NAME) $(OBJS) $(CFLAGS) -ltermcap

clean:
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(NAME)

re:			fclean all
