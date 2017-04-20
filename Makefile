##
## makefile for make in tetris
## 
## Made by Romain Pillot
## Login   <romain.pillot@epitech.net>
## 
## Started on  Sat Oct 29 17:09:21 2016 romain pillot
## Last update Thu Apr 20 19:05:24 2017 romain pillot
##

CC	=	gcc

NAME	=	lem_in

RM	=	rm -f

SRCS	=	src/main.c			\
		src/util/list.c			\
		src/util/nbr_util.c		\
		src/util/out_util.c		\
		src/util/scanner.c		\
		src/util/tab_util.c		\
		src/util/str_util.c		\
		src/util/str_util_more.c	\
		src/util/str_util_plus.c	\
		src/util/util.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-Iinc -g3 #-Werror -Wall -Wextra

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
