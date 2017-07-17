/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:53:30 by heynard           #+#    #+#             */
/*   Updated: 2017/06/30 16:53:33 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int			msh_sizeofsplit(const char *s, char c, char spec)
{
	int				i;
	int				ret;

	ret = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0' && s[i] != spec)
	{
		if (s[i] == c || s[i] == '\t')
		{
			while (s[i] == c || s[i] == '\t')
				i++;
		}
		else if (s[i] == '"' || s[i] == '\'' || s[i] == '`')
			msh_parse_quotes(s, spec, &i, &ret);
		else
		{
			while (s[i] != c && s[i] != '\t' && s[i] != '\0' && s[i] != spec)
				i++;
			ret++;
		}
	}
	return (ret);
}

static char			**msh_split(const char *s, char c, char **tab, char spec)
{
	t_split			spt;

	spt.i = 0;
	spt.j = 0;
	spt.c = c;
	spt.spec = spec;
	while (s[spt.i] != '\0' && s[spt.i] != spec)
	{
		if (s[spt.i] == c || s[spt.i] == '\t')
			while (s[spt.i] == c || s[spt.i] == '\t')
				spt.i++;
		else if (s[spt.i] == '"' || s[spt.i] == '\'' || s[spt.i] == '`')
			msh_split_quotes(&spt, tab, s);
		else
		{
			spt.start = spt.i;
			while (s[spt.i] != c && s[spt.i] != '\t' &&
				s[spt.i] != '\0' && s[spt.i] != spec)
				spt.i++;
			tab[spt.j++] = ft_strsub(s, spt.start, spt.i - spt.start);
		}
		tab[spt.j] = NULL;
	}
	return (tab);
}

char				**msh_strsplit_spec(char const *s, int *ac,
											char c, char spec)
{
	char			**tab;
	int				i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i) == ' ' || *(s + i) == '\t')
		i++;
	if (*(s + i) == '\0' || *(s + i) == spec)
		return (NULL);
	*ac = msh_sizeofsplit(s, c, spec);
	tab = (char **)malloc(sizeof(char *) * (*ac) + 1);
	if (tab == NULL)
	{
		ft_putendl_fd("minishell: Memory allocation failed in ft_strsplit", 2);
		return (NULL);
	}
	tab = msh_split(s, c, tab, spec);
	return (tab);
}
