# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 14:57:16 by wdegraf           #+#    #+#              #
#    Updated: 2025/01/15 16:15:38 by wdegraf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3d
CC					= gcc
CFLAGS				= -g -fsanitize=address -o -Wall -Wextra -Werror -I./MLX42/include -I./libft -I.
LDFLAGS				= -L./MLX42/build -lmlx42 -L./libft -lft -lglfw -ldl -pthread -lm

# -g -fsanitize=address -o 

REPO_URL			= https://github.com/codam-coding-college/MLX42.git
LOCAL_DIR			= MLX42
MLX_LIB				= $(LOCAL_DIR)/build/libmlx42.a
LIBFT_DIR			= ./libft
LIBFT_LIB			= $(LIBFT_DIR)/libft.a

SRCS				= main.c \
					parse_map.c \
					parse_line.c \
					valid_map.c \
					create_player.c \
					
OBJS				= $(SRCS:.c=.o)

all: clone $(LIBFT_LIB) $(MLX_LIB) $(NAME)

clone:
	@if [ -d $(LOCAL_DIR) ]; then \
		echo "\033[36mRepository already cloned\033[0m"; \
	else \
		echo "\033[32mCloning and building MLX42\033[0m"; \
		git clone $(REPO_URL) $(LOCAL_DIR) && \
		cd $(LOCAL_DIR) && \
		cmake -B build && \
		cd build && \
		make; \
	fi

$(MLX_LIB): clone
	@echo "\033[32mBuilding MLX42 library\033[0m"
	@cd $(LOCAL_DIR) && cmake -B build && cd build && make

$(LIBFT_LIB):
	@echo "\033[32mBuilding libft library\033[0m"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "\033[36m[READY] $(NAME)\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m[OK] $@\033[0m"

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[31mCleanup object files\033[0m"

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[31mFull cleanup completed (MLX42 and libft folders retained)\033[0m"

re: fclean all

.PHONY: all clone clean fclean re