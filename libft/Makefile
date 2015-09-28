#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 09:49:07 by rbenjami          #+#    #+#              #
#    Updated: 2013/11/20 11:31:21 by rbenjami         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

include		Makefile.sources

NAME		=	libft

CFLAGS	=	-Wall -Wextra -Werror -g

OBJ_LIB		=	$(SRC_LIB:.c=.o)

HEAD		=	libft.h get_next_line.h

all:		$(NAME)

$(NAME):	$(OBJ_LIB)
	@ar -rc ../$(NAME).a $(OBJ_LIB)
	@ranlib ../$(NAME).a
	@echo ""
	@printf '\033[33mCompilation of %s: \033[32mSuccess \t\
			\033[34m[\033[32m✔\033[34m]\033[0m\n' $(NAME)

$(OBJ_LIB):	$(HEAD)

%.o:		%.c
	@echo -n _
	@$(CC) $(CFLAGS) -I. -c $< -o $@ $(INC)

clean:
	@echo "\033[31m"Objects of libft.a : deleted"\033[0m"
	@/bin/rm -f $(OBJ_LIB)

fclean:		clean
	@echo "\033[31m"libft.a : deleted"\033[0m"
	@/bin/rm -f ../$(NAME).a

re:			fclean all

norm:		$(SRC_LIB) $(HEAD)
	@echo "\033[31mNORME $(NAME)\033[0m":
	@norminette $^

.PHONY:		all re fclean clean norm
