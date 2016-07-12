##
## Makefile for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
##
## Made by Loïc GIGOMAS
## Login   <gigoma_l@epitech.net>
##
## Started on  Thu Jul  7 09:25:01 2016 Loïc GIGOMAS
## Last update Tue Jul 12 17:36:41 2016 drozdz_b
##

BIN_SERVER	= serverJ2T3

BIN_CLIENT	= clientJ2T3

SRC_SERVER	= main.c \
		  server.c \
		  select.c \
		  player.c \
		  player_cmd.c \
		  player_utils.c \
		  player_phys.c \
		  cells.c \
		  ../new.c \
		  ../vector_modifiers.c \
		  ../vector_accessors.c \
		  ../splited.c \
		  ../map_modifiers.c \
		  ../map_accessors.c \
		  ../entity.c \
		  ../tcpnets.c \
		  ../pair.c \
		  ../gnl.c \
		  ../game_map.c \
		  ../get_opt.c \
		  ../opt_types.c

SRC_CLIENT	= main.c 	\
		  ../new.c 	\
		  ../tcpnetc.c 	\
		  ../thread.c	\
		  graphic.c	\
		  graphic2.c	\
		  graphic3.c	\
		  graphic4.c	\
		  ../pair.c	\
		  ../vector_accessors.c	\
		  ../vector_modifiers.c	\
		  ../map_modifiers.c	\
		  ../game_map.c		\
		  ../splited.c		\
		  ../map_accessors.c	\
		  ../gnl.c

CC		= gcc

CFLAGS		+= -W -Wall -Wextra -std=gnu99

CFLAGS		+= -Iinclude/

RM		= rm -f

SRCDSTCOM	= src

SRCDST1		= $(SRCDSTCOM)/server

SRCDST2		= $(SRCDSTCOM)/client

OBJDSTCOM	= obj

OBJDST1		= $(OBJDSTCOM)/server

OBJDST2		= $(OBJDSTCOM)/client

SRC1		= $(addprefix $(SRCDST1)/, $(SRC_SERVER))

SRC2		= $(addprefix $(SRCDST2)/, $(SRC_CLIENT))

OBJ_SERVER	= $(addsuffix .o, $(basename $(subst $(SRCDST1), $(OBJDST1), $(SRC1))))

OBJ_CLIENT	= $(addsuffix .o, $(basename $(subst $(SRCDST2), $(OBJDST2), $(SRC2))))

all		: server client
		  @echo -e "\033[32mPlease do '\033[1msource autocompletion\033[0;32m' in your shell.\033[0m"

$(OBJDST1)/%.o	: $(SRCDST1)/%.c
		  @mkdir -p $(OBJDST1)
		  $(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJDST2)/%.o	: $(SRCDST2)/%.c
		  @mkdir -p $(OBJDST2)
		  $(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BIN_SERVER)	: $(OBJ_SERVER)
		  $(CC) $(CFLAGS) $(OBJ_SERVER) -o $(BIN_SERVER) $(LDFLAGS) -lm

$(BIN_CLIENT)	: $(OBJ_CLIENT)
		  $(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(BIN_CLIENT) $(LDFLAGS) -lpthread -lSDL2-2.0 -lSDL2_image

server		: $(BIN_SERVER)

client		: $(BIN_CLIENT)

clean		:
		  $(RM) $(OBJ_SERVER)
		  $(RM) $(OBJ_CLIENT)

fclean		: clean
		  $(RM) $(BIN_SERVER)
		  $(RM) $(BIN_CLIENT)

re		: fclean all

.PHONY		: all clean fclean re server client
