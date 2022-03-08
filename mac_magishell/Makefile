# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: akramp <akramp@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/08 16:53:59 by akramp        #+#    #+#                  #
#    Updated: 2022/03/08 13:32:32 by Angi          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = 		magi_shell
CC = 		gcc
FLAGS =  	-Wall -Werror -Wextra
TEST_FLAG =	-lcriterion -L/Users/akramp/.brew/Cellar/criterion/2.3.3/lib/
READLINE_FLAG = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
#READLINE_FLAG = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
#Codam macs flags ^^

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:* SOURCES ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

MAIN =		./SRC/magi_shell.c
SRC =		builtins/builtins.c libft/functions_ms.c libft/functions_ms2.c\
			tokenizer/tokenizer.c lists/token_list.c \
			libft/ft_substr.c GNL/get_next_line.c \
			GNL/get_next_line_utils.c error/error.c \
			builtins/builtins_redirect.c lists/list_functions.c \
			libft/ft_itoa.c libft/ft_atoi.c libft/ft_strjoin.c \
			env_export/export.c builtins/echo.c env_export/env_str_edit.c \
			ascii/ascii.c parsing/parser.c \
			env_export/env_basics.c tokenizer/tokenizer_part2.c \
			tokenizer/tokenizer_part3.c lists/findlist.c \
			tokenizer/tokenizer_part4.c redirections/redirections_fd_func.c \
			redirections/redirections_list_func.c signal_handling/signal.c\
			builtins/builtin_tokens.c builtins/bin_token.c \
			ascii/ascii_utils.c pipes/pipes.c \
			lists/token_list_part2.c init/magi_init.c ascii/dmysys.c \
			tokenizer/tokenizer_part5.c lists/list_functions_part2.c \
			pipes/pipes_utils.c env_export/export_part2.c \
			tokenizer/tokenizer_part6.c tokenizer/tokenizer_quote_handler.c \
			libft/ft_split.c builtins/path_check.c builtins/fork.c \
			redirections/redirections_utils.c signal_handling/ctr.c \
			builtins/exit.c signal_handling/signal_handlers.c

TEST_SRC =	./tester.c

CFILES	=	$(SRC:%.c=SRC/%.c)
OBJ		=	${SRC:%.c=%.o}
#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:* COLORS ✧*:･ﾟ✧: *✧･ﾟ:* ✧ *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

ORANGE = 	\033[1;38;5;208m
RES = 		\033[m

#✧･ﾟ: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ *✧･ﾟ:*  RULES  ✧*:･ﾟ✧: *✧･ﾟ:*  *:･ﾟ✧*:･ﾟ✧✧･ﾟ: *✧･ﾟ:#

all: $(NAME)

$(NAME): $(MAIN) $(CFILES)
	@echo "$(ORANGE)CODE: 000\nEXEC COMPILATION: "
	$(CC) $(MAIN) $(CFILES) -o $(NAME) $(FLAGS) $(READLINE_FLAG)
	@echo "$(RES)"

test: fclean $(TEST_SRC) $(CFILES)
	@echo "$(ORANGE)CODE: 501\nTEST COMPILATION: "
	$(CC) $(CFILES) $(TEST_SRC) -o test $(TEST_FLAG) $(READLINE_FLAG)
	@echo "$(RES)"

clean:
	@echo "$(ORANGE)\t    🄲 🄻 🄴 🄰 🄽 🄸 🄽 🄶 ...\n"
	rm -f ./*~ ./*# a.out test $(OBJ)
	@echo "\n\t    Cleaning Done! $(RES)"

fclean: clean
	@echo "$(ORANGE)\t    ℝ𝕖𝕞𝕠𝕧𝕚𝕟𝕘 $(NAME)...\n"
	rm -f $(NAME) .magishell_history
	@echo "\n\t    Removed $(NAME)!$(RES)"

re: fclean all
