# Main Variables
NAME = philo_bonus
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread
LIBS = -I./includes/
CC = cc
RM = rm -rf
PHILOSOPHERS = ./includes/philosophers_bonus.h

# Directories
SRC_DIR = src
OBJ_DIR = obj
SRCS = ${wildcard ${SRC_DIR}/*.c}
OBJS = ${patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SRCS}}

# Colors
RESET = \033[0m
RED   = \033[31m
GREEN = \033[32m
YELLOW = \033[33m

all : ${NAME}

${NAME} : Makefile ${OBJS} ${PHILOSOPHERS}
	@${CC} ${FLAGS} ${OBJS} -o ${NAME}
	@make DONE_MSG

${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c | ${OBJ_DIR}
	@make CREATE_OBJECT_FILES
	@${CC} ${CFLAGS} ${LIBS} -c $< -o $@

clean : DELETE_OBJ_MSG
	@${RM} ${OBJ_DIR}

fclean : clean DELETE_PROGRAM_MSG
	@${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re

# Helper messages
DONE_MSG :
	@echo "${GREEN}Philosophers Ready To Go!${RESET}"
DELETE_OBJ_MSG :
	@echo "${RED}Object Files Deleting..${RESET}"
CREATE_OBJECT_FILES :
	@echo "${YELLOW}Create Obj Files..${RESET}"
DELETE_PROGRAM_MSG :
	@echo "${RED}Remove Philosophers..${RESET}"