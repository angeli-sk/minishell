/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:48:24 by akramp        #+#    #+#                 */
/*   Updated: 2022/02/11 16:10:59 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static int	pipe_token_counter(t_list *head)
{
	t_list	*current;
	int		count;

	count = 0;
	current = head;
	while (current)
	{
		if (current->type == PIPE)
			break ;
		current = current->next;
		count++;
	}
	return (count);
}

static int	pipe_token_check(t_magi *magi)
{
	t_list	*current;

	current = magi->head;
	while (current)
	{
		if (current->type == PIPE)
		{
			current = current->next;
			if (check_token(current->token, \
				pipe_token_counter(current), magi) != 0)
				return (1);
			while (current && current->type != PIPE)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (0);
}

static int	double_pipe_check(t_magi *magi)
{
	t_list	*current;
	int		temp;

	current = magi->head;
	temp = current->type;
	current = current->next;
	while (current)
	{
		if (temp == PIPE && current->type == PIPE)
		{
			error_msg(SYNTAX_ERR, current->token);
			return (1);
		}
		temp = current->type;
		current = current->next;
	}
	return (0);
}

int	parser(t_magi *magi)
{
	if (double_pipe_check(magi) != 0
		|| pipe_token_check(magi) != 0)
		return (1);
	return (0);
}
