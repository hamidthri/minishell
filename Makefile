# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 16:21:20 by mmomeni           #+#    #+#              #
#    Updated: 2023/11/30 18:30:40 by htaheri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell
CFLAGS		=		-Wall -Wextra -Werror
FUNC		=		history.c utils.c builtins/cd_custom.c
SRCS		=		main.c $(FUNC)
LIBFT_DIR	=		libft
LIBFT		=		$(LIBFT_DIR)/libft.a

BONUS_DIR	=		bonus
BONUS_NAME	=		minishell_bonus
BONUS_SRCS	=		$(BONUS_DIR)/main_bonus.c

all: $(NAME)

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -L$(LIBFT_DIR) -lft  -lreadline -o $(NAME)

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

.PHONY: all clean fclean re bonus
