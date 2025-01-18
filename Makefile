# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 17:28:43 by jduraes-          #+#    #+#              #
#    Updated: 2024/06/28 18:25:33 by jduraes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC =	main.c utils.c dinner.c dinner_utils.c
OBJS =	${SRC:.c=.o}
HEADER =	philo.h
INCLUDE =	-I .
CFLAGS =	-Wall -Wextra -Werror -pthread
RM =	rm -f
CC =	cc #-g #-fsanitize=thread
.SILENT: $(CC) $(SRC) $(NAME) $(OBJS) 
	
$(NAME):	$(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo compiling
	
all:	$(NAME)

clean:	
	@$(RM) $(OBJS)
	@echo cleaning
		
fclean:	
	@$(RM) $(OBJS) $(NAME)
	@echo full clean
	
		
re:	fclean all
