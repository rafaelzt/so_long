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

# Trying to use pprof to profile the program 
# Have to install go and go install github.com/google/pprof@latest
# Change source code to use pprof 
# TOO MUCH TROUBLE
# CPUPROFILE=profile.out ./bin./so_long assets/maps/4_map.ber

# kcachegrind works better than pprof
# sudo apt-get install valgrind kcachegrind
# valgrind --tool=callgrind ./bin/so_long assets/maps/4_map.ber

# pip install gprof2dot
# gprof2dot -f callgrind callgrind.out.279800 | dot -Tsvg -o profile.svg
# gprof2dot -f callgrind callgrind.out.279800 | dot -Tpng -o profile.png