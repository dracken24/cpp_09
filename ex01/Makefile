# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 22:58:04 by nadesjar          #+#    #+#              #
#    Updated: 2023/04/30 00:02:29 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS 		= ./objs/
P_SRCS		= ./srcs/
P_INCL		= ./includes/

FILES			= $(P_SRCS)main.cpp \

OBJS			= $(patsubst $(P_SRCS)%.cpp, $(P_OBJS)%.o, $(FILES))

CC				= c++

CFLAGS			= -Wall -Werror -Wextra -std=c++98

NAME			= RPN

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME) msg_out

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

# --------------------------- Recompilation Headers --------------------------- #

$(P_OBJS)main.o:	$(P_SRCS)main.cpp $(P_INCL)RPN.hpp
	@mkdir -p $(P_OBJS)
	@$(CC) $(CFLAGS) -I. -c $< -o $@
	@printf "$G■"

# ----------------------------------- Git ------------------------------------ #

COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

# --------------------------------- Messages --------------------------------- #

msg_in:
	@echo $L"COMPILATION DE RPN EN COURS..."$W

msg_out:
	@echo $L"\nRPN READY !!!"$W
	
signat:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--* $LPROJET: CPP09 EX01    PAR: NADESJAR$G *--*             |"
	@echo " |             ---------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"

# ---------------------------------- Colors ---------------------------------- #

R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
Y   = $(shell tput -Txterm setaf 3)
L	= $(shell tput -Txterm setaf 5)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)

# ---------------------------------- Clean ----------------------------------- #

clean:	
	@rm -fr $(P_OBJS)

fclean: clean
	@echo $G"                                    BYE BYE !!!"$W
	@rm -f $(NAME)


re: fclean all


.PHONY: all msg_in msg_out clean fclean re signat
