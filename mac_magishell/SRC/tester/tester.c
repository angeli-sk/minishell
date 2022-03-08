#include <string.h>
#include <stdio.h>
#include "/Users/akramp/.brew/Cellar/criterion/2.3.3/include/criterion/criterion.h"
#include "./SRC/magi.h"
#include <stdlib.h>
#include <string.h>

void	init_magi(t_magi *magi)
{
	magi->mod = 1;
	magi->head = NULL;
	magi->my_environ = NULL;
	magi->out_head = NULL;
	magi->in_head = NULL;
	magi->pipe_head = NULL;
	magi->single_quote = 0;
	magi->double_quote = 0;
	magi->exit_status = 0;
	magi->redirect = 0;
	magi->redir_error = 0;
	magi->echo_n = 0;
	magi->saved_stdout = 0;
	magi->saved_stdin = 0;
	magi->argv_pipes = NULL;
	magi->quotes = 0;
	magi->multi_line = 0;
	magi->heredoc = 0;
	make_head(&magi->head);
	make_head(&magi->env);
	make_head(&magi->env_value);
	make_head(&magi->read_input);
	make_head(&magi->out_head);
	make_head(&magi->in_head);
}

void	delete_list(t_list **head)
{
	t_list	*temp;
	t_list	*current;

	current = *head;
	while (current)
	{
		temp = current->next;
		free(current->token);
		free(current);
		current = temp;
	}
	*head = NULL;
	make_head(head);
}

void	entry_plug(t_magi	*magi, char	*line)
{
	const char	*mod[4] = {"eva-00", "eva-01", "eva-02", "dmysys"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (token_cmp(line, mod[i]) == 0)
		{
			magi->mod = i;
			break ;
		}
		i++;
	}
	// if (magi->mod == 3)
	// 	boot_up_dmy(magi);
	// else
	// 	boot_up(magi);
}

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

void	warning_line()
{
	printf(\
	"\033[1;38;5;85m▒\033[1;38;5;85m▒\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\
	\b\b\b\b\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;196m ⚠ \033[1;38;5;85m▒\
	\b\b\b\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[1;38;5;85m▒\
	\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;85m\n");
}

void	test_boot_up()
{
	warning_line();
	printf("\033[1;38;5;208mＣＯＤＥ： ５０１\n\033[1;38;5;166m\
	FILE: MAGI_TEST\n\tEXTENTION:2021\n\
	ML_MODE: OFF\n\tPRIORITY:BBB\n\n\t𝐈𝐍𝐈𝐓𝐈𝐀𝐋𝐈𝐙𝐄 𝐓𝐄𝐒𝐓𝐒\n");

}

char *join(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1);

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }
    return (result);
}

void	tester_tokenizer(char *my_input, char *shell_output, t_magi *magi)
{
	t_list	*current;
	char	*my_str;
	char	*temp;
	char 	*my_i;

	make_head(&magi->head);
	current = magi->head;
	my_str = ft_strdup("");
	my_i = NULL;
	my_i = strdup(my_input);
	printf("%s\n", my_i);
	tokenizer(&my_i, magi);
	print_list(&magi->head);
	while (current)
	{
		if (!current->token)
			break ;
		temp = join(my_str, current->token);
		free (my_str);
		my_str = temp;
		if (current->next != NULL)
			my_str = join(my_str, " ");
		current = current->next;
	}
	printf("\033[38;5;208mmystr[%s]\n", my_str);//81
	printf("\033[38;5;166mshell[%s]\n", shell_output);//177
	cr_assert_str_eq(my_str, shell_output);
	delete_list(&magi->head);
	free (my_i);
}

Test(echo, parser)
{
	t_magi	*magi;

	test_boot_up();
	init_magi(magi);
	env_init(magi);

	tester_tokenizer("\"h\"''\"\"\"'\"e\" \"ll\"o'\"", "h'e llo'", magi);
	tester_tokenizer("$HOME$HOME$USERlol$PAGER\"$ZSH\"'$LANG'", \
		"/Users/akramp/Users/akrampless/Users/akramp/.oh-my-zsh$LANG", magi);
	tester_tokenizer("\"$HOMElol$HOME\"'$HOMEkedikfjek'fskhfkjd$HOME\"$USER\"", \
	 "/Users/akramp$HOMEkedikfjekfskhfkjd/Users/akrampakramp", magi);
	tester_tokenizer("$HOME'$HOME'\"$HOME\"$HOME", "/Users/akramp$HOME/Users/akramp/Users/akramp", magi);
	tester_tokenizer("$HOME'$USER'\"$HOME\"$ZSH", \
	"/Users/akramp$USER/Users/akramp/Users/akramp/.oh-my-zsh", magi);
	tester_tokenizer("lemao$HOME'$USERlolol'hjhsdjhj$ZSH $HOME \"$HOME $HOME $HOME\"", \
	"lemao/Users/akramp$USERlololhjhsdjhj/Users/akramp/.oh-my-zsh /Users/akramp /Users/akramp /Users/akramp /Users/akramp", magi);
	tester_tokenizer("\"$HOME $HOME $HOME\"", "/Users/akramp /Users/akramp /Users/akramp", magi);
	// tester_tokenizer("\"\" \"$HOME\"\"$USERlol$ZSH\"lolol $USER $loljdj$HOME", \
	// " /Users/akramp/Users/akramp/.oh-my-zshlolol akramp /Users/akramp", magi);
	tester_tokenizer("$\"$HOME $ $ $HOME $\"$", "/Users/akramp $ $ /Users/akramp $$", magi);
	tester_tokenizer("a\"$HOME $HOME\"b", "a/Users/akramp /Users/akrampb", magi);
	tester_tokenizer("\"'\"", "'", magi);
	tester_tokenizer("$\"lol\" $\"lemao\" $'EEE'$", "lol lemao EEE$", magi);
	tester_tokenizer("'\"'", "\"", magi);
	tester_tokenizer("$", "$", magi);
	tester_tokenizer("", "", magi);
	tester_tokenizer("lemao lol \"lemao lol $skkkrt $HOME\"\'$\'\'$LEMAO\'\'$HOME\'lollemao$HOME",
		"lemao lol lemao lol  /Users/akramp$$LEMAO$HOMElollemao/Users/akramp", magi);
	tester_tokenizer("ho", "ho", magi);
	tester_tokenizer("a", "a", magi);
	tester_tokenizer("a'a'\"a\"'a'a", "aaaaa", magi);
	tester_tokenizer("\"\"''\"'''\"", "'''", magi);
	tester_tokenizer("    ", "", magi);
	tester_tokenizer("\"   \"", "   ", magi);
	tester_tokenizer("hallo doei bitch lemao get wrecked", "hallo doei bitch lemao get wrecked", magi);
	tester_tokenizer("\"$ $\"", "$ $", magi);
	tester_tokenizer("$ $", "$ $", magi);
	tester_tokenizer("$ $   $", "$ $ $", magi);
	tester_tokenizer("$\"$\"'$'$", "$$$", magi);
	tester_tokenizer("uwu", "uwu", magi);
	tester_tokenizer("$?", "0", magi);
	tester_tokenizer("'a     b'", "a     b", magi);
	tester_tokenizer("'     b'", "     b", magi);
	tester_tokenizer("'     '", "     ", magi);

	tester_tokenizer("\'\'\'\'      ", "", magi);
	// tester_tokenizer("\'  \' \'  \' \' \' \'\'", "        ", magi);
	// tester_tokenizer("abc    \'\'", "abc ", magi);
	// tester_tokenizer("\'       \'    \'  \' \' \' \'\'", "             ", magi);
	// tester_tokenizer("\'       \'    \'  \' \' \' \'\' ", "             ", magi);
	// tester_tokenizer("\'  \' \'  \' \' \' \'\' ", "        ", magi);
	// tester_tokenizer("\" \"\"\"", " ", magi);
	// tester_tokenizer("abc    \"\"", "abc ", magi);
	// tester_tokenizer("'  ' '  ' ' ' '' \"\"", "         ", magi);
	// tester_tokenizer("'  ' '  ' ' ' '' \" \"", "          ", magi);
	// tester_tokenizer("'  ' '  ' ' ' '' \" \"\"\"", "          ", magi);
	// tester_tokenizer("\"   \"\"\"", "   ", magi);
	// tester_tokenizer("\"  \"\"\"", "  ", magi);
	// tester_tokenizer("\" \"\"\"", " ", magi);
	// tester_tokenizer("\"  \"\"\"", "  ", magi);
	// tester_tokenizer("\"\"\"\"", "", magi);
	// tester_tokenizer("\"\"\"\"\"\"", "", magi);
	// tester_tokenizer("\"\"\"\"\" \" \"\"", "  ", magi);

	tester_tokenizer("hello world!", "hello world!", magi);
	tester_tokenizer("\"      \"", "      ", magi);
	// tester_tokenizer("\"\"'' '' ' ' \" \"''", "     ", magi);
	// tester_tokenizer("\"\"'' '' ' ' ' '\"\"", "     ", magi);
	// tester_tokenizer("echo \"\" \"lol\" \"\" \"\" \"\" \"lol\"", " lol    lol", magi);
	// tester_tokenizer("\"\"'' ''sdfddfdsfsd' ' ' '\"\"", " sdfddfdsfsd   ", magi);
	tester_tokenizer("$USER\"$HOME\"'' '$HOME'sdfddfdsfsd' ' ' '\"\"sfd", "akramp/Users/akramp $HOMEsdfddfdsfsd   sfd", magi);
	warning_line();
}

// Test(export_unset, export)
// {
// 	t_magi	*magi;

// 	test_boot_up();
// 	test_init(magi);
// 	env_init(magi);


// }
