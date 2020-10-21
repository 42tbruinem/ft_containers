# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/27 16:25:13 by tbruinem      #+#    #+#                  #
#    Updated: 2020/10/21 11:16:40 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = containers
SRC = main.cpp
VEC_INC = ./vector
MISC_INC = ./misc
ITER_INC = ./iterator

#USING_FT = ""

#ifeq ($(FT), 1)
#	USING_FT += -D FT=1;
#endif

OBJ = $(SRC:%.cpp=%.o)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
CXX = clang++

FT = 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -fsanitize=address
endif

all: $(NAME)

%.o: %.cpp
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) -c $< -o $@ -I $(ITER_INC) -I $(MISC_INC) -I $(VEC_INC) -D FT=$(FT)

$(NAME): $(OBJ)
	@echo "Compiling $@"
	$(CXX) $(CFLAGS) $^ -o $(NAME) -I $(ITER_INC) -I $(MISC_INC) -I $(VEC_INC) -D FT=$(FT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
