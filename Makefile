# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleonett <gleonett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/28 16:05:16 by gleonett          #+#    #+#              #
#    Updated: 2019/03/27 17:36:48 by rwalder-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LNAME = ft_printf
SRCS = *.c 
LINCLUDES = ft_printf/libftprintf.a
OBJ = *.o
NORMA = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C ft_printf fclean && make -C ft_printf && make -C ft_printf clean
	gcc $(NORMA) -I . -I ft_printf -I ft_printf/libft -c $(SRCS) 
	gcc $(OBJ) $(LINCLUDES) -o $(NAME)
clean:
	@rm -f $(OBJ)
	make -C ft_printf clean

fclean: clean
	@rm -f $(NAME)
	make -C ft_printf fclean

re: fclean all
