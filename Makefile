# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 16:25:13 by tbruinem      #+#    #+#                  #
#    Updated: 2021/02/26 11:14:54 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#SRC = test_vector.cpp
SRC =	test_list.cpp \
		test_vector.cpp \
		test_map.cpp

VEC_INC = ./vector
LIST_INC = ./list
MISC_INC = ./misc
ITER_INC = ./iterator
UTIL_INC = ./util

CONTAINERS = list vector stack queue
INCL = $(CONTAINERS:%=-I ./%)

OBJ = $(SRC:%.cpp=%.o)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
CXX = g++

FT = 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: $(CONTAINERS)

# %.o: %.cpp
# 	@echo "Compiling $@"
# 	$(CXX) $(CFLAGS) -c $< -o $@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

$(CONTAINERS):
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) test_$@.cpp -o test_$@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -I ./map -D FT=$(FT)

map:
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) -I ./map test_$@.cpp ./map/Map.cpp -o test_$@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(CONTAINERS:%=test_%) test_map

re: fclean all

.PHONY: $(CONTAINERS) map
