/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:11:49 by heynard           #+#    #+#             */
/*   Updated: 2017/07/11 14:11:51 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				msh_signal_prompt(void)
{
	char		*buffer;
	char		*tmp;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
	{
		ft_putendl_fd(ERROR_CUURENT_DIR, 2);
		return (1);
	}
	tmp = buffer;
	buffer = ft_strrchr(buffer, '/');
	buffer = !buffer ? tmp : buffer;
	buffer = ft_strcmp(buffer, "/") ? buffer + 1 : buffer;
	ft_printf("%s \033[1;34m$>\033[0m ", buffer);
	ft_strdel(&tmp);
	return (0);
}

int				msh_prompt(t_var_env *env)
{
	char		*buffer;
	char		*tmp;

	buffer = NULL;
	if (msh_get_var_env(env, "PWD") == NULL)
	{
		buffer = getcwd(buffer, 0);
		if (buffer == NULL)
		{
			ft_putendl_fd(ERROR_CUURENT_DIR, 2);
			return (1);
		}
	}
	else
		buffer = ft_strdup(msh_get_var_env(env, "PWD"));
	tmp = buffer;
	buffer = ft_strrchr(buffer, '/');
	buffer = !buffer ? tmp : buffer;
	buffer = ft_strcmp(buffer, "/") ? buffer + 1 : buffer;
	ft_printf("%s \033[1;34m$>\033[0m ", buffer);
	ft_strdel(&tmp);
	return (0);
}
