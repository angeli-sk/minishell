/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   magi_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 15:03:21 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/02/23 20:17:03 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

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
	if (magi->mod == 3)
		boot_up_dmy(magi);
	else
		boot_up(magi);
}

static void	init_magi_make_head(t_magi *magi)
{
	make_head(&magi->head);
	make_head(&magi->env);
	make_head(&magi->env_value);
	make_head(&magi->read_input);
	make_head(&magi->out_head);
	make_head(&magi->in_head);
}

void	init_magi(t_magi *magi)
{
	ft_bzero(magi, sizeof(*magi));
	magi->mod = 1;
	init_magi_make_head(magi);
	env_init(magi);
}

void	magi_reset(t_magi	*magi)
{
	reset_list(&magi->out_head);
	reset_list(&magi->head);
	reset_list(&magi->in_head);
	reset_list(&magi->read_input);
	magi->echo_n = 0;
	magi->redirect = 0;
	magi->redir_error = 0;
	magi->heredoc = 0;
}

void	magi_exit(char	*line)
{
	if (line == NULL)
	{
		printf("exit\n");
		exit (0);
	}
}
