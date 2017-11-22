# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/07 23:21:20 by nmougino          #+#    #+#              #
#    Updated: 2017/11/16 00:05:43 by nmougino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Compilator - clang est plus sur que gcc
CC =		clang
CFLAGS =	-Wall -Wextra -Werror -Weverything -Wno-padded #-g #-fsanitize=address

#	Binary
NAME =		libft_malloc_$$HOSTTYPE.so
FINAL =		libft_malloc.so

#	Default rule
DEFRULE =	all

#	Dossiers utiles
SRCDIR =	srcs
INCDIR =	includes
OBJDIR =	objs

#	Liste des sources
SRC =		free.c \
			realloc.c \
			m_page.c \
			m_pageseek.c \
			malloc.c \
			show_alloc_mem.c
LIB =		ft
OBJ =		$(SRC:.c=.o)

#	Prefixes
LLIBP =		$(addprefix -l, $(LIB))
LIBP =		$(addprefix lib, $(LIB))
OBJP =		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#	Couleurs
DEF =		\033[0m
GRA =		\033[1m
SOU =		\033[4m
BLI =		\033[5m
BLA =		\033[30m
RED =		\033[31m
GRE =		\033[32m
YEL =		\033[33m
BLU =		\033[34m
PUR =		\033[35m
CYA =		\033[36m
WHI =		\033[37m

define \n


endef

# #
#	RULES
#

.PHONY = default glu all re libcomp $(OBJDIR) $(NAME) clean fclean

ifneq ($(wildcard /Users/nmougino/.brew/bin/lolcat), "")
	LOLCAT = | lolcat -F 0.25
endif


UNICORN = "\n \t     \\ \n \t      \\ \n \t       \\\\ \n \t        \\\\ \n \t         >\\/7 \n \t     _.-(6\'  \\          Unicorns get the shit done\n \t    (=___._/\` \\ \n \t         )  \ | \n \t        /   / | \n \t       /    > / \n \t      j    < _\ \n \t  _.-\' :      \`\`. \n \t  \\ r=._\\        \`. \n \t <\`\\\\_  \\         .\`-. \n \t  \\ r-7  \`-. ._  \' .  \`\\ \n \t   \\\`,      \`-.\`7  7)   ) \n \t    \\/         \\|  \\\'  / \`-._ \n \t               ||    .\'                   Be more unicorn.\n \t                \\  ( \n \t                 >\\  > \n \t             ,.-\' >.\' \n \t            <.\'_.\'\' \n \t              <\' \n"

#	Main rules
default:
	@echo "$(GRA)  DEFAULT RULE EXECUTION  :::  rule $(DEFRULE)$(DEF)"
	@$(addprefix make ,$(DEFRULE))
	@echo "$(GRE)$(GRA)Programme termine :)$(DEF)"
	@echo $(UNICORN) $(LOLCAT)

glu: re
	make clean

all: libcomp $(OBJDIR) $(NAME)

re: fclean all
	@echo $(UNICORN) $(LOLCAT)

reloc: fcleanloc all

#	Compilation rules
libcomp:
	make all -C lib$(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)" $(LOLCAT)
	@$(CC) $(CFLAGS)	$(ADDFLAGS) -c -o $@ $^ -I $(INCDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(GRA)$(CYA)@ ++ Objects compilation$(DEF)"

$(NAME): $(OBJP)
	@echo "$(GRA)$(CYA)@ ++ $@ compilation$(DEF)"
	@$(CC) $(CFLAGS) $(ADDFLAGS) -shared -o $@ $^ -I $(INCDIR) -L lib$(LIB) -l$(LIB)
	@rm -f libft_malloc.so
	@ln -s $(NAME) $(FINAL)

#	MrProper's legacy
cleanloc:
	@echo "$(RED)@ Objects deletion$(DEF)"
	@rm -rf $(OBJDIR)


clean: cleanloc
	@echo "$(RED)@ Library deletion$(DEF)"
	@make fclean -C libft/

fcleanloc: cleanloc
	@echo "$(RED)@ Binary deletion$(DEF)"
	@rm -f $(NAME)
	@rm -f $(FINAL)

fclean: clean
	@echo "$(RED)@ Binary deletion$(DEF)"
	@rm -f $(NAME)
	@rm -f $(FINAL)
