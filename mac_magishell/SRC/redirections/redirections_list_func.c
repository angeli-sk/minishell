/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_list_func.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elisabeth <elisabeth@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 14:11:32 by elisabeth     #+#    #+#                 */
/*   Updated: 2022/02/23 20:28:19 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static void	add_redir_token(int type, t_magi *magi, t_list *current)
{
	if (type == REDIR_OUT_APP || type == REDIR_OUT)
		add_token(type, ft_strdup(current->token), &magi->out_head);
	if (type == REDIR_INPUT || type == READ_INPUT)
		add_token(type, ft_strdup(current->token), &magi->in_head);
}

void	remove_redir(t_list **head)
{
	t_list	*current;

	current = *head;
	while (current)
	{
		if (current->type == 2)
		{
			del_elem(head, current->next);
			del_elem(head, current);
			if (!(*head) || !(*head)->next)
				return ;
			current = (*head)->next;
		}
		else
			current = current->next;
	}
}

int	redir_fill_lists(t_list **head, t_magi *magi)
{
	t_list	*current;
	int		type;

	current = *head;
	while (current)
	{
		if (current->token[0] == '<' || current->token[0] == '>')
		{
			type = find_redir_type(current->token);
			current = current->next;
			if (!current)
			{
				error_msg(SYNTAX_ERR, "newline");
				return (1);
			}
			if (type == REDIR_INPUT
				&& check_if_file_exists(current->token, magi) == 1)
				return (1);
			if (type == READ_INPUT)
				redirect_input_stream(magi, current->token);
			add_redir_token(type, magi, current);
		}
		current = current->next;
	}
	return (0);
}
