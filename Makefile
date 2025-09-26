
NAME = cud3d
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
MAPS_DIR = maps


SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/map_control.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parse_utils.c \
	$(SRC_DIR)/ft_libft.c \
	$(SRC_DIR)/map_check.c \
	$(SRC_DIR)/get_next_line_utils.c \
	$(SRC_DIR)/get_next_line.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


INSPECT_SRC = $(SRC_DIR)/inspect_map.c
INSPECT_OBJS = \
	$(OBJ_DIR)/inspect_map.o \
	$(OBJ_DIR)/map_control.o \
	$(OBJ_DIR)/parser.o \
	$(OBJ_DIR)/parse_utils.o \
	$(OBJ_DIR)/ft_libft.o \
	$(OBJ_DIR)/map_check.o \
	$(OBJ_DIR)/get_next_line_utils.o \
	$(OBJ_DIR)/get_next_line.o

INSPECT_BIN = inspect_map

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m


all: $(NAME) $(INSPECT_BIN)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) created successfully!$(NC)"


$(INSPECT_BIN): $(INSPECT_OBJS)
	@echo "$(YELLOW)Linking $(INSPECT_BIN)...$(NC)"
	@$(CC) $(CFLAGS) $(INSPECT_OBJS) -o $(INSPECT_BIN)
	@echo "$(GREEN)✅ $(INSPECT_BIN) created successfully!$(NC)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "$(RED)🧹 Cleaning object files...$(NC)"
	@rm -f $(OBJ_DIR)/*.o $(NAME) $(INSPECT_BIN)

fclean: clean
	@echo "$(RED)🧹 Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re