# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 13:17:36 by rzamolo-          #+#    #+#              #
#    Updated: 2025/02/20 23:05:55 by rzamolo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -O3
CFLAGS += -g


# Libft
LIBFT_DIR = /home/rzamolo-/Includes
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MLX
MLX_DIR = /home/rzamolo-/Includes
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lmlx -lm -lXext -lX11


A = assets/maps assets/images
B = bin/
I = inc/
O = obj/
S = src/


# So_long: Source files
SRCS = \
$Smap.c \
$Spath.c \
$Splayer.c \
$Sposition.c \
$Srender.c \
$Sso_long.c \
$Ssprites.c \
$Sutils.c \

# Object files
OBJS = $(patsubst $(S)%.c,$(O)%.o,$(SRCS))

NAME = $(B)so_long

RM = rm -f

all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $B
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(O)%.o: $(S)%.c
	@echo "Compiling $< into $@"
	@mkdir -p $O
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	$(RM) $(O)*

fclean: clean
	$(RM) $(B)*

re: fclean all

.PHONY: all clean fclean re

# valgrind --tool=callgrind ./bin/so_long assets/maps/4_map.ber

# pip install gprof2dot
# gprof2dot -f callgrind callgrind.out.279800 | dot -Tsvg -o profile.svg
# gprof2dot -f callgrind callgrind.out.279800 | dot -Tpng -o profile.png
