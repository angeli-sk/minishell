/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_part6.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 13:47:27 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	reset_quote_vars(t_magi *magi, int *i)
{
	if ((magi->single_quote != SQ && magi->double_quote != DQ))
	{
		magi->quotes = 0;
		(*i)--;
	}
}

void	move_pos_if_no_red(t_magi *magi, int *fsp, char **line, int *pos)
{
	magi->quotes = 0;
	*fsp = *fsp + (*pos - *fsp) + 1;
	if ((*line)[*fsp] == ' ')
		(*fsp)++;
	(*pos) = (*pos) + 2;
}

void	move_pos_after_red(int *fsp, char **line, int *pos)
{
	if ((*line)[*fsp] == '>' || (*line)[*fsp] == '<')
		(*fsp)++;
	if ((*line)[*fsp] == ' ')
		(*fsp)++;
	if ((*line)[*fsp] == '\"' || (*line)[*fsp] == '\'')
		(*pos)--;
}

void	double_red_token_add(char **line, t_magi *magi, int *pos, int i)
{
	if (((*line)[i] == '>' && (*line)[i + 1] == '>' ) || \
		((*line)[i] == '<' && (*line)[i + 1] == '<' ))
	{
		add_token_x(2, ft_substr((*line), i, 2), magi);
		(*pos) = (*pos) + 2;
	}
	else
	{
		add_token_x(1, ft_substr((*line), i, 1), magi);
		(*pos) = (*pos) + 1;
	}
}

int	check_for_pip_or_red(char **line, int *i, t_magi *magi, int *fsp)
{
	magi->quotes = 0;
	if (extra_pipe_or_redirect_err_check(line, i, magi) == ERROR)
		return (ERROR);
	if ((*fsp) != (*i))
		add_token_x(2, ft_substr((*line), *fsp, (*i) - (*fsp)), magi);
	return (0);
}
