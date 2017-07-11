/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:02:29 by heynard           #+#    #+#             */
/*   Updated: 2017/06/27 21:36:24 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**msh_parse_line(const char *line, char **next, int *ac)
{
	char		**argv;

	(*next) = ft_strchr(line, ';');
	if ((argv = msh_strsplit_spec(line, ac, ' ', ';')) == NULL)
		*ac = -1;
	if (*next)
	{
		(*next)++;
		*((*next) - 1) = '\0';
	}
	else
		*next = NULL;
	return (argv);
}
