NAME = philo
FLAGS = -Wall -Wextra -Werror
LIBS   = -I./includes/
PHILOSOPHERS = ./includes/philosophers.h

# Compiled directories
SRC = src
OBJ = obj
SUBDIRS = philosophers

# Folder directions
SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

# File directions
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))

# Colors
RESET = \033[0m
RED   = \033[31m
GREEN = \033[32m

all : $(NAME)
bonus : all

$(NAME) : Makefile $(OBJS) $(PIPEX) $(GNL)
	@gcc $(FLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	@make DONE_MSG

$(OBJ)/%.o : $(SRC)/%.c
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@gcc $(CFLAGS) $(LIBS) -c $< -o $@

clean : DELETE_OBJ_MSG
	@rm -rf $(OBJ)

fclean : clean DELETE_PROGRAM_MSG
	@rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re

# Helper messages
DONE_MSG:
	@echo "${GREEN}Philosophers Ready To Go!${RESET}"
DELETE_OBJ_MSG:
	@echo "${RED}Object Files Deleting..${RESET}"
DELETE_PROGRAM_MSG:
	@echo "${RED}Remove Philosophers..${RESET}"