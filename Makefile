
NAME = minishell
CC = gcc
INCLUDE = ./Includes
LIBFT_PATH = ./src/utils/libft/
LIBFT = ./src/utils/libft/libft.a
TERMCAP = -ltermcap
C_FILES = $(shell find . -name "*.c" $(IGNORE_PATHS) -execdir echo {} ';')
OBJDIR = ./src/obj
OBJ = $(C_FILES:%.c=%.o)
O_FILES = $(addprefix $(OBJDIR)/, $(OBJ))
IGNORE_PATHS = ! -path "./src/utils/libft/*" \
				! -path "./cmake-build-debug/*"

SRC_PATHS = ./src \
			./src/execute \
			./src/execute/export \
			./src/init \
			./src/search \
			./src/parser \
			./src/shlvl \
			./src/variable \
			./src/utils \
			./src/utils/check_operators \
			./src/operators \
			./src/operators/pipe \
			./src/operators/redirect \
			./src/history \
			./src/signal \
			./src/utils/GNL

vpath %.c $(SRC_PATHS)
vpath %.o $(OBJDIR)
vpath %.h $(INCLUDE)

#Tools to edit text
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
UNDERLINE = \033[0;4m
TEXT_RESET = \033[0;0m

.PHONY: all clean fclean re libft

all: $(OBJDIR) libft $(NAME)

libft:
	@echo "$(TEXT_RESET)"
	@echo "$(UNDERLINE)$(BLUE)Libft:$(TEXT_RESET)"
	@make -C $(LIBFT_PATH)
	@echo "$(GREEN)Libft has been compiled!\n"
	@echo "$(TEXT_RESET)"
	@echo "$(UNDERLINE)$(BLUE)$(NAME):"

$(NAME): $(OBJ)
	@$(CC) -I$(INCLUDE) $(LIBFT) $(TERMCAP) $(O_FILES) -o $@
	@echo "$(GREEN)Success!"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

%.o: %.c $(INCLUDE)
	@echo "$(CYAN)Compiling $<"
	@$(CC) -I$(INCLUDE) -c $< -o $(OBJDIR)/$@

clean:
	@echo "$(TEXT_RESET)"
	@rm -rf $(OBJDIR) ./Includes/*.h.gch
	@cd $(LIBFT_PATH) && make clean
	@echo "$(YELLOW)Delete 'o' files"

fclean: clean
	@echo "$(TEXT_RESET)"
	@rm -f $(NAME)
	@cd $(LIBFT_PATH) && make fclean
	@echo "$(YELLOW)Delete the binary file '$(NAME)'"

re: fclean all


