# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 16:21:20 by mmomeni           #+#    #+#              #
#    Updated: 2023/12/21 22:04:56 by htaheri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=		minishell
CFLAGS=		 -Wall -Wextra -Werror -fsanitize=address -g -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
CMDS= 		cmds/cd.c cmds/echo.c cmds/exit.c cmds/export.c
FUNC=		env.c system.c parse.c utils.c
SRCS=		main.c $(FUNC) $(CMDS)
LIBFT_DIR=	libft
LIBFT=		$(LIBFT_DIR)/libft.a

BONUS_DIR=	bonus
BONUS_NAME=	minishell_bonus
BONUS_SRCS=	$(BONUS_DIR)/main_bonus.c

# INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include
# INCL_RDL_LIB	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(FUNC) $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(FUNC) $(BONUS_SRCS) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

test: $(LIBFT) $(FUNC) test.c
norm:
	norminette $(SRCS)

.PHONY: all clean fclean re bonus
