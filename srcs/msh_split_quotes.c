/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:13:24 by heynard           #+#    #+#             */
/*   Updated: 2017/07/17 15:13:25 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			msh_parse_quotes(const char *s, char spec, int *i, int *ret)
{
	char		qtype;

	qtype = s[*i];
	(*i)++;
	while (s[(*i)] != qtype && s[(*i)] != '\0' && s[(*i)] != spec)
		(*i)++;
	(*i)++;
	(*ret)++;
}

void			msh_split_quotes(t_split *spt, char **tab, const char *s)
{
	char		qtype;

	qtype = s[spt->i];
	spt->i += 1;
	spt->start = spt->i;
	while (s[spt->i] != qtype && s[spt->i] != '\0' && s[spt->i] != spt->spec)
		spt->i++;
	tab[spt->j] = ft_strsub(s, spt->start, spt->i - spt->start);
	spt->i += 1;
	spt->j += 1;
}
