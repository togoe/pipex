NAME            =    pipex
SRC_DIR            =    ./src/
INC_DIR            =    ./inc/
SRCS            =    main.c utils.c ft_err.c
                    
SRC_BASENAME    =    $(addprefix $(SRC_DIR), $(SRCS))        
OBJS            =    $(SRC_BASENAME:.c=.o)
CC              =    clang
FLAGS			=	 -Wall -Wextra -Werror -I $(INC_DIR) -I ./libft/


all				:    $(NAME)
.c.o			:
				$(CC) $(FLAGS) -c $< -o $@

$(NAME)			:    $(OBJS)
			make -C ./libft/
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) -L./libft/ -lft
			@echo [$(NAME)] : Created !

clean        :
			rm -rf $(OBJS)
			make fclean -C ./libft/
			@echo "[OBJS] Deleted"

fclean        :    clean
			rm -f $(NAME)
			@echo "[$(NAME)]: Deleted"

re            :    fclean all

.PHONY: all clean fclean re
