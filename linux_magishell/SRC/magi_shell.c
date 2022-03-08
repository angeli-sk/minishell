/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   magi_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 13:57:25 by akramp        #+#    #+#                 */
/*   Updated: 2022/03/08 12:43:09 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "magi.h"
#include "./GNL/get_next_line.h"

const char	*g_mod_table[4] = {
	"\033[1;38;5;69mevashell\033[1;97m00\033[1;38;5;144m$\033[m ", \
	"\033[1;38;5;135mevashell\033[1;38;5;112m01\033[1;38;5;208m$\033[m ", \
	"\033[1;38;5;9mevashell\033[1;38;5;214m02\033[1;38;5;104m$\033[m ", \
	"\033[1;38;5;160md̸͔̙͕̲̫̥͇̅̉m̷͖̙̼̫̘̞͍͖̳̪̄̓̓͋̈́̉̌y̵̻̟̠̦̔ş̴̜̦̱̪̠̳̩͓̼̍́̒̉̀̽́͘͝y̷̠̭̝̪̦̺̭͖̻͇̐͒̋̈́̒͠s̸̨̢̰̺̘̞͕̦̮̯͌͒̅͆̎͐̀͗͝͝\
	\b\b\b\033[1;38;5;46m$\033[m"};

void	handle_fd(t_magi *magi, int mod)
{
	if (mod == DUPLICATE)
	{
		magi->saved_stdout = dup(STDOUT_FILENO);
		magi->saved_stdin = dup(STDIN_FILENO);
	}
	if (mod == RESET)
	{
		dup2(magi->saved_stdout, STDOUT_FILENO);
		dup2(magi->saved_stdin, STDIN_FILENO);
		close(magi->saved_stdout);
		close(magi->saved_stdin);
	}
}

void	magi_do(t_magi *magi, int argc)
{
	if (count_pip_type(&magi->head, NO) > 0)
		pipes(magi);
	else if (magi->redirect != 1 && argc != -1)
		checksies(magi->head, magi, argc);
	else if (redir_fill_lists(&magi->head, magi) == 0 && argc != -1)
	{
		handle_fd(magi, DUPLICATE);
		remove_redir(&magi->head);
		fd_redir_output(&magi->out_head);
		fd_redir_input(&magi->in_head, magi);
		if (magi->head && check_token(magi->head->token,
				countlist(&(magi->head)), magi) == 0)
			checksies(magi->head, magi, countlist(&(magi->head)));
		handle_fd(magi, RESET);
	}
}

void	read_loop(t_magi	*m)
{
	char	*line;
	int		argc;

	while (true)
	{
		line = readline(g_mod_table[m->mod]);
		if (m->mod == 3)
			dmysys(line, m);
		else
		{
			magi_exit(line);
			add_history(line);
			argc = tokenizer(&line, m);
			if (m->head->token != NULL)
			{
				if (check_token(m->head->token, argc, m) == 0 && parser(m) == 0)
					magi_do(m, argc);
				else
					m->exit_status = 127;
			}
			magi_reset(m);
			free(line);
		}
	}
}

int	main(void)
{
	t_magi	magi;

	init_magi(&magi);
	ctr_handle();
	signal_main();
	print_ascii(&magi);
	read_loop(&magi);
	return (0);
}

/*
	line 97 ---> print_ascii(&magi);
				clear_screen();
	line 78 ---> print_list(&magi->head);
*/
