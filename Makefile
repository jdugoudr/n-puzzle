# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/09 17:09:22 by jdugoudr          #+#    #+#              #
#    Updated: 2021/02/17 21:39:32 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= n-puzzle

CC			= clang++

CFLAGS	= -Wall -Werror -Wextra
CVERSION=	-std=c++11

CFLAGS	+= $(CVERSION)

SPEED =


OS			= $(shell uname -s)

PWD			= \"$(shell pwd)\"
ECHO		= echo
MKDIR		= mkdir
#RM			=	rm -R

DEBUG		?= 0

SRCDIR   = srcs
OBJDIR   = objs/
INCLUDESDIR = incs
TESTDIR			=	test


VPATH		= $(INCLUDESDIR) \
					$(SRCDIR) \
					$(SRCDIR)/templates \
					$(SRCDIR)/AStar \
					$(SRCDIR)/AStar/heuristic



SRCS			=	main.cpp \
						Node.cpp \
						Puzzle.cpp \
						Manhattan.cpp \
						Hamming.cpp \
						AStar.cpp

INCLUDES	= n-puzzle.hpp \
						Node.hpp \
						Puzzle.hpp \
						IHeuristic.hpp \
						Manhattan.hpp \
						Hamming.hpp \
						AStar.hpp \
						pq_custom.hpp \
						find_if_mix.hpp

TEST_UNARY=	case \
					 	node \
						puzzle \
						astar \
						time
#						pq_custom

#OBJECTS			=	$(addprefix $(OBJDIR), $(notdir $(SRCS:.cpp=.o)))
OBJECTS			=	$(addprefix $(OBJDIR),  $(SRCS:.cpp=.o))
#OBJECTS			=	$(SRCS:.cpp=.o)
INC 				=	-I $(INCLUDESDIR) -I $(SRCDIR)/AStar -I $(SRCDIR) -I $(SRCDIR)/AStar/heuristic -I $(SRCDIR)/templates

EOC = \033[0m
ifeq ($(OS),Linux)
	CFLAGS += -DPATH=$(PWD) $(INC)
	OK_COLOR = \033[1;32m
	FLAGS_COLOR = \033[1;34m
	#COMP_COLOR =
else
	CFLAGS += -DPATH=$(PWD) $(INC)
	OK_COLOR = \x1b[32;01m
	#COMP_COLOR = \x1b[34;01m
	FLAGS_COLOR = \x1b[34;01m
#	COMP_COLOR =
endif

ifeq ($(DEBUG),1)
	CFLAGS += -g3
endif

all:
	@$(ECHO) $(SRCS)
	@$(ECHO) $(OBJECTS)
	@$(ECHO) "$(FLAGS_COLOR)Compiling with flags $(CFLAGS) $(EOC)"
	@$(MAKE) $(NAME) $(SPEED)

$(NAME): $(OBJDIR) $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LFLAGS) \
		&& $(ECHO) "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR):
	@$(MKDIR) $@

$(OBJDIR)%.o:$(SRC_DIR)%.cpp $(INCLUDES)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@$(ECHO) "${COMP_COLOR}$< ${EOC}"




#######################################################
## Add here rules for particular test

# TEST_OBJ is a shell variable
.ONESHELL: # This is required to use variable on diff lines
$(TEST_UNARY): $(OBJDIR) $(OBJECTS)
	@TEST_OBJ=$(OBJDIR)$@.o
	@$(CC) -c $(TESTDIR)/$@.cpp -o "$${TEST_OBJ}" $(CFLAGS)
	@$(CC) -o $(TESTDIR)/$@ "$${TEST_OBJ}" $(filter-out $(OBJDIR)main.o,$(OBJECTS)) $(CFLAGS) $(LFLAGS) \
	&& $(ECHO) "$(OK_COLOR)$@ test program linked with success !$(EOC)"
#######################################################



clean:
	@$(RM) $(OBJECTS)
	@$(RM) -r $(OBJDIR) && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) objects files ${EOC}"

fclean: clean
	@$(RM) $(addprefix $(TESTDIR)/, $(TEST_UNARY)) \
		&& $(ECHO) "${OK_COLOR}Successfully cleaned $(TESTDIR) ${EOC}"
	@$(RM) $(NAME)  && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) ${EOC}"

re: fclean all

rere:
	@$(RM) $(OBJECTS)
	@$(RM) -r $(OBJDIR)
	@$(RM) $(NAME)
	@$(MAKE) all

os:
	@$(ECHO) $(OS)

.PHONY: all clean fclean re debug
