# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 12:52:07 by jwillert          #+#    #+#              #
#    Updated: 2023/03/03 16:08:20 by jwillert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Programm Name
NAME								=	minishell

#	Directories
HEADER_DIR							=	./00_includes/
LIBALLME_DIR						=	./01_liballme/
LIBFT_DIR							=	$(LIBALLME_DIR)/libft/
LIBME_DIR							=	$(LIBALLME_DIR)/libme/
LEXER_DIR							=	./02_lexer/
PARSER_DIR							=	./03_parser/
EXPANDER_DIR						=	./04_expander/
REDIRECTOR							=	./05_redirector/
EXECUTOR							=	./06_executor/
BUILTINS_DIR						=	./07_builtins/
SIGNALS_DIR							=	./08_signals/
CORE_DIR							=	./09_core/

#	Libraries
LIBME								=	$(LIBME_DIR)libme.a
LEXER								=	$(LEXER_DIR)lexer.a
PARSER								=	$(PARSER_DIR)parser.a
EXPANDER							=	$(EXPANDER_DIR)expander.a
REDIRECTOR							=	$(REDIRECTOR_DIR)redirector.a
EXECUTOR							=	$(EXECUTOR_DIR)executor.a
BUILTINS							=	$(BUILTINS_DIR)builtins.a
SIGNALS								=	$(SIGNALS_DIR)signals.a
CORE								=	$(CORE_DIR)core.a

LIBS_DIR_ALL						=	$(LIBALLME_DIR)\
										$(LEXER_DIR)\
										$(PARSER_DIR)\
										$(EXPANDER_DIR)\
										$(REDIRECTOR_DIR)\
										$(EXECUTOR_DIR)\
										$(BUILTINS_DIR)\
										$(SIGNALS_DIR)

LIBS_ALL							=	$(LIBME)\
										$(LEXER)\
										$(PARSER)\
										$(EXPANDER)\
										$(REDIRECTOR)\
										$(EXECUTOR)\
										$(BUILTINS)\
										$(SIGNALS)

#	General Rules
CC									=	cc
DEBUG								=	$(shell $$DEBUG_FLAG)
CFLAGS								=	-Wall -Wextra -Werror $(DEBUG)
REMOVE								=	rm -f

#	Deletes targets on error
.DELETE_ON_ERROR:

#	General targets
.PHONY:									all clean fclean re

all:									$(NAME)

$(NAME):								$(LIBS_ALL)
											$(CC) $(CFLAGS) $(LIBS_ALL)
$(LIBS_ALL):
											for dir in $(LIBS_DIR_ALL); do\
												$(MAKE) -C $$dir; \
											done
clean:
											for dir in $(LIBS_DIR_ALL); do\
												$(MAKE) clean -C $$dir; \
											done
fclean:									clean
											for dir in $(LIBS_DIR_ALL); do\
												$(MAKE) fclean -C $$dir; \
											done
											$(REMOVE) $(NAME)
re:										fclean
											$(MAKE)
