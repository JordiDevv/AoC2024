NAME = gnl.out
BNAME = gnl_bonus.out

COLOR_RESET = \033[0m
COLOR_GREEN = \033[0;32m

INCLUDE = get_next_line.h
INCLUDE_BONUS = get_next_line_bonus.h

COMPILE_FLAGS = cc -Wall -Werror -Wextra

SRCS = get_next_line.c get_next_line_utils.c main.c
BSRCS = get_next_line_bonus.c get_next_line_utils_bonus.c main.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILE_FLAGS) -o $@ $^

%.o: %.c $(INCLUDE)
	$(COMPILE_FLAGS) -c $< -o $@

bonus: $(BNAME)

$(BNAME): $(BOBJS)
	$(CC)  -o $@ $^

%.o: %.c $(INCLUDE_BONUS)
	$(CC)  -c $< -o $@

clean: 
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

ex: $(NAME)
	@./$(NAME)

ex_bonus: $(BNAME)
	@./$(BNAME) bonus

prueba_total: $(NAME) $(BNAME)
	@echo "$(COLOR_GREEN)El programa se ejecuta con normalidad$(COLOR_RESET)"
	@./$(NAME)
	@echo "\n"
	@echo "$(COLOR_GREEN)Intentamos el bonus con él$(COLOR_RESET)"
	@./$(NAME) bonus
	@echo "\n"
	@echo "$(COLOR_GREEN)El bonus con las fuentes adecuadas$(COLOR_RESET)"
	@./$(BNAME) bonus
	@echo "\n"

.PHONY: all clean fclean re bonus
