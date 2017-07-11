/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 14:27:56 by heynard           #+#    #+#             */
/*   Updated: 2017/07/11 14:27:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		msh_main_loop(t_shell *shell)
{
	char		*command;
	int			gnl;

	command = NULL;
	while (TRUE)
	{
		if (shell->exit_builtin)
			break ;
		msh_prompt(shell->env) ? ft_putstr("$>") : (0);
		gnl = get_next_line(0, &command);
		if (ft_strequ(command, "exit") || !gnl)
		{
			!gnl ? ft_putendl("exit") : ft_strdel(&command);
			break ;
		}
		if (gnl < 0)
			ft_putendl_fd(ERROR_GNL, 2);
		else
			msh_handle_line(shell, command);
	}
}

int				main(int ac, char **av)
{
	extern char	**environ;
	t_shell		shell;
	int			exit_value;

	shell.exit_builtin = 0;
	shell.exit_value = 0;
	msh_init_env(environ, &shell);
	msh_main_loop(&shell);
	shell.env ? msh_free_env(shell.env) : (0);
	return (shell.exit_value);
}
