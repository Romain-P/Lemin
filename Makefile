##
## Makefile for  in /home/romain.pillot/projects/CPE_2016_Lemin
## 
## Made by romain pillot
## Login   <romain.pillot@epitech.net>
## 
## Started on  Mon Apr 24 08:47:01 2017 romain pillot
## Last update Fri Apr 28 16:30:15 2017 romain pillot
##

CC	=	gcc

NAME	=	lem_in

RM	=	rm -f

SRCS	=	src/main.c			\
		src/parser.c			\
		src/builder.c			\
		src/lemin.c			\
		src/display.c			\
		src/path_finder.c		\
		src/path_util.c			\
		src/util/link_builder.c		\
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

CFLAGS	+=	-Iinc -g3 -Wall -Werror -Wextra -pedantic

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
