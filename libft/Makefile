# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctogoe <ctogoe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/09 18:12:03 by ctogoe            #+#    #+#              #
#    Updated: 2022/02/01 06:58:15 by ctogoe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a

SRC = 		ft_strlen.c ft_strncmp.c \
			ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c  ft_split.c ft_calloc.c ft_memset.c


BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c 
OBJS 		= $(SRC:.c=.o)

BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

CC 			= gcc $(CFLAGS)  

CFLAGS 		= -Wall -Wextra -Werror

RM 			= rm -f

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)

bonus:		$(OBJS) $(BONUS_OBJS)
			ar rc $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
