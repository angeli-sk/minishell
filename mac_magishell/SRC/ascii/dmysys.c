/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dmysys.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ubuntu <ubuntu@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/04 15:16:10 by ubuntu        #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	dmysys(char *line, t_magi *magi)
{
	const char	*mod[3] = {"eva-00", "eva-01", "eva-02"};
	int			i;

	i = 0;
	error_msg_dmy();
	while (i < 3)
	{
		if (token_cmp(line, mod[i]) == 0)
		{
			clear_screen();
			entry_plug(magi, line);
			break ;
		}
		i++;
	}
	magi_reset(magi);
	free(line);
}
