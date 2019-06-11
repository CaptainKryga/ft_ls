# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/28 16:05:16 by gleonett          #+#    #+#              #
#    Updated: 2019/03/27 17:53:49 by rwalder-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LNAME = libft
SRCS = *.c get_types/*.c utils/*.c va_functions/*.c print/*.c \
        check_fmt/*.c
LINC = libft/libft.a
OBJ = libft/*.o *.o
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(LNAME)
	gcc $(FLAGS) -I. -I libft -c $(SRCS) 
	ar rc $(NAME) $(OBJ) $(LINC)
	ranlib $(NAME)

clean:
	@make clean -C $(LNAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LNAME)
	@rm -f $(NAME)

re: fclean all
