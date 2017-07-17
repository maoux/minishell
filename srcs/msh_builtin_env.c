/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 17:42:27 by heynard           #+#    #+#             */
/*   Updated: 2017/07/17 17:42:29 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			msh_fill_var_env(t_var_env *new, char *name, char *value)
{
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
}

static t_var_env	*msh_copy_env_temp(t_shell *shell)
{
	t_var_env		*tmpenv;
	t_var_env		*tmp2;
	t_var_env		*tmp;
	t_var_env		*new;

	tmp = shell->env;
	if (shell->env == NULL)
		return (NULL);
	if ((tmpenv = msh_malloc_env(shell)) == NULL)
		return (shell->env);
	msh_fill_var_env(tmpenv, tmp->name, tmp->value);
	tmp = tmp->next;
	tmp2 = tmpenv;
	while (tmp)
	{
		if ((new = msh_malloc_env(shell)) == NULL)
			return (shell->env);
		msh_fill_var_env(new, tmp->name, tmp->value);
		tmp2->next = new;
		tmp2 = tmp2->next;
		tmp = tmp->next;
	}
	return (tmpenv);
}

static void			msh_modify_tmp_env(t_shell *shell, char **av, int *i)
{
	char			*name;
	char			*value;

	name = ft_strcpy_spec(av[*i], '=');
	value = ft_strrcpy_spec(av[*i], '=');
	if (msh_get_var_env(shell->env, name))
		msh_update_env(shell, name, value);
	else
		msh_add_to_env(shell, name, value);
	ft_strdel(&name);
	ft_strdel(&value);
	(*i)++;
}

void				msh_builtin_env(t_shell *shell, int ac, char **av)
{
	int				i;
	t_var_env		*tmpenv;
	char			*tmp;

	if (ac <= 1)
		msh_print_env(shell->env);
	else
	{
		tmpenv = shell->env;
		shell->env = msh_copy_env_temp(shell);
		i = 1;
		while (i < ac && (tmp = ft_strchr(av[i], '=')))
			msh_modify_tmp_env(shell, av, &i);
		if (i == ac)
			msh_print_env(shell->env);
		else
			msh_handle_command(shell, &av[i]);
		msh_free_env(shell->env);
		shell->env = tmpenv;
	}
}
