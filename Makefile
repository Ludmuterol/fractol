# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpeters <tpeters@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 10:31:31 by tpeters           #+#    #+#              #
#    Updated: 2022/05/12 02:02:13 by tpeters          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fractol.c fractol_color_utils.c fractol_pixel_utils.c
OBJS = $(SRCS:.c=.o)
NAME = fractol

CFLAGS = #-Wall -Wextra -Werror
CC = cc

exec: $(NAME)
	./$(NAME)

debug :
	$(CC) $(CFLAGS) -g -I/usr/include -c $(SRCS)
	gcc $(OBJS) -g -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -I/usr/include -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -c $< -o $@

fclean: 
	rm -f $(NAME) $(OBJS)

re: fclean
	$(MAKE)
