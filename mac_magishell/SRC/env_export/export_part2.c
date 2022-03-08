/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_part2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/05 14:15:37 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

static void	export_token_print(t_list *current, t_magi *magi)
{
	printf("%s\n", current->token);
	printlist(&magi->env, 2);
}

static void	if_empty_and_doesnt_exist_in_list(t_list *current, \
	char *env_token, t_magi *magi)
{
	if (env_token != NULL && !(find_replace_exp \
		(&magi->env, env_token, current->token)))
		add_token(0, ft_strdup(current->token), &magi->env);
}

void	export_token(t_list *token, t_magi *magi, int argc)
{
	t_list	*current;
	char	*env_token;
	int		i;
	char	*temp;

	current = token;
	i = 0;
	env_token = NULL;
	temp = NULL;
	if (argc == 1)
		export_token_print(current, magi);
	else
	{
		current = token->next;
		while (current)
		{
			if (!current->token)
				break ;
			if (export_token_argc_2(current, i, &temp, &env_token) == -1)
				break ;
			if_empty_and_doesnt_exist_in_list(current, env_token, magi);
			current = current->next;
		}
	}
	free (env_token);
}
