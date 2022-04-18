SRCS		=	${wildcard philo/*.c}		\

B_SRCS		=	${wildcard philo_bonus/*.c}	\

OBJS		=	$(SRCS:.c=.o)	

B_OBJS		=	$(B_SRCS:.c=.o)	

HEADS		=	${wildcard philo/*.h}

B_HEADS		=	${wildcard philo_bonus/*.h}

NAME		=	philo/philo

B_NAME		=	philo_bonus/philo_bonus

GCC			=	gcc -MMD -Wall -Wextra -Werror

RM			=	rm -f

%.o: 		%.c
			$(GCC) -c $< -o $@

$(NAME):	$(HEADS) $(OBJS)
			$(GCC) $(OBJS) -o $(NAME)

$(B_NAME):	$(B_HEADS) $(B_OBJS)
			$(GCC) $(OBJS) -o $(NAME)
			

all:		$(NAME)

bonus:		$(B_NAME)

clean:
			$(RM) $(wildcard */*.d)
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			$(RM) $(NAME)
			$(RM) $(B_NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re