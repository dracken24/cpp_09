# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 13:22:35 by nadesjar          #+#    #+#              #
#    Updated: 2023/04/26 14:35:32 by dracken24        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS 		= ./objs/
P_SRCS		= ./srcs/
P_INCL		= ./includes/

FILES			= $(P_SRCS)main.cpp $(P_SRCS)BitcoinExchange.cpp  \

OBJS			= $(patsubst $(P_SRCS)%.cpp, $(P_OBJS)%.o, $(FILES))

CC				= c++

CFLAGS			= -Wall -Werror -Wextra -std=c++98 -Wno-unused-parameter -Wno-unused-variable

NAME			= btc

# ------------------------------- Compilation -------------------------------- #

all: signat msg_in $(NAME) msg_out

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

# --------------------------- Recompilation Headers --------------------------- #

$(P_OBJS)main.o:	$(P_SRCS)main.cpp $(P_INCL)BitcoinExchange.hpp
	@mkdir -p $(P_OBJS)
	@$(CC) $(CFLAGS) -I. -c $< -o $@
	@printf "$G■"

$(P_OBJS)BitcoinExchange.o:	$(P_SRCS)BitcoinExchange.cpp $(P_INCL)BitcoinExchange.hpp
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
	@echo $L"COMPILATION DE Bitcoin EN COURS..."$W

msg_out:
	@echo $L"\nBitcoin READY !!!"$W
	
signat:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--* $LPROJET: CPP09 EX00    PAR: NADESJAR$G *--*             |"
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
