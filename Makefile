# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 10:31:31 by tpeters           #+#    #+#              #
#    Updated: 2022/08/06 20:36:00 by tpeters          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fractol.c fractol_color_utils.c fractol_pixel_utils.c fractol_mandelbrot.c fractol_depth_array.c fractol_julia.c fractol_newton.c fractol_rect_optimization.c
OBJS = $(SRCS:.c=.o)
NAME = fractol

CFLAGS = -Wall -Wextra -Werror
CC = cc


ifeq ($(OS),Windows_NT)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -I/usr/include
		LINK_FLAGS = -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -O3
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -Imlx
		LINK_FLAGS = -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit
    endif
endif

all: $(NAME)

lsan: CFLAGS += -ILeakSanitizer-main -Wno-gnu-include-next
lsan: LINK_FLAGS += -LLeakSanitizer-main -llsan -lc++
lsan: fclean
lsan: all

debug :
	$(CC) $(CFLAGS) -g -c $(SRCS)
	$(CC) $(OBJS) -g $(LINK_FLAGS) -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LINK_FLAGS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

fclean: 
	rm -f $(NAME) $(OBJS)

re: fclean
	$(MAKE)
