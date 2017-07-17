/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:47:52 by heynard           #+#    #+#             */
/*   Updated: 2017/07/15 16:47:53 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void				msh_handle_cd_env(t_shell *shell, char *curpath)
{
	char			*pwd;

	pwd = msh_get_var_env(shell->env, "PWD");
	if (pwd)
		msh_update_env(shell, "OLDPWD", pwd);
	msh_update_env(shell, "PWD", curpath);
	shell->exit_value = 0;
}

void				msh_handle_cd_env_link(t_shell *shell, char *curpath)
{
	char			*buffer;
	char			*pwd;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (buffer == NULL)
	{
		ft_putendl_fd(ERROR_CUURENT_DIR, 2);
		return ;
	}
	pwd = msh_get_var_env(shell->env, "PWD");
	if (pwd)
		msh_update_env(shell, "OLDPWD", pwd);
	msh_update_env(shell, "PWD", buffer);
	ft_strdel(&buffer);
	shell->exit_value = 0;
}

char				*msh_catpath(t_shell *shell, const char *dir)
{
	char			*tmp;
	char			*pwd;

	pwd = NULL;
	pwd = msh_get_var_env(shell->env, "PWD");
	if (pwd)
	{
		tmp = ft_strjoin(pwd, "/");
		shell->curpath = ft_strjoin(tmp, dir);
		free(tmp);
		return (shell->curpath);
	}
	shell->exit_value = 1;
	return (NULL);
}
