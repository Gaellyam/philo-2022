# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galamy <galamy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 15:07:32 by galamy            #+#    #+#              #
#    Updated: 2023/02/01 10:55:49 by galamy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
PFLAGS = -pthread -fsanitize=thread -g
HEADER	= -I./includes 

SRC_NAME = action.c philo_thread.c philo_utils.c philosopher.c utils.c
SRC_PATH = ./srcs
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAG) $(PFLAGS) $(HEADER) -o $@ -c $<

$(NAME) :	$(OBJ)
			$(CC) $(CFLAGS) $(PFLAGS) -o $(NAME) $(HEADER) $(OBJ)

all		:	$(NAME)
clean	:	
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re