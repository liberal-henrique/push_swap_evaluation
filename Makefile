# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 15:28:14 by lliberal          #+#    #+#              #
#    Updated: 2023/03/03 19:08:10 by rasantos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
NAME	=	push_swap
INCLUDE	=	push_swap.h
SRCS	=	push_swap.c \
			util.c \
			util2.c \
			util3.c \
			moviments.c \
			sort.c \
			create_stack.c \
			
OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(INCLUDE)

clean:
		@$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME)
re:	fclean all

.PHONY:	all clean fclean re
