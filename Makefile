# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llapage <llapage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 10:54:31 by llapage           #+#    #+#              #
#    Updated: 2023/10/16 14:37:19 by llapage          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

#-------------------SOURCES PATH----------------------
SOURCES     = src/
HEADER_PWD  = ./includes/
LIBFT_PWD   = ./dep/libft/

#-------------------MAX OPEN FILES--------------------
FD_MAX = -D OPEN_MAX=1024

#-------------------COMPILATION-----------------------
CC	= cc

FLAGS	= -Wall -Werror -Wextra $(FD_MAX)
#FLAGS	= -Wall -Werror -Wextra -g $(FD_MAX)
#FLAGS	= -Wall -Werror -Wextra -g -fsanitize=address $(FD_MAX)

#-------------------SOURCES FILES----------------------
HEADERS     =   $(HEADER_PWD)minishell.h

H_LIB       =   $(LIBFT_PWD)libft.h

SRCS        =	$(SOURCES)builtins/builtins.c \
				$(SOURCES)builtins/cd.c \
				$(SOURCES)builtins/cd_get_cwd.c \
				$(SOURCES)builtins/cd_remove_dir_path.c \
				$(SOURCES)builtins/cd_to_abs_path.c \
				$(SOURCES)builtins/echo.c \
				$(SOURCES)builtins/exit.c \
				$(SOURCES)builtins/exit_2.c \
				$(SOURCES)builtins/exit_utils.c \
				$(SOURCES)builtins/export.c \
				$(SOURCES)builtins/export_error.c \
				$(SOURCES)builtins/export_utils.c \
				$(SOURCES)builtins/pwd.c \
				$(SOURCES)builtins/unset.c \
				$(SOURCES)core/minishell.c \
				$(SOURCES)core/minishell_preliminary_checks.c \
				$(SOURCES)core/minishell_readline.c \
				$(SOURCES)environment/minishell_environment.c \
				$(SOURCES)environment/minishell_environment_expand_file.c \
				$(SOURCES)environment/minishell_environment_get_file_1.c \
				$(SOURCES)environment/minishell_environment_get_file_2.c \
				$(SOURCES)environment/minishell_environment_print_export.c \
				$(SOURCES)errors/minishell_errors.c \
				$(SOURCES)errors/minishell_errors_2.c \
				$(SOURCES)executor/minishell_executor.c \
				$(SOURCES)executor/minishell_executor_and_or_node.c \
				$(SOURCES)executor/minishell_executor_leaf_node.c \
				$(SOURCES)executor/minishell_executor_pipe_node.c \
				$(SOURCES)executor/minishell_executor_subshell_node.c \
				$(SOURCES)expander/minishell_expander.c \
				$(SOURCES)expander/minishell_expander_utils.c \
				$(SOURCES)expander/minishell_expander_wildcard.c \
				$(SOURCES)expander/minishell_expander_wildcard_get_arr.c \
				$(SOURCES)expander/minishell_expander_wildcard_match.c \
				$(SOURCES)file/minishell_file.c \
				$(SOURCES)finalizer/minishell_finalizer.c \
				$(SOURCES)finalizer/minishell_finalizer_set_various.c \
				$(SOURCES)history/minishell_history.c \
				$(SOURCES)interpreter/minishell_interpreter.c \
				$(SOURCES)interpreter/minishell_interpreter_end_subshell.c \
				$(SOURCES)interpreter/minishell_interpreter_link_nodes.c \
				$(SOURCES)interpreter/minishell_interpreter_operator.c \
				$(SOURCES)launcher/minishell_launcher.c \
				$(SOURCES)launcher/minishell_launcher_get_path.c \
				$(SOURCES)launcher/minishell_launcher_split_args.c \
				$(SOURCES)launcher/minishell_launcher_utils.c \
				$(SOURCES)lexer/minishell_lexer.c \
				$(SOURCES)lexer/minishell_lexer_argument.c \
				$(SOURCES)lexer/minishell_lexer_command.c \
				$(SOURCES)lexer/minishell_lexer_fail.c \
				$(SOURCES)lexer/minishell_lexer_heredoc.c \
				$(SOURCES)lexer/minishell_lexer_input_redirection.c \
				$(SOURCES)lexer/minishell_lexer_logical_and.c \
				$(SOURCES)lexer/minishell_lexer_new_argument.c \
				$(SOURCES)lexer/minishell_lexer_new_sequence.c \
				$(SOURCES)lexer/minishell_lexer_output_redirection.c \
				$(SOURCES)lexer/minishell_lexer_output_append.c \
				$(SOURCES)lexer/minishell_lexer_pipe.c \
				$(SOURCES)lexer/minishell_lexer_token_add.c \
				$(SOURCES)lexer/minishell_lexer_verify_syntax.c \
				$(SOURCES)lexer/minishell_lexer_verify_syntax_2.c \
				$(SOURCES)memory/minishell_memory_1.c \
				$(SOURCES)memory/minishell_memory_2.c \
				$(SOURCES)parser/minishell_parser.c \
				$(SOURCES)parser/minishell_parser_handle_token_1.c \
				$(SOURCES)parser/minishell_parser_handle_token_2.c \
				$(SOURCES)parser/minishell_parser_heredoc.c \
				$(SOURCES)parser/minishell_parser_heredoc_2.c \
				$(SOURCES)parser/minishell_parser_heredoc_expand.c \
				$(SOURCES)parser/minishell_parser_utils.c \
				$(SOURCES)pipes/minishell_pipes.c \
				$(SOURCES)redirections/minishell_redirections.c \
				$(SOURCES)redirections/minishell_redirections_open_files.c \
				$(SOURCES)redirections/minishell_redirections_pipe_infiles.c \
				$(SOURCES)redirections/minishell_redirections_pipe_outfiles.c \
				$(SOURCES)quotes/minishell_quotes.c \
				$(SOURCES)quotes/minishell_quotes_resolve_heredoc.c \
				$(SOURCES)quotes/minishell_quotes_resolve_infiles_outfiles.c \
				$(SOURCES)quotes/minishell_quotes_resolve_quotes.c \
				$(SOURCES)quotes/minishell_quotes_single_double.c \
				$(SOURCES)quotes/minishell_quotes_utils.c \
				$(SOURCES)signals/minishell_signals.c \
				$(SOURCES)structs/arg_list/minishell_arg_list.c \
				$(SOURCES)structs/arg_list/minishell_arg_list_print.c \
				$(SOURCES)structs/arg_list/minishell_arg_list_to_str_arr.c \
				$(SOURCES)structs/ast/minishell_ast.c \
				$(SOURCES)structs/ast/minishell_ast_is.c \
				$(SOURCES)structs/ast/minishell_ast_ops.c \
				$(SOURCES)structs/ast/minishell_ast_print_1.c \
				$(SOURCES)structs/ast/minishell_ast_print_2.c \
				$(SOURCES)structs/char_list/minishell_char_list_1.c \
				$(SOURCES)structs/char_list/minishell_char_list_2.c \
				$(SOURCES)structs/char_list/minishell_char_list_3.c \
				$(SOURCES)structs/char_list/minishell_char_list_4.c \
				$(SOURCES)structs/int_list/minishell_int_list_1.c \
				$(SOURCES)structs/int_list/minishell_int_list_2.c \
				$(SOURCES)structs/token/minishell_token.c \
				$(SOURCES)structs/token/minishell_token_print.c \
				$(SOURCES)utils/minishell_ditoa.c

SRC_LIBFT   =   $(LIBFT_PWD)ft_abs.c \
				$(LIBFT_PWD)ft_atoi.c \
				$(LIBFT_PWD)ft_atoll.c	\
				$(LIBFT_PWD)ft_csplit.c	\
				$(LIBFT_PWD)ft_isalnum.c \
				$(LIBFT_PWD)ft_isalpha.c \
				$(LIBFT_PWD)ft_isdigit.c \
				$(LIBFT_PWD)ft_isllong.c \
				$(LIBFT_PWD)ft_isnumeric.c \
				$(LIBFT_PWD)ft_isspace.c \
				$(LIBFT_PWD)ft_itoa.c \
				$(LIBFT_PWD)ft_memcpy.c	\
				$(LIBFT_PWD)ft_pstrdup.c \
				$(LIBFT_PWD)ft_pputchar_fd.c \
				$(LIBFT_PWD)ft_pputstr_fd.c \
				$(LIBFT_PWD)ft_putnbr_base_fd.c \
				$(LIBFT_PWD)ft_sort_strstr_tab.c \
				$(LIBFT_PWD)ft_split.c \
				$(LIBFT_PWD)ft_strcchr.c \
				$(LIBFT_PWD)ft_strchr.c \
				$(LIBFT_PWD)ft_strcasecmp.c \
				$(LIBFT_PWD)ft_strcmp.c \
				$(LIBFT_PWD)ft_strcncpy.c \
				$(LIBFT_PWD)ft_strdup.c \
				$(LIBFT_PWD)ft_strdupchr.c \
				$(LIBFT_PWD)ft_strduprchr.c \
				$(LIBFT_PWD)ft_strduprnchr.c \
				$(LIBFT_PWD)ft_strfjoin.c \
				$(LIBFT_PWD)ft_strjoin.c \
				$(LIBFT_PWD)ft_strlcpy.c \
				$(LIBFT_PWD)ft_strlen.c \
				$(LIBFT_PWD)ft_strncmp.c \
				$(LIBFT_PWD)ft_strnstr.c \
				$(LIBFT_PWD)ft_strracat.c \
				$(LIBFT_PWD)ft_strrchr.c \
				$(LIBFT_PWD)ft_strstrdup.c \
				$(LIBFT_PWD)ft_strtrim.c \
				$(LIBFT_PWD)ft_strstrlen.c \
				$(LIBFT_PWD)ft_tolower.c \
				$(LIBFT_PWD)get_next_line.c \
				$(LIBFT_PWD)skip_spaces.c

#-------------------OBJECTS----------------------
OBJS        =   $(SRCS:.c=.o)
LIBFT_OBJ	=	$(SRC_LIBFT:.c=.o)
#B_OBJS		=	$(SRC_BONUS:.c=.o)

#-------------------HEADERS----------------------
I_HEADER    =   $(addprefix( -include, $(HEADERS)))
I_H_LIB     =   $(addprefix( -include, $(H_LIB)))

#-------------------COLORS-----------------------
RED         =   \x1b[31m
YELLOW      =   \x1b[33m
GREEN       =   \x1b[32m
NO_COLOR    =   \x1b[0m
BOLD        =   \x1b[1m
BOLD_OFF    =   \x1b[21m

#-------------------RULES-----------------------
%.o: %.c
			@printf "$(YELLOW)Generating $(NAME) objects... %-33.33s\r$(NO_COLOR)" $@
			@$(CC) $(FLAGS) -Iincludes $(I_H_LIB) -c $< -o $@ -I ~/homebrew/opt/readline/include \
										-I /usr/local/opt/readline/include
$(NAME):    $(LIBFT_OBJ) $(OBJS)
			@make -sC ./dep/libft/
			@printf "$(GREEN)Compiling $(NAME)... %33s\r$(NO_COLOR)" " "
			@$(CC) $(FLAGS) $(OBJS) $(LIBFT_OBJ) -o $(NAME) -lreadline -L ~/homebrew/opt/readline/lib
			@echo "\n$(GREEN)$(BOLD)$@ done !$(BOLD_OFF)$(NO_COLOR)"

bonus:	$(NAME)

macos : $(LIBFT_OBJ) $(OBJS)
			@make -sC ./dep/libft/
			@printf "$(GREEN)Compiling $(NAME)... %33s\r$(NO_COLOR)" " "
			@$(CC) $(FLAGS) $(OBJS) $(LIBFT_OBJ) -o $(NAME) -lreadline -L /usr/local/opt/readline/lib
			@echo "\n$(GREEN)$(BOLD)minishell done !$(BOLD_OFF)$(NO_COLOR)"

linux : $(LIBFT_OBJ) $(OBJS)
			@make -sC ./dep/libft/
			@printf "$(GREEN)Compiling $(NAME)... %33s\r$(NO_COLOR)" " "
			@$(CC) $(FLAGS) $(OBJS) $(LIBFT_OBJ) -lreadline -o $(NAME)
			@echo "\n$(GREEN)$(BOLD)minishell done !$(BOLD_OFF)$(NO_COLOR)"

all:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...$(NO_COLOR)"
		@rm -rf $(OBJS)
		@rm -rf $(B_OBJS)
		@make clean -sC ./dep/libft/
fclean:	clean
		@echo "$(RED)Deleting executables...$(NO_COLOR)"
		@make fclean -sC ./dep/libft/
		@rm -f $(NAME)
		@rm -f $(CHECKER)
re:	fclean all

remacos: fclean macos

relinux: fclean linux

.PHONY: all clean fclean bonus re
