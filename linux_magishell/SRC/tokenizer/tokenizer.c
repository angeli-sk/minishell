/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 18:52:00 by akramp        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"
#include <stdlib.h>

/*
	first_split_pos = fsp
	SINGLE_QUOTE_FOUND = SQ
	DOUBLE_QUOTE_FOUND = DQ
*/

static	int	token_splitter_checks_per_chr(char **line, \
	int *pos, t_magi *magi, int *fsp)
{
	int	i;

	i = *pos;
	if (flag_check((*line)[i], magi) == SPLIT_TOKEN \
		&& magi->single_quote != SQ && magi->double_quote != DQ)
	{
		if (check_for_pip_or_red(line, &i, magi, fsp) == ERROR)
			return (ERROR);
		if ((*line)[i] == '>' || (*line)[i] == '<')
		{
			*fsp = (*fsp) + (*pos - *fsp) + 1;
			double_red_token_add(line, magi, pos, i);
			move_pos_after_red(fsp, line, pos);
			return (0);
		}
		else
		{
			move_pos_if_no_red(magi, fsp, line, pos);
			add_token_x(2, ft_substr((*line), i, 1), magi);
			return (0);
		}
		i++;
	}
	reset_quote_vars(magi, &i);
	return (quote_handler(&i, magi, line, pos));
}

static	int	token_splitter_add_token(char **line, int i, \
int first_split_pos, t_magi *magi)
{
	int	len;

	len = ft_strlen(*line);
	while (i < ft_strlen((*line)) && (*line)[i] \
		&& (*line)[i] != ' ' && (*line)[i] != '\t')
		i++;
	if ((i - first_split_pos) <= 0)
	{
		magi->quotes = 0;
		return (i);
	}
	if (first_split_pos <= len)
		add_token_x(4, ft_substr((*line), first_split_pos, \
		i - first_split_pos), magi);
	magi->quotes = 0;
	return (i);
}

static	int	token_splitter(char **line, int i, t_magi *magi)
{
	int	first_split_pos;
	int	ret;

	first_split_pos = i;
	ret = 0;
	while ((*line)[i])
	{
		if (((*line)[i] == ' ' || (*line)[i] == '\t')
			&& magi->single_quote != SINGLE_QUOTE_FOUND
			&& magi->double_quote != DOUBLE_QUOTE_FOUND)
			break ;
		ret = token_splitter_checks_per_chr(line, &i, magi, &first_split_pos);
		if (i >= ft_strlen(*line))
			break ;
		if (ret > 0 || ret == ERROR)
			return (ret);
		i++;
	}
	return (token_splitter_add_token(line, i, first_split_pos, magi));
}

int	tokenizer(char **line, t_magi *magi)
{
	int	i;

	i = 0;
	magi->double_quote = NO_QUOTE_FOUND;
	magi->single_quote = NO_QUOTE_FOUND;
	while ((*line)[i] && (*line)[i] != '\n')
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\t')
			i = token_splitter(line, i, magi);
		else
			i++;
		if (i == -1)
			return (-1);
		if (i > ft_strlen(*line))
			break ;
	}
	magi->exit_status = 0;
	return (countlist(&(magi->head)));
}

/*
	first_split_token	----> keeps track of where it started
	i					----> is it's current index

	It loops over every charcter in the string, once it finds a quote or
	special character it will go over all characters in between the quotes and
	store the entire quote string as one token. Else it will just store the
	token.
*/
