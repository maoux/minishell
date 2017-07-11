/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 16:25:52 by heynard           #+#    #+#             */
/*   Updated: 2017/07/11 16:25:54 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int			msh_handle_builtin(t_shell *shell, int argc, char **argv)
{
//	if (ft_strequ("cd", argv[0]))
//		msh_builtin_cd(shell, argc, argv);
	if (ft_strequ("echo", argv[0]))
		msh_builtin_echo(argc, argv);
	else if (ft_strequ("setenv", argv[0]))
		msh_builtin_setenv(shell, argc, argv);
//	else if (ft_strequ("unsetenv", argv[0]))
//		msh_builtin_unsetenv(shell, argc, argv);
//	else if (ft_strequ("env", argv[0]))
//		msh_builtin_env(shell, argc, argv);
	else if (ft_strequ("exit", argv[0]))
		msh_builtin_exit(shell, argc, argv);
	else
		return (-1);
	return (0);
}

void				msh_free_argv(char **av)
{
	size_t			i;
	char			*tmp;

	if (av)
	{
		i = 0;
		while (av[i])
		{
			tmp = av[i];
			i++;
			free(tmp);
		}
		free(av);
	}
}

static void			msh_inner_handle_line(t_shell *shell, int argc,
											char **argv, char *next_command)
{
	if (argc <= 0)
		next_command ? msh_handle_line(shell, next_command) : (0);
	else if (msh_handle_builtin(shell, argc, argv) != -1)
		;
//	else
//		msh_handle_command(shell, argv);
}

void				msh_handle_line(t_shell *shell, char *command)
{
	char			**argv;
	char			*next_command;
	int				argc;

	next_command = NULL;
	if (command && ft_strcmp(command, ""))
	{
		if (msh_check_quotes(command))
		{
			ft_putendl_fd("minishell: quote not closed in last command.", 2);
			return ;
		}
		argv = msh_parse_line(command, &next_command, &argc);
		msh_inner_handle_line(shell, argc, argv, next_command);
		msh_free_argv(argv);
		next_command ? msh_handle_line(shell, next_command) : (0);
	}
	ft_strdel(&command);
}
