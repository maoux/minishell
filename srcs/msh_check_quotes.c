/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:22:06 by heynard           #+#    #+#             */
/*   Updated: 2017/07/06 16:22:08 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					msh_check_quotes(const char *str)
{
	char			c;
	int				i;

	i = 0;
	while (str[i] != ';' && str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '`')
		{
			c = str[i++];
			while (str[i] != c || (str[i] == c && str[i - 1] == '\\'))
			{
				if (str[i] == '\0' || str[i] == ';')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}
