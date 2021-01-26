# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 16:25:13 by tbruinem      #+#    #+#                  #
#    Updated: 2021/01/24 15:25:23 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers
#SRC = test_vector.cpp
SRC =	test_list.cpp \
		test_vector.cpp \
		test_map.cpp

VEC_INC = ./vector
LIST_INC = ./list
MISC_INC = ./misc
ITER_INC = ./iterator
UTIL_INC = ./util

INCL = -I ./vector -I ./map -I ./list

CONTAINERS = list vector map

OBJ = $(SRC:%.cpp=%.o)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
CXX = g++

FT = 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: $(CONTAINERS)

%.o: %.cpp
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) -c $< -o $@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

$(CONTAINERS): $(OBJ)
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) $^ -o $@_test -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf list_test vector_test

re: fclean all

.PHONY:
	vector