/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_part5.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 15:37:15 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static int	loop_and_replace_check(char **line, t_magi *magi, int env_pos, \
	char	*env)
{
	if (loop_through_env_list(magi, line, env, env_pos) == -1)
		str_from_str_replacer(line, "", env_pos, ft_strlen(env));
	if (env_pos < ft_strlen(*line) && ((*line)[env_pos + 1] == '=' \
		|| (*line)[env_pos + 1] == '?'))
	{
		exit_status_replacer(magi, line, env_pos);
		free (env);
		return (-1);
	}
	free (env);
	return (0);
}

static void	env_replacer_loop(char **line, int start_pos, t_magi *magi, \
	int *pos)
{
	int		env_pos;
	int		find_d_s;
	char	*env;

	env = NULL;
	env_pos = chrfinder((*line), '$', start_pos);
	while (env_pos != ft_strlen(*line) && env_pos < chrfinder((*line), '"', \
		start_pos) && env_pos < chrfinder((*line), '\'', start_pos))
	{
		find_d_s = find_dollar_or_space(&(*line)[env_pos]);
		if (find_d_s == 1)
			env_replacer_loop_single_dollar(line, magi, &env_pos, pos);
		else
		{
			env = ft_substr((*line), env_pos, find_d_s);
			if (loop_and_replace_check(line, magi, env_pos, env) == -1)
				break ;
		}
		env_pos = chrfinder((*line), '$', env_pos);
	}
}

static void	env_replacer_quote_pos_check(char **line, int *start_pos)
{
	if ((*line)[(*start_pos) - 1] == '"')
	{
		remove_chr(line, (*start_pos) - 1);
		(*start_pos)--;
	}
	else if ((*line)[(*start_pos)] == '"')
	{
		remove_chr(line, (*start_pos));
		(*start_pos)--;
	}
}

int	double_quote_env_handler(char **line, int start_pos, t_magi *magi, int *pos)
{
	env_replacer_loop(line, start_pos, magi, pos);
	if (magi->double_quote == DOUBLE_QUOTE_FOUND)
	{
		env_replacer_quote_pos_check(line, &start_pos);
		*pos = chrfinder((*line), '"', start_pos);
		magi->double_quote = NO_QUOTE_FOUND;
		if ((*line)[*pos] == '"'
			|| ((*line)[(*pos) - 1] == '"' && (*line)[(*pos)] == '\0'))
		{
			remove_chr(line, *pos);
			(*pos)--;
		}
	}
	return (0);
}

void	single_quote_handler(char **line, int start_pos, int *pos, t_magi *magi)
{
	if ((*line)[start_pos - 1] == '\'')
	{
		remove_chr(line, start_pos - 1);
		(*pos)--;
	}
	magi->single_quote = NO_QUOTE_FOUND;
	*pos = chrfinder((*line), '\'', start_pos - 1);
	if ((*line)[*pos] == '\''
		|| ((*line)[(*pos) - 1] == '\'' && (*line)[(*pos)] == '\0'))
	{
		remove_chr(line, *pos);
		(*pos)--;
	}
}
