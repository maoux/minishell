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
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0' && s[i] != spec)
				i++;
			i++;
			ret++;
		}
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
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	if (s == NULL)
		return (tab);
	while (s[i] != '\0' && s[i] != spec)
	{
		if (s[i] == c || s[i] == '\t')
			while (s[i] == c || s[i] == '\t')
				i++;
		else if (s[i] == '"')
		{
			start = ++i;
			while (s[i] != '"' && s[i] != '\0' && s[i] != spec)
				i++;
			tab[j] = ft_strsub(s, start, i - start);
			i++;
			j++;
		}
		else
		{
			start = i;
			while (s[i] != c && s[i] != '\t' && s[i] != '\0' && s[i] != spec)
				i++;
			tab[j] = ft_strsub(s, start, i - start);
			j++;
		}
		tab[j] = NULL;
	}
	return (tab);
}

char				**msh_strsplit_spec(char const *s, int *ac, char c, char spec)
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
		ft_printf("minishell: Memory allocation failed in ft_strsplit\n");
		return (NULL);
	}
	tab = msh_split(s, c, tab, spec);
	return (tab);
}
