/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:53:00 by heynard           #+#    #+#             */
/*   Updated: 2017/07/11 14:53:01 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t		sizeof_env(t_var_env *env)
{
	t_var_env		*tmp;
	size_t			i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void				msh_init_env(char **environ, t_shell *shell)
{
	char			*buffer;

	buffer = NULL;
	if (!(shell->env = msh_copy_environ(environ, shell, NULL, NULL)))
	{
		shell->env = msh_add_to_env(shell, "PATH", "/usr/bin:/bin");
		if ((buffer = getcwd(buffer, 0)) == NULL)
			ft_putendl_fd(ERROR_CUURENT_DIR, 2);
		shell->env = msh_add_to_env(shell, "PWD", buffer ? buffer : "");
		shell->env = msh_add_to_env(shell, "SHELL", "minishell");
		shell->env = msh_add_to_env(shell, "OLDPWD",
									msh_get_var_env(shell->env, "PWD"));
	}
	if (!msh_get_var_env(shell->env, "PATH"))
		shell->env = msh_add_to_env(shell, "PATH", "/usr/bin:/bin");
	if (!msh_get_var_env(shell->env, "PWD"))
	{
		if ((buffer = getcwd(buffer, 0)) == NULL)
			ft_putendl_fd(ERROR_CUURENT_DIR, 2);
		shell->env = msh_add_to_env(shell, "PWD", buffer ? buffer : "");
	}
	if (!msh_get_var_env(shell->env, "OLDPWD"))
		shell->env = msh_add_to_env(shell, "OLDPWD",
								msh_get_var_env(shell->env, "PWD"));
	ft_strdel(&buffer);
}

char				**msh_swapenv_to_char(t_var_env *env)
{
	char			**environ;
	char			*tmp_char;
	t_var_env		*tmp;
	size_t			i;

	i = sizeof_env(env);
	if (i == 0)
		return (NULL);
	if (!(environ = (char **)malloc(sizeof(char *) * i + 1)))
	{
		ft_putendl_fd("minishell: memory allocation failed in swapenv", 2);
		return (NULL);
	}
	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		tmp_char = ft_strjoin(tmp->name, "=");
		environ[i++] = ft_strjoin(tmp_char, tmp->value);
		ft_strdel(&tmp_char);
		tmp = tmp->next;
	}
	environ[i] = NULL;
	return (environ);
}
