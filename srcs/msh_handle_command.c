/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_handle_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 13:57:07 by heynard           #+#    #+#             */
/*   Updated: 2017/07/12 13:57:08 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			msh_get_sigint(int sig)
{
	write(1, "\r\n", 2);
}

static void			msh_wait_child(pid_t pid, const char *path)
{
	int				status;

	signal(SIGINT, msh_get_sigint);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 11)
		{
			ft_putstr_fd("[1]    ", 2);
			ft_putnbr_fd(pid, 2);
			ft_putstr_fd(" segmentation fault  ", 2);
			ft_putendl_fd(path, 2);
		}
	}
}

static void			msh_exec_bin(t_shell *shell, const char *path, char **av)
{
	pid_t			pid;
	char			**environ;

	environ = msh_swapenv_to_char(shell->env);
	pid = fork();
	if (pid > 0)
		msh_wait_child(pid, path);
	else if (pid == 0)
	{
		if ((shell->exit_value = execve(path, av, environ)) == -1)
		{
			ft_putstr_fd("minishell: permission denied: ", 2);
			ft_putendl_fd((char *)path, 2);
			msh_free_argv(environ);
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_putendl_fd("minishell: cannot create processus.", 2);
	msh_free_argv(environ);
}

static void			msh_path_finding(t_shell *shell, char **av)
{
	t_path_finding	pf;
	struct stat		buffer;

	pf.current_path = msh_get_var_env(shell->env, "PATH");
	while (pf.current_path)
	{
		pf.next_path = ft_strchr(pf.current_path, ':');
		pf.next_path ? pf.next_path++ : (0);
		pf.tmp = ft_strjoin_spec(pf.current_path, "/", ':');
		pf.path = ft_strjoin(pf.tmp, av[0]);
		free(pf.tmp);
		if (stat(pf.path, &buffer) == 0)
		{
			msh_exec_bin(shell, pf.path, av);
			free(pf.path);
			return ;
		}
		free(pf.path);
		pf.current_path = pf.next_path;
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(av[0], 2);
}

void				msh_handle_command(t_shell *shell, char **av)
{
	struct stat		buffer;

	if (stat(av[0], &buffer) == 0)
		msh_exec_bin(shell, av[0], av);
	else
		msh_path_finding(shell, av);
}
