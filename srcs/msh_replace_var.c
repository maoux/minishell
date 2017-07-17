/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_replace_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:36:35 by heynard           #+#    #+#             */
/*   Updated: 2017/07/17 15:36:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			msh_replace_bslash(t_shell *shell, char **av, int ac)
{
	char		*tmp;
	int			j;
	int			i;

	i = 1;
	while (i < ac)
	{
		tmp = av[i];
		while ((tmp = ft_strchr(tmp, '\\')))
		{
			j = 0;
			while (tmp[j] != '\0')
			{
				tmp[j] = tmp[j + 1];
				j++;
			}
			tmp[j] = '\0';
			tmp++;
		}
		i++;
	}
}

void			msh_replace_var(t_shell *shell, char **av, int ac)
{
	int			i;
	char		*tmp;
	char		*arg;

	i = 1;
	while (i < ac)
	{
		if ((tmp = ft_strchr(av[i], '$')) != NULL)
		{
			tmp++;
			if (*tmp != '\0' && *tmp != ' ')
			{
				*(tmp - 1) = '\0';
				if (msh_get_var_env(shell->env, tmp) != NULL)
				{
					arg = av[i];
					av[i] = (av[i] != NULL) ?
						ft_strjoin(av[i], msh_get_var_env(shell->env, tmp)) :
						ft_strdup(msh_get_var_env(shell->env, tmp));
					ft_strdel(&arg);
				}
			}
		}
		i++;
	}
}
