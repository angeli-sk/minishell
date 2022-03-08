/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_part4.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/05 15:51:30 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static int	special_chr_counter(int *counter, char **line, int x, char c)
{
	if (((*line)[x] == '>' && c == '>') ||
		((*line)[x] == '<' && c == '<') ||
		((*line)[x] == '|' && c == '|'))
		(*counter)++;
	else
		return (-1);
	return (0);
}

int	error_redirct_check(char **line, int pos)
{
	if ((*line)[pos] == '>' && (*line)[pos + 1] == '<')
		return (ERROR);
	if ((*line)[pos] == '<' && (*line)[pos + 1] == '>')
		return (ERROR);
	if (((*line)[pos] == '<' || (*line)[pos] == '>') && (*line)[pos + 1] == '|')
		return (ERROR);
	if ((*line)[pos] == '|' && ((*line)[pos + 1] == '<' || \
		(*line)[pos + 1] == '>'))
		return (ERROR);
	if ((*line)[pos] == '|' && (*line)[pos + 1] == '|')
		return (ERROR);
	return (0);
}

static int	pip_red_counter_err(char ret[2], char c)
{
	ret[0] = c;
	ret[1] = '\0';
	error_msg(SYNTAX_ERR, ret);
	return (ERROR);
}

int	extra_pipe_or_redirect_err_check(char **line, int *i, t_magi *magi)
{
	int		x;
	int		pos;
	char	c;
	char	ret[2];
	int		counter;

	x = *i;
	pos = *i;
	c = (*line)[*i];
	counter = 0;
	while ((*line)[x])
	{
		if (special_chr_counter(&counter, line, x, c) == -1)
			break ;
		x++;
	}
	if ((c == '|' && counter >= 2) || (c == '>' && counter >= 3) || \
		(c == '<' && counter >= 3) || error_redirct_check(line, pos) == ERROR)
		return (pip_red_counter_err(ret, c));
	if (counter >= 3)
		(*i)++;
	magi->redirect = 1;
	return (0);
}

void	exit_status_replacer(t_magi *magi, char **line, int env_pos)
{
	int		i;
	int		len;
	char	*ascii_num;

	i = env_pos;
	len = 0;
	ascii_num = ft_itoa(magi->exit_status);
	len = ft_strlen(*line);
	while (i < len)
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			remove_chr(&(*line), i);
			remove_chr(&(*line), i);
			insert_str(&(*line), i, ascii_num);
			if (i == '\0')
				break ;
		}
		i++;
	}
	free (ascii_num);
}
