# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgering <mgering@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 14:57:16 by wdegraf           #+#    #+#              #
#    Updated: 2025/02/28 13:59:17 by mgering          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3D
BONUS_NAME			= cub3D_bonus
DEBUG_NAME			= cub3D_debug
VALGRIND_DEBUG_NAME	= cub3D_valgrind_debug
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

BONUS_SRCS			= $(wildcard src_bonus/*.c)
BONUS_OBJS			= $(BONUS_SRCS:.c=.o)

all: clone $(LIBFT_LIB) $(MLX_LIB) $(NAME)

bonus: clone $(LIBFT_LIB) $(MLX_LIB) $(BONUS_NAME)

debug: clone $(LIBFT_LIB) $(MLX_LIB) $(DEBUG_NAME)

valgrind_debug: clone $(LIBFT_LIB) $(MLX_LIB) $(VALGRIND_DEBUG_NAME)

clone:
	@if [ -d $(LOCAL_DIR) ]; then \
		echo "\033[36mRepository already cloned\033[0m"; \
	else \
		echo "\033[32mCloning and building MLX42\033[0m"; \
		git clone $(REPO_URL) $(LOCAL_DIR) && \
		cmake -S $(LOCAL_DIR) -B $(LOCAL_DIR)/build && \
		make -C $(LOCAL_DIR)/build -j4; \
	fi

$(LIBMLX):
	@echo "\033[32mBuilding MLX42 library\033[0m"
	@cmake -S $(LOCAL_DIR) -B $(LOCAL_DIR)/build && \
	make -C $(LOCAL_DIR)/build -j4

$(LIBFT_LIB):
	@echo "\033[32mBuilding libft library\033[0m"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(BONUS_NAME)

$(DEBUG_NAME): $(DEBUG_OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(DEBUG_OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(DEBUG_NAME)

$(VALGRIND_DEBUG_NAME): $(VALGRIND_DEBUG_OBJS)
	@$(CC) $(CFLAGS) $(VFLAGS) $(VALGRIND_DEBUG_OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(VALGRIND_DEBUG_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.debug.o: %.c
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

%.valgrind_debug.o: %.c
	@$(CC) $(CFLAGS) $(VFLAGS) -c $< -o $@

clean:
	@echo Deleting objects...
	@rm -rf $(OBJS) $(BONUS_OBJS) $(DEBUG_OBJS) $(VALGRIND_DEBUG_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo Deleting executables...
	@rm -f $(NAME) $(BONUS_NAME) $(DEBUG_NAME) $(VALGRIND_DEBUG_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean bonus

re_debug: fclean debug

re_valgrind_debug: fclean valgrind_debug

.PHONY: all bonus debug valgrind_debug clean fclean re re_bonus re_debug re_valgrind_debug clone