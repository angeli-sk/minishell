/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_str_edit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Angi <Angi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 12:55:07 by Angi          #+#    #+#                 */
/*   Updated: 2022/02/23 16:15:28 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	quoteremover(char	**edit_line)
{
	int	i;

	i = 0;
	while ((*edit_line)[i])
	{
		if ((*edit_line)[i] == '"' || (*edit_line)[i] == '\'')
			remove_chr(edit_line, i);
		else
			i++;
	}
}

void	remove_quotes(t_magi *magi)
{
	t_list	*current;

	current = magi->head;
	while (current)
	{
		if (!current->token)
			return ;
		quoteremover(&(current->token));
		current = current->next;
	}
}

static int	ret_eol_magi(int i, t_magi *magi)
{
	while (magi->my_environ[i])
	{
		if (!magi->my_environ[i])
			break ;
		i++;
	}
	return (i);
}

void	update_my_environ(t_magi *magi)
{
	int		i;
	t_list	*current;

	i = 0;
	current = magi->env;
	if (magi->my_environ == NULL)
	{
		magi->my_environ = malloc(sizeof(char *) * count_env(magi->env));
		if (magi->my_environ == NULL)
		{
			error_msg(MALLOC_FAIL, NULL);
			exit(EXIT_FAILURE);
		}
	}
	else
		i = ret_eol_magi(i, magi);
	while (current)
	{
		if (!current->token)
			return ;
		magi->my_environ[i] = ft_strdup(current->token);
		i++;
		current = current->next;
	}
}

int	find_dollar_or_space(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '"' || str[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}
