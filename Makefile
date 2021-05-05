# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 16:25:13 by tbruinem      #+#    #+#                  #
#    Updated: 2021/05/05 12:08:04 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VEC_INC = ./vector
LIST_INC = ./list
MISC_INC = ./misc
ITER_INC = ./iterator
UTIL_INC = ./util

CONTAINERS = list vector stack queue map
INCL := $(CONTAINERS:%=-I ./%)


CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
CXX = clang++

CONTAINERS := $(CONTAINERS:%=test_%)

SRC :=	$(CONTAINERS:%=%.cpp)
OBJ :=	$(SRC:%.cpp=%.o)

FT = 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: $(CONTAINERS)

%.o: %.cpp
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) -c $< -o $@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

.SECONDEXPANSION:
$(CONTAINERS): $$@.o
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) $^ -o $@ -I . -I $(ITER_INC) -I $(UTIL_INC) -I $(MISC_INC) $(INCL) -D FT=$(FT)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(CONTAINERS)

re: fclean all
