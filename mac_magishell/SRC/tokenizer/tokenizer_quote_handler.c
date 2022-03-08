/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_quote_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 13:48:11 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static void	single_double_quote_check(t_magi *magi, char **line, \
	int start_pos, int *pos)
{
	if (magi->single_quote == SINGLE_QUOTE_FOUND)
		single_quote_handler(line, start_pos, pos, magi);
	else
		double_quote_env_handler(line, start_pos, magi, pos);
}

static void	if_empty_single_qoute(int *i, char **line, int start_pos, \
	t_magi *magi)
{
	*i = chrfinder((*line), '\'', start_pos);
	if ((*i) < ft_strlen(*line) && (*i) > 1 && (*line)[*i + 1] == ' ' && \
		(*line)[*i - 2] == ' ' && (*line)[*i] == '\'' && \
		(*line)[*i - 1] == '\'')
		add_token_x(6, ft_strdup(""), magi);
}

static void	if_empty_double_quote(int *i, char **line, int start_pos, \
	t_magi *magi)
{
	*i = chrfinder((*line), '"', start_pos);
	if ((*i) < ft_strlen(*line) && (*i) > 1 && (*line)[*i + 1] == ' ' && \
		(*line)[*i - 2] == ' ' && (*line)[*i] == '"' && \
		(*line)[*i - 1] == '"')
		add_token_x(6, ft_strdup(""), magi);
}

int	quote_handler(int *i, t_magi *magi, char **line, int *pos)
{
	int	start_pos;

	(*i)++;
	start_pos = *i;
	if (magi->double_quote == DOUBLE_QUOTE_FOUND || \
		magi->single_quote == SINGLE_QUOTE_FOUND)
		magi->quotes = 1;
	if (magi->double_quote == DOUBLE_QUOTE_FOUND && \
		(*i) + 1 != ft_strlen((*line)))
		if_empty_double_quote(i, line, start_pos, magi);
	else if (magi->single_quote == SINGLE_QUOTE_FOUND && \
		(*i) + 1 != ft_strlen((*line)))
		if_empty_single_qoute(i, line, start_pos, magi);
	if (*i == ft_strlen(*line))
	{
		magi->exit_status = 1;
		magi->multi_line = 1;
		error_msg(TOKEN_ERR, NULL);
		return (ERROR);
	}
	*pos = *i;
	single_double_quote_check(magi, line, start_pos, pos);
	return (0);
}
