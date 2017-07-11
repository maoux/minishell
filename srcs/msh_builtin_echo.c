/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 17:31:25 by heynard           #+#    #+#             */
/*   Updated: 2017/07/06 17:31:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				msh_builtin_echo(int ac, char **av)
{
	unsigned int	i;
	short int		n;

	if (ac <= 1)
		return ;
	i = 1;
	n = 1;
	while (i < ac && ft_strequ(av[i], "-n"))
	{
		i += 1;
		n = 0;
	}
	while (i < ac)
	{
		ft_printf("%s", av[i++]);
		if (i < ac)
			ft_putchar(' ');
	}
	if (n)
		ft_putchar('\n');
}
