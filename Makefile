# --------------------------- Executable and Library ------------------------- #
NAME    := ADC

CC      := cc
CFLAGS  := -Wextra -Wall -Werror
INCDIR  := ./includes
HEADERS := -I$(INCDIR) -I$(LIBFT)/includes

LIBFT   := ./libft
LIBFT_A := $(LIBFT)/libft.a
LIBS    := $(LIBFT_A) -lm

SRCS    := $(wildcard ./src/*.c)
OBJS    := $(SRCS:.c=.o)

# ------------------------------ Colors -------------------------------------- #
RESET   := \033[0m
GREEN   := \033[32m
BLUE    := \033[34m
RED     := \033[31m

# ------------------------------- Targets ------------------------------------ #
all: libft $(NAME)
	@echo "$(GREEN)Program $(NAME) compiled successfully!$(RESET)"

# Ensure Libft is cloned and built
libft:
	@echo "$(BLUE)[LIBFT] Checking for Libft library...$(RESET)"
	@if [ ! -d "$(LIBFT)" ]; then \
		echo "$(RED)Libft not found! Cloning...$(RESET)"; \
		if ! git clone https://github.com/iliamunaev/libft-C-library $(LIBFT); then \
			echo "$(RED)Error: Failed to clone Libft!$(RESET)"; \
			exit 1; \
		fi; \
	fi
	@if [ ! -f "$(LIBFT_A)" ]; then \
		echo "$(BLUE)[LIBFT] Building Libft library...$(RESET)"; \
		make -C $(LIBFT); \
	fi

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "$(BLUE)Linking executable: $(NAME)$(RESET)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@echo "$(BLUE)Compiling: $(notdir $<)...$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@echo "$(GREEN)Removing object files...$(RESET)"
	rm -rf $(OBJS)
	@if [ -d "$(LIBFT)" ]; then make -C $(LIBFT) clean; fi
	@echo "$(BLUE)Cleaned object files and directories.$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executable: $(NAME)...$(RESET)"
	rm -rf $(NAME)
	@if [ -d "$(LIBFT)" ]; then make -C $(LIBFT) fclean; fi
	@echo "$(GREEN)'$(NAME)' executable successfully removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft
