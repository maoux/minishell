/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:47:26 by heynard           #+#    #+#             */
/*   Updated: 2017/07/12 15:47:27 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			msh_builtin_cd_home(t_shell *shell)
{
	char			*home;
	char			*pwd;

	home = msh_get_var_env(shell->env, "HOME");
	if (!home)
	{
		shell->exit_value = 1;
		return ;
	}
	if (chdir(home))
	{
		ft_putendl_fd("minishell: cannot access home directory.", 2);
		shell->exit_value = 1;
		return ;
	}
	pwd = msh_get_var_env(shell->env, "PWD");
	if (pwd)
		msh_update_env(shell, "OLDPWD", pwd);
	msh_update_env(shell, "PWD", home);
	shell->exit_value = 0;
}

static void			msh_builtin_cd_error(t_shell *shell, char *curpath,
											const char *dir)
{
	struct stat		buf;

	stat(curpath, &buf) < 0 ?
		ft_putstr_fd("cd: no such file or directory: ", 2) :
		ft_putstr_fd("cd: permission denied: ", 2);
	ft_putendl_fd(dir, 2);
	shell->exit_value = 1;
	ft_strdel(&(shell->curpath));
}

static void			msh_builtin_cd_standard(t_shell *shell, const char *dir)
{
	char			*curpath;
	char			*pwd;
	struct stat		buf;

	if (dir[0] == '/')
		curpath = (char *)dir;
	else if (!ft_strcmp(dir, "-"))
		curpath = msh_get_var_env(shell->env, "OLDPWD");
	else
		curpath = msh_catpath(shell, dir);
	if (curpath == NULL)
		return ;
	if (chdir(curpath) < 0)
	{
		msh_builtin_cd_error(shell, curpath, dir);
		return ;
	}
	msh_handle_cd_env_link(shell, curpath);
	ft_strdel(&(shell->curpath));
}

void				msh_builtin_cd(t_shell *shell, int ac, char **av)
{
	shell->curpath = NULL;
	if (ac <= 1)
		msh_builtin_cd_home(shell);
	else if ((!ft_strcmp(av[1], "--") && 2 == ac))
		msh_builtin_cd_home(shell);
	else if (!ft_strcmp(av[1], "--"))
		msh_builtin_cd_standard(shell, av[2]);
	else
		msh_builtin_cd_standard(shell, av[1]);
}
