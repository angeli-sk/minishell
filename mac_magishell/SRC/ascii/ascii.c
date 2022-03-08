/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ascii.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Angi <Angi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/20 11:58:46 by Angi          #+#    #+#                 */
/*   Updated: 2022/02/10 17:21:44 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../magi.h"

void	nerv_logo(void)
{
	printf("\n\
\033[1;38;5;196m\n\
                           ,**************\n\
                         ****************\n\
            *           **********************.\n\
             *,         **************************\n\
               *.      *****************************\n\
                 ** .*********************************\n\
                    *******************************\n\
   ***      ***    ** ********************\n\
    * **     .     **   ,*********************\n\
    *   **   .     ** ** ,*********************\n\
    *     ** .     **        *******************\n\
    *       **     **       *  .*****************\n\
  *****      *   ***********      ***************,\n\
                      ***,,***    ****************\n\
                       **    ,**    ** ***********.\n\
                       **   .**      **  **********\n\
                       ** .**         **  ********,\n\
                       **   ,**        ***    ****\n\
                     ,****    ***,      *       ***\n\
  𝐆𝐎𝐃 𝐈𝐒 𝐈𝐍 𝐇𝐈𝐒 𝐇𝐄𝐀𝐕𝐄𝐍, 𝐀𝐋𝐋 𝐈𝐒 𝐑𝐈𝐆𝐇𝐓 𝐖𝐈𝐓𝐇 𝐓𝐇𝐄 𝐖𝐎𝐑𝐋𝐃.\033[m\n\
");
}

void	loading_bar(void)
{
	write(1, "\033[1;38;5;196mB O O T I N G . . .\n", 34);
	cursed_sleep(LONG);
	write(1, "█", 4);
	cursed_sleep(SHORT);
	write(1, "██", 7);
	cursed_sleep(SHORT);
	write(1, "███", 10);
	cursed_sleep(SHORT);
	write(1, "████", 13);
	cursed_sleep(SHORT);
	write(1, "█████", 16);
	cursed_sleep(SHORT);
	write(1, "██████\n\033[0m", 24);
	cursed_sleep(LONG);
	cursed_sleep(SHORT);
}

void	error_msg_dmy(void)
{
	printf("\033[38;5;196m▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n\
▒                        ,,###=,                    ▒\n\
▒ 𝐒𝐄𝐂𝐔𝐑𝐈𝐓𝐘 𝐋𝐄𝐕𝐄𝐋:𝐄𝐄𝐄    𝐍𝐄###=   𝐒𝐄𝐂𝐔𝐑𝐈𝐓𝐘:𝐋𝐎𝐂𝐊𝐄𝐃    ▒\n\
▒ PERSONAL CODE: - - -   𝐑𝐕##=   NAME: - - - -      ▒\n\
▒  ____________________  ---''  _________________   ▒\n\
▒    -------------------------------------------    ▒\n\
▒    |             ＥＭＥＲＧＥＮＣＹ          |    ▒\n\
▒    -------------------------------------------    ▒\n\
▒                   𝐈𝐍𝐏𝐔𝐓 𝐃𝐄𝐍𝐈𝐄𝐃                    ▒\n\
▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒\n\
\033[37m");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	boot_up_dmy(t_magi	*magi)
{
	printf(\
	"\033[1;38;5;85m▒\033[1;38;5;85m▒\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\
	\b\b\b\b\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;196m ⚠ \033[1;38;5;85m▒\
	\b\b\b\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[1;38;5;85m▒\
	\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;85m\n");
	printf("\033[1;38;5;208mＣＯＤＥ： X̸̲̱̪͇̼̚͝X̸̲̱̪͇̼̚͝X̶̡͈̭̀͆̃̎̓̏͋\n\033[1;38;5;166m\
	FILE: D̷͈̤̿̒̔̎͒͘̚͠͝M̴̧͇͎̟̞͎͉̫͉͑̉͋͐̌Y̶̺̪͌_̵͕̊̔͛̌̾̈̋̓S̵̺̝̯̐̆̋̔̐̕͜͝Ỳ̵̛̭̠͕̪͎̣̥̣̩͋̊̇̆͂S̷͎̝̈́͐̂͝\n\tEXTENTION:2021\n\
	M̶̢͇̩̹̋̏̒̅̀̂Ḻ̸͕̦̈̓͆ͅ_MODE: O̵̤͕͔͙̱̯͆̄̈́̓̂̅͐̍̚̕N̶̟͖͋̑̃͒̃͊̾̐ͅ\n\tPRIORITY\
	:̶̭͕͚̪̼̳̬̾͜Ẍ̵̡̧̡͖̥̣́̂̑̿̈́͜X̵̧̛̙̭̻̩̫̙͚̠͚̎̎͒̾̓́͘͝͝Ẍ̶͎́̒̅̃͆͐͝\n");
	if (magi->mod == 0)
		printf("UNIT:00\033[37m\n");
	else if (magi->mod == 1)
		printf("UNIT:01\033[37m\n");
	else if (magi->mod == 2)
		printf("UNIT:02\033[37m\n");
}

void	boot_up(t_magi	*magi)
{
	printf(\
	"\033[1;38;5;85m▒\033[1;38;5;85m▒\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\
	\b\b\b\b\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;196m ⚠ \033[1;38;5;85m▒\
	\b\b\b\033[1;38;5;72m▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\033[1;38;5;85m▒\
	\b\b\b\b\033[1;38;5;85m▒\033[1;38;5;85m\n");
	printf("\033[1;38;5;208mＣＯＤＥ： ４２\n\033[1;38;5;166m\
	FILE: MAGI_SYS\n\tEXTENTION:2021\n\
	ML_MODE: OFF\n\tPRIORITY:AAA\n\t");
	if (magi->mod == 0)
		printf("UNIT:00\033[37m\n");
	else if (magi->mod == 1)
		printf("UNIT:01\033[37m\n");
	else if (magi->mod == 2)
		printf("UNIT:02\033[37m\n");
}