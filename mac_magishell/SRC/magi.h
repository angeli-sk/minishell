/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   magi.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 16:23:48 by pani_zino     #+#    #+#                 */
/*   Updated: 2022/03/08 13:02:49 by Angi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAGI_H
# define MAGI_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>

# define PURPLE "\033[1;38;5;135m"
# define GREEN "\033[1;38;5;112m"
# define ORANGE "\033[1;38;5;208m"
# define YELLOW "\033[1;38;5;214m"
# define WHITE "\033[1;97m"
# define RED "\033[1;38;5;9m"
# define BLUE "\033[1;38;5;69m"
# define DENIM "\033[1;38;5;104m"
# define MUD "\033[1;38;5;144m"
# define RES "\033[m"

typedef	void	(t_function)();
extern char		**environ;
pid_t			g_pid;

typedef struct s_lookup
{
	int			index;
	t_function	*func;
}					t_lookup;

typedef struct s_list
{
	int		type;
	char	*token;
	void	*next;
}	t_list;

typedef struct s_id_list
{
	int		type;
	char	*token;
	void	*next;
}				t_id_list;

typedef struct s_magi
{
	int			mod;
	t_list		*head;
	t_list		*env;
	t_list		*env_value;
	t_list		*out_head;
	t_list		*in_head;
	t_list		*read_input;
	t_list		*pipe_head;
	char		*old_pwd;
	char		**my_environ;
	int			single_quote;
	int			double_quote;
	int			exit_status;
	int			redirect;
	int			redir_error;
	int			echo_n;
	int			saved_stdout;
	int			saved_stdin;
	int			pipes_count;
	char		**argv_pipes;
	int			quotes;
	int			multi_line;
	int			heredoc;
	int			heredoc_fd;
}	t_magi;

typedef enum e_rror
{
	ERROR = -1,
	CD_ERR = 1,
	CD_ERR1 = 2,
	ENV_ERR = 3,
	CD_ERR2 = 4,
	LS_ERR = 5,
	TOKEN_ERR = 6,
	EXP_ERR = 7,
	LS_ERR_1 = 8,
	SYNTAX_ERR = 9,
	NUM_ERR = 10,
	CMD_ERROR = 11,
	EVA_ERROR = 12,
	ENV_ERR2 = 13,
	EXIT_ERR = 14,
	WRITE = 1,
	READ = 0,
	YES	= 1,
	NO = 0,
	ESCAPE = -2,
	MALLOC_FAIL = 15,
	FORK_FAIL = 16
}	t_error;

typedef enum e_nviron
{
	EMPTY_STRING = 0,
	REMOVE_QUOTE = -1,
	DO_NOTHING = 1,
	FOUND_ENV = 1,
	NO_ENV_FOUND = 0,
	ONE_CHAR = 1,
	SINGLE_QUOTES_FOUND = 1,
	DONE = 2
}	t_nviron;

typedef enum e_token
{
	DONT_SPLIT_TOKEN = 0,
	SPLIT_TOKEN = 1,
	NO_QUOTE_FOUND = 0,
	SINGLE_QUOTE_FOUND = 1,
	SQ = 1,
	DOUBLE_QUOTE_FOUND = 2,
	DQ = 2,
	SINGLE_QUOTE_FINISHES = 3,
	DOUBLE_QUOTE_FINISHES = 4,
	ALL_QUOTES_FOUND_AND_FINISHED = -2
}	t_oken;

typedef enum e_redir
{
	REDIR_INPUT = 1,
	REDIR_OUT = 2,
	READ_INPUT = 3,
	REDIR_OUT_APP = 4
}			t_redir;

typedef enum e_sleep
{
	LONG = 1,
	SHORT = 2
}			t_sleep;

typedef enum e_fd
{
	DUPLICATE = 1,
	RESET = 2
}			t_fd;

typedef enum e_type
{
	COMMAND = 1,
	REDIRECTION = 2,
	PIPE = 3,
	ARGUMENT = 4,
	QUOTED_ARG = 5,
	EMPTY_QUOTE = 6
}			t_type;

/* aasci.c */
void	nerv_logo(void);
void	loading_bar(void);
void	error_msg_dmy(void);
void	boot_up_dmy(t_magi	*magi);
void	boot_up(t_magi	*magi);

/* aasci_utils.c */
void	cursed_sleep(int mod);
void	clear_screen(void);
void	print_ascii(t_magi *magi);

/* bin_token.c */
void	handle_heredoc(int sig);
void	bin_token(t_list *token, t_magi *magi);
char	*check_path_list(t_list **head, char *command);

/* builtin_tokens.c */
void	env_token(t_list *token, t_magi *magi, int argc);
void	pwd_token(void);
void	cd_token(t_list *token, t_magi *magi, int argc);
void	exit_token(t_list *token, t_magi *magi, int argc);

/* builtins.c */
void	change_env_cd(char *str, char *pwd, char **new_pwd, t_list **head);
void	update_env_cd(t_list **head, char *str, char *pwd);
int		ft_mod(const char *str, const char *cmp);
int		cd(const char *path, t_magi *magi);
void	unset_token(t_list *token, t_magi	*magi, int argc);

/* builtins_redirect.c */
int		token_cmp(char *token, const char *cmd);
int		check_token(char *token, int argc, t_magi *magi);
void	checksies(t_list *token, t_magi *magi, int argc);

/* dmysys.c */
void	dmysys(char *line, t_magi *magi);

/* echo.c */
int		write_echo_pipes(char **argv);
void	echo_token(t_list *token, t_magi	*magi, int argc);

/* env_basics.c */
void	env_init(t_magi *magi);
char	*get_home_env(t_magi *magi);
void	env(t_magi *magi);
int		count_env(t_list *current);

/* env_str_edit.c */
void	quoteremover(char	**edit_line);
void	remove_quotes(t_magi *magi);
void	update_my_environ(t_magi *magi);
int		find_dollar_or_space(char *str);

/* error.c */
void	error_msg(int nr, char *extra_arg);

/* export.c */
int		find_replace_exp(t_list	**head, char *env, char *str);
int		chrfinder(const char *str, char c, int start);
int		export_token_argc_2(t_list	*current, int i, char **temp, \
	char **env_token);

/*export_part2.c*/
void	export_token(t_list *token, t_magi *magi, int argc);

/* findlist.c */
char	*findlist(t_list **head, char *str, int del, char *pwd);

/* ft_atoi.c */
int		ft_atoi(const char *str);

/* ft_itoa.c */
char	*ft_itoa(int n);

/* ft_strjoin */
char	*ft_strjoin(char const *s1, char const *s2);

/* ft_substring */
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, int len);

/* functions_ms.c */
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		len_cmp(const char *str, const char *cmp);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
char	*ft_memcpy(char *dst, const char *src, size_t n);

/* functions_ms2.c */
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
char	*ft_memcpy(char *dst, const char *src, size_t n);

/* list_functions.c */
void	printlist(t_list **head, int x);
int		countlist(t_list **head);
char	*tokenmaker(char *env_to_change, char *pwd);
void	del_elem(t_list **head, t_list *to_delete);
int		find_red_type(t_list **head);

/* list_functions_part2.c */
char	*redir_file_name(t_list **head);
int		count_pip_type(t_list **head, int ret_on_first);
void	fill_charp_with_list(t_list	*list, char **charp, char *bin_token);

/* magi_shell.c */
void	handle_fd(t_magi *magi, int mod);

/*magi_init.c*/
void	entry_plug(t_magi	*magi, char	*line);
void	init_magi(t_magi *magi);
void	magi_reset(t_magi	*magi);
void	magi_exit(char	*line);

/* parser.c */
int		parser(t_magi *magi);

/* pipe_utils.c */
int		count_pipes(t_list	*current);
int		**fd_pipe_maker(t_magi	*magi);
void	free_fd(int **fd, t_list	*current);
void	exec(t_list *token, t_magi	*magi);
t_list	*split_list(t_list *orig_head, t_list *new_head, t_magi *magi);

/* pipes.c */
void	forkie_boi(t_magi	*magi, int **fd, t_list *current, t_list *temp);
void	pipes(t_magi	*magi);

/* redirections_utils.c */
void	redir_exit_status(t_magi *magi, int *ret);
int		check_if_file_exists(const char *file, t_magi *magi);
void	read_heredoc(int herdoc_fd, char *end);
int		find_redir_type(char *redir);

/* redirections_fd_func.c */
void	read_input(char *end, t_magi *magi);
void	fd_redir_output(t_list **head);
void	fd_redir_input(t_list **head, t_magi *magi);

/* redirections_list_func.c */
void	remove_redir(t_list **head);
int		redir_fill_lists(t_list **head, t_magi *magi);

/* ctr.c */
void	ctr_handle(void);

/* signal.c */
void	signal_main(void);
void	signal_int(void);
void	signal_ing_int(void);
void	signal_heredoc(void);

/* signal_handers.c */
void	handle_heredoc(int sig);
void	handle_signal(int sig);

/* token_list.c */
void	print_list(t_list **head);
void	free_list(t_list **head);
void	reset_list(t_list **head);
void	make_head(t_list **head);
void	add_token(int type, char *token, t_list **head);

/*token_list_part2.c*/
int		type_helper(t_magi *magi, char *token);
void	add_token_x(int type, char *token, t_magi *magi);

/* tokenizer.c */
int		tokenizer(char **line, t_magi *magi);

/* tokenizer_part2.c */
void	insert_str(char **edit_line, int insert_pos, char *to_insert);
void	remove_chr(char **edit_line, int chr_pos);
void	env_replacer_loop_single_dollar(char **line, t_magi *magi, \
	int *env_pos, int *pos);
int		int_len_counter(int num);

/* tokenizer_part3.c */
int		flag_check(char c, t_magi *magi);
int		loop_through_env_list(t_magi *magi, char **line, \
	char *env, int env_pos);
void	str_from_str_replacer(char **str, char *replace_with, int str_pos, \
	int len_to_be_replaced);

/* tokenizer_part4.c */
int		error_redirct_check(char **line, int pos);
int		extra_pipe_or_redirect_err_check(char **line, int *i, t_magi *magi);
void	exit_status_replacer(t_magi *magi, char **line, int env_pos);

/* tokenizer_part5.c */
int		double_quote_env_handler(char **line, int start_pos, t_magi *magi, \
	int *pos);
void	single_quote_handler(char **line, int start_pos, int *pos, \
	t_magi *magi);

/* tokenizer_part_6.c */

void	reset_quote_vars(t_magi *magi, int *i);
void	move_pos_if_no_red(t_magi *magi, int *fsp, char **line, int *pos);
void	move_pos_after_red(int *fsp, char **line, int *pos);
void	double_red_token_add(char **line, t_magi *magi, int *pos, int i);
int		check_for_pip_or_red(char **line, int *i, t_magi *magi, int *fsp);

/* tokenizer_quote_handler.c */

int		quote_handler(int *i, t_magi *magi, char **line, int *pos);

/* ft_split.c */

char	**ft_split(char const *s, char c);

/* path_check.c */

char	*check_path_list(t_list **head, char *command);

/* fork.c*/
void	handle_signal(int sig);
void	first_pipe(t_list *token, t_magi	*magi, int **fd);
void	last_pipe(t_list *token, t_magi	*magi, int **fd);
void	inbetween_pipes(t_list *token, int **fd, int i, t_magi	*magi);
void	redirect_input_stream(t_magi *magi, char *end);
void	exec_subpros(t_magi	*magi, char **argv, int *err, int *ret);

#endif
