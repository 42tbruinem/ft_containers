# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 16:25:13 by tbruinem      #+#    #+#                  #
#    Updated: 2020/11/28 14:22:13 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers
#SRC = test_vector.cpp
SRC = test_list.cpp
VEC_INC = ./vector
LIST_INC = ./list
MISC_INC = ./misc
ITER_INC = ./iterator

#USING_FT = ""

#ifeq ($(FT), 1)
#	USING_FT += -D FT=1;
#endif

OBJ = $(SRC:%.cpp=%.o)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
CXX = g++

FT = 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: vector

%.o: %.cpp
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) -c $< -o $@ -I . -I $(ITER_INC) -I $(MISC_INC) -I $(VEC_INC) -I $(LIST_INC) -D FT=$(FT)

vector: test_vector.o
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) $^ -o vector_test -I . -I $(ITER_INC) -I $(MISC_INC) -I $(VEC_INC) -D FT=$(FT)

list: test_list.o
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) $^ -o list_test -I . -I $(ITER_INC) -I $(MISC_INC) -I $(LIST_INC) -D FT=$(FT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:
	vector