#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/06/26 23:02:52 by jflorimo          #+#    #+#              #
#    Updated: 2014/06/26 23:02:53 by jflorimo         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# SOURCES FILES:

SERVEUR_FILES		=		client_ctrl.c\
							client_ctrl2.c\
							read_write.c\
							init.c\
							init2.c\
							init3.c \
							cmd.c\
							prendre.c \
							poser.c\
							regen_food.c\
							cmd_gfx.c \
							cmd_gfx2.c \
							cmd_gfx3.c \
							cmd_gfx4.c \
							cmd_gfx5.c \
							cmd_gfx6.c \
							parse.c \
							select.c \
							cmd_connect.c \
							cmd_move.c \
							cmd_case.c \
							cmd_c_expulse1.c \
							cmd_c_expulse2.c \
							cmd_c_voir.c \
							cmd_c_lvl.c \
							broadcast.c \
							cmd_c_incantation.c \
							cmd2.c \
							cmd3.c

SERVEUR_INC_FILES	=

# **************************************************************************** #

include		libft/Makefile.sources

export	CC		=	clang

export	INC		=	-I $(PWD)/libft

SERVEUR		=	serveur
CLIENT		=	client
GFX			=	gfx

CFLAGS		=	-Wall -Wextra -Werror -g

INC			+=	-I $(SERVEUR)_dir/includes

INC_DIR		=	includes/
SRC_DIR		=	srcs/

#SERVEUR
SERVEUR_INC_FILES	+=	$(SERVEUR).h

SERVEUR_INC_SRC		=	$(addprefix $(SERVEUR)_dir/$(INC_DIR), $(SERVEUR_INC_FILES))

SERVEUR_FILES		+=	$(SERVEUR).c

SERVEUR_SRC			=	$(addprefix $(SERVEUR)_dir/$(SRC_DIR), $(SERVEUR_FILES))

SERVEUR_OBJ			=	$(SERVEUR_SRC:.c=.o)

#LIBFT
OBJ_LIB		=	$(libft/SRC_LIB:.c=.o)

HEAD_LIB	=	libft/libft.h

LIB			=	-L./ -lft

all:			libft.a $(SERVEUR)

libft.a:		libft/$(OBJ_LIB) $(HEAD_LIB)
	@make -C libft

$(SERVEUR):		libft.a $(SERVEUR_OBJ)
	@$(CC) $(CFLAGS) -o $(SERVEUR) $(SERVEUR_OBJ) $(LIB)
	@echo ""
	@printf '\033[33mCompilation of %s: \033[32mSuccess \
			\033[34m[\033[32m✔\033[34m]\033[0m\n' $(SERVEUR)

%.o:			%.c
	@echo -n _
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean-serveur:
	@/bin/rm -f $(SERVEUR_OBJ)
	@echo "\033[31m"Objects of $(SERVEUR) : deleted"\033[0m"

clean: clean-serveur

fclean:			clean
	@/bin/rm -f $(SERVEUR)
	@echo "\033[31m"$(SERVEUR) : deleted"\033[0m"
	@make fclean -C libft

re:				fclean all

norm:			$(SERVEUR_SRC) $(SERVEUR_INC_SRC)
	@echo "\033[31mNORME server\033[0m":
	@norminette $^
	@make norm -C libft

.PHONY:			all clean fclean re clean-serveur
