# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzamolo- <rzamolo-@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 13:17:36 by rzamolo-          #+#    #+#              #
#    Updated: 2024/11/02 21:14:17 by rzamolo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall
CFLAGS += -Werror
CFLAGS += -Wextra
CFLAGS += -O3

# MLX
MLX_FLAGS = -lmlx -lm -lXext -lX11

# Libft
LIBFT_DIR = inc
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

A = assets/maps assets/images
B = bin/
I = inc/
O = obj/
S = src/
T = tst/


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

all: dirs $(MLX_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(O)%.o: $(S)%.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

debug: CFLAGS += -g
debug: fclean all

keys:
	$(CC) $Scapture_keycode.c -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

dirs:
	@echo "Creating directories if doesn't exist"
	mkdir -p $(B) $(I) $(O) $(S) $(T)

clean:
	$(RM) $(O)*

fclean: clean
	$(RM) $(B)*

re: fclean all

.PHONY: all $(NAME) dirs clean fclean 
