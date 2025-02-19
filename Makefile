# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 14:57:16 by wdegraf           #+#    #+#              #
#    Updated: 2025/02/19 12:12:32 by wdegraf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3d
DEBUG_NAME			= cub3d_debug
VALGRIND_DEBUG_NAME	= cub3d_valgrind_debug
CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -I./MLX42/include -I./libft -I.
DFLAGS				= -g -fsanitize=address
VFLAGS				= -g
LDFLAGS				= -L./MLX42/build -lmlx42 -L./libft -lft -lglfw -ldl -pthread -lm

REPO_URL			= https://github.com/codam-coding-college/MLX42.git
LOCAL_DIR			= MLX42
MLX_LIB				= $(LOCAL_DIR)/build/libmlx42.a
LIBFT_DIR			= ./libft
LIBFT_LIB			= $(LIBFT_DIR)/libft.a

SRCS				= $(wildcard src/*.c)
OBJS				= $(SRCS:.c=.o)
DEBUG_OBJS			= $(SRCS:.c=.debug.o)
VALGRIND_DEBUG_OBJS	= $(SRCS:.c=.valgrind_debug.o)

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

$(DEBUG_NAME): $(DEBUG_OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(DEBUG_NAME) $(DEBUG_OBJS) $(LDFLAGS)
	@echo "\033[36m[READY] $(DEBUG_NAME)\033[0m"

$(VALGRIND_DEBUG_NAME): $(VALGRIND_DEBUG_OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(VFLAGS) -o $(VALGRIND_DEBUG_NAME) $(VALGRIND_DEBUG_OBJS) $(LDFLAGS)
	@echo "\033[36m[READY] $(VALGRIND_DEBUG_NAME)\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[32m[OK] $@\033[0m"

%.debug.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@
	@echo "\033[32m[OK] $@\033[0m"

%.valgrind_debug.o: %.c
	$(CC) $(CFLAGS) $(VFLAGS) -c $< -o $@
	@echo "\033[32m[OK] $@\033[0m"	

clean:
	rm -f $(OBJS) $(DEBUG_OBJS) $(VALGRIND_DEBUG_OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[31mCleanup object files\033[0m"

fclean: clean
	rm -f $(NAME) $(DEBUG_NAME) $(VALGRIND_DEBUG_NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "\033[31mFull cleanup completed (MLX42 and libft folders retained)\033[0m"

re: fclean all

debug: $(DEBUG_NAME)

valgrind_debug: $(VALGRIND_DEBUG_NAME)

.PHONY: all clone clean fclean re debug valgrind_debug