/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_setenv_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 19:37:49 by heynard           #+#    #+#             */
/*   Updated: 2017/07/06 19:37:50 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_name(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int		update_env(t_shell *shell, int ac, char **av)
{
	if (ac == 2)
		shell->env = msh_update_env(shell, av[1], "");
	else
		shell->env = msh_update_env(shell, av[1], av[2]);
	return (0);
}

void			msh_builtin_setenv(t_shell *shell, int ac, char **av)
{
	if (ac <= 1)
		msh_print_env(shell->env);
	else if (check_name(av[1]) == 1)
	{
		ft_putstr_fd("setenv: Variable name must contain ", 2);
		ft_putendl_fd("alphanumeric characters.", 2);
		shell->exit_value = -1;
	}
	else
	{
		if (msh_get_var_env(shell->env, av[1]) != NULL)
			update_env(shell, ac, av);
		else if (ac == 2)
			shell->env = msh_add_to_env(shell, av[1], "");
		else
			shell->env = msh_add_to_env(shell, av[1], av[2]);
	}
	shell->exit_value = shell->malloc_error ? -1 : 1;
}
