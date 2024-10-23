# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 08:37:12 by kecheong          #+#    #+#              #
#    Updated: 2024/10/23 18:23:15 by kecheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := raycast_test
UNAME := $(shell uname)
$(info $$(UNAME) = $(UNAME))

CC := cc
CFLAGS := -Wall -Werror -Wextra

ifeq ($(UNAME), Darwin)
	MLX_dir := ../mlx_mac
	MLX := $(MLX_dir)/libmlx.a
	LDFLAGS := -L../mlx_mac
	LDLIBS := -lmlx
	includes := -I../mlx_mac
	framework := -framework OpenGL -framework AppKit
else
	MLX_dir := ../mlx_linux
	MLX := $(MLX_dir)/libmlx_Linux.a
	LDFLAGS := -L../mlx_linux
	LDLIBS := -lmlx_Linux -lXext -lX11 -lm -lz
	includes := -I../mlx_linux
endif

srcs := raycast_test.c
obj_dir := obj
objs := $(addprefix obj/, $(srcs:.c=.o))

.PHONY: all
all: $(MLX) $(NAME)

$(MLX):
	make -C $(MLX_dir)

$(NAME): $(objs)
	$(CC) $(CFLAGS) $(objs) $(includes) $(LDFLAGS) $(LDLIBS) $(framework) -o $(NAME)

$(obj_dir):
	mkdir -p $(obj_dir)

$(obj_dir)/%.o: %.c | obj
	$(CC) $(CFLAGS) $(includes) $< -c -o $@

.PHONY: clean
clean:
	$(RM) -r $(obj_dir)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: debug
debug: CFLAGS += -g3
debug: all

.PHONY: fsan
fsan: CFLAGS += -fsanitize=address -g3
fsan: all
