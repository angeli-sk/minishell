/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 12:56:47 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/23 16:36:47 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
/* #include </Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/
include/editline/readline.h>*/

static void	write_errs_p1(int nr, char *extra_arg, int len)
{
	if (nr == CD_ERR)
		write(1, "evashell: cd: too many arguments\n", 34);
	if (nr == CD_ERR1)
	{
		write(1, "evashell: ", 10);
		write(1, "cd: ", 4);
		write(1, extra_arg, len);
		write(1, ": No such file or directory\n", 28);
	}
	if (nr == ENV_ERR)
	{
		write(1, "evashell: ", 10);
		write(1, "env: ", 4);
		write(1, extra_arg, len);
		write(1, " : No such file or directory\n", 29);
	}
}

static void	write_errs_p2(int nr, char *extra_arg, int len)
{
	if (nr == CD_ERR2)
	{
		write(1, "evashell: ", 10);
		write(1, "cd: ", 4);
		write(1, extra_arg, len);
		write(1, ": No such file or directory\n", 28);
	}
	if (nr == LS_ERR)
	{
		write(1, "evashell: ", 10);
		write(1, extra_arg, len);
		write(1, ": No such file or directory\n", 28);
	}
	if (nr == TOKEN_ERR)
		write(1, "evashell: MULTILINE UNAVAILABLE\n", 33);
}

static	void	write_errs_p3(int nr, char *extra_arg, int len)
{
	if (nr == EXP_ERR)
	{
		write(1, "evashell: ", 10);
		write(1, "export: ", 8);
		write(1, extra_arg, len);
		write(1, ": not a valid identifier\n", 25);
	}
	if (nr == SYNTAX_ERR)
	{
		write(1, "evashell: ", 10);
		write(1, "syntax error near unexpected token `", 36);
		write(1, extra_arg, len);
		write(1, "'\n", 3);
	}
	if (nr == NUM_ERR)
	{
		write(1, "evashell: exit: ", 16);
		write(1, extra_arg, len);
		write(1, ": numeric argument required\n", 29);
	}
}

static	void	write_errs_p4(int nr, char *extra_arg, int len)
{
	if (nr == CMD_ERROR)
	{
		write(1, "evashell: ", 10);
		write(1, extra_arg, len);
		write(1, ": command not found\n", 21);
	}
	if (nr == EVA_ERROR)
		write(1, "evashell: invalid syntax for changemod\n", 40);
	if (nr == ENV_ERR2)
		write(1, "evashell: bad assignment\n", 26);
	if (nr == EXIT_ERR)
		write(1, "evashell: exit: too many arguments\n", 36);
	if (nr == MALLOC_FAIL)
		write(1, "Malloc failed lemao, how did u do it?\n", 38);
	if (nr == FORK_FAIL)
		write(1, "Fork failed? Wot? Confused...\n", 30);
}

void	error_msg(int nr, char *extra_arg)
{
	int	len;

	if (extra_arg != NULL)
		len = ft_strlen(extra_arg);
	else
		len = 0;
	write_errs_p1(nr, extra_arg, len);
	write_errs_p2(nr, extra_arg, len);
	write_errs_p3(nr, extra_arg, len);
	write_errs_p4(nr, extra_arg, len);
	printf("\033[38;5;196m▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n\
▒                        ,,###=,                    ▒\n\
▒ 𝐒𝐄𝐂𝐔𝐑𝐈𝐓𝐘 𝐋𝐄𝐕𝐄𝐋:𝐄𝐄𝐄    𝐍𝐄###=   𝐒𝐄𝐂𝐔𝐑𝐈𝐓𝐘:𝐂𝐇𝐄𝐂𝐊     ▒\n\
▒ PERSONAL CODE: - - -   𝐑𝐕##=   NAME: - - - -      ▒\n\
▒  ____________________  ---''  _________________   ▒\n\
▒    -------------------------------------------    ▒\n\
▒    |                ＥＲＲＯＲ               |    ▒\n\
▒    -------------------------------------------    ▒\n\
▒                 𝐅𝐈𝐍𝐀𝐋 𝐆𝐀𝐓𝐄/𝐋𝐎𝐂𝐊𝐄𝐃                 ▒\n\
▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n\
\033[37m");
	rl_on_new_line();
	rl_replace_line("", 0);
}
