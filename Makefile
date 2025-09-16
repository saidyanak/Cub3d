NAME = cud3d

GNL = get_next_line
CC = gcc 
CFLAGS = -g -Wall -Wextra -Werror
SRCS = main.c \
		map_control.c \
		utils.c \
		$(GNL)/get_next_line_utils.c \
		$(GNL)/get_next_line.c 

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created successfully!$(NC)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(NC)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)🧹 Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re