/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 11:23:09 by akramp        #+#    #+#                 */
/*   Updated: 2021/07/20 11:50:32 by Angi          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_pn_check(int pn)
{
	if (pn == 1)
		return (-1);
	else
		return (0);
}

static	long int	checker(const char *s, long int r, int *m, int *pn)
{
	if (*s >= '0' && *s <= '9')
		r = (*s - '0') + (r * 10);
	else if (*s <= 32 && *s != '\e' && (r != 0 || *m == 1))
		return (-1);
	else if (*s == '-' && r == 0 && *m == 0)
	{
		*m = 1;
		*pn = -1;
	}
	else if (*s == '+' && r == 0 && *m == 0)
		*m = 1;
	else if (*s > 32 || *s == '\e')
		return (-1);
	return (r);
}

int	ft_atoi(const char *str)
{
	long int	result;
	long int	prev;
	int			m;
	int			pn;
	long int	check;

	result = 0;
	m = 0;
	pn = 1;
	check = 0;
	while (*str != '\0')
	{
		prev = result;
		check = checker(str, result, &m, &pn);
		if (check == -1)
			break ;
		else
			result = check;
		if (prev > result)
			return (ft_pn_check(pn));
		str++;
	}
	result = (int)result;
	return (result * pn);
}
