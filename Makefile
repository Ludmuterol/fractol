# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/28 17:42:17 by tpeters           #+#    #+#              #
#    Updated: 2022/08/30 17:29:40 by tpeters          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fractol.c fractol_color_utils.c fractol_pixel_utils.c fractol_mandelbrot.c fractol_depth_array.c fractol_julia.c fractol_newton.c fractol_rect_optimization.c
OBJS = $(SRCS:.c=.o)
NAME = fractol

CFLAGS = -Wall -Wextra -Werror
LINK_FLAGS = -Llibft -lft
CC = cc

ifeq ($(OS),Windows_NT)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		CFLAGS += -I/usr/include
		LINK_FLAGS += -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -O3
    endif
    ifeq ($(UNAME_S),Darwin)
	    CFLAGS += -Imlx
		LINK_FLAGS += -Lmlx -lmlx -framework OpenGL -framework AppKit
    endif
endif

LIBFTLIB=/libft/libft.a
LIBMLXLIB=/mlx/libmlx.a
all: $(LIBFTLIB) $(LIBMLXLIB)
all: $(NAME)

debug: CFLAGS += -g
debug: all

LSANLIB = /LeakSanitizer/liblsan.a
lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += -LLeakSanitizer -llsan -lc++
lsan: fclean $(LSANLIB)
lsan: all

$(LSANLIB): 
	@if [ ! -d "LeakSanitizer" ]; then git clone git@github.com:mhahnFr/LeakSanitizer.git; fi
	$(MAKE) -C LeakSanitizer

$(LIBFTLIB):
	@if [ ! -d "libft" ]; then git clone git@github.com:Ludmuterol/libft.git; fi
	$(MAKE) -C libft

$(LIBMLXLIB):
	$(MAKE) -C mlx CFLAGS+="-Wno-deprecated -DSTRINGPUTX11 -O2"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LINK_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C mlx clean
	rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: lsan debug all clean fclean re