/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ascii_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 12:01:28 by epanholz      #+#    #+#                 */
/*   Updated: 2022/01/08 14:35:57 by ubuntu        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	cursed_sleep(int mod)
{
	long	i;

	i = 0;
	if (mod == SHORT)
	{
		while (i < 243741824)
			i++;
	}
	if (mod == LONG)
	{
		while (i < 593741824)
			i++;
	}
}

void	clear_screen(void)
{
	const char	*clear_screen_ansii;

	clear_screen_ansii = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, clear_screen_ansii, 11);
}

void	print_ascii(t_magi *magi)
{
	clear_screen();
	loading_bar();
	clear_screen();
	cursed_sleep(LONG);
	nerv_logo();
	cursed_sleep(LONG);
	boot_up(magi);
	cursed_sleep(LONG);
}
