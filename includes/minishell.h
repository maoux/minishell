/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:06:05 by heynard           #+#    #+#             */
/*   Updated: 2017/06/27 20:33:12 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H
# define __MINISHELL_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>

# define TRUE	1
# define FALSE	0

# define ERROR_CUURENT_DIR "minishell: cannot access current working directory."
# define ERR_MAL_ENV "minishell: memory allocation failed while setting env."
# define ERROR_GNL "minishell: get_next_line failed to read in stdin."

typedef struct	s_var_env
{
	char				*name;
	char				*value;
	struct s_var_env	*next;
}				t_var_env;

typedef struct	s_shell
{
	struct s_var_env	*env;
	int					exit_value;
	short int			exit_builtin;
	short int			malloc_error;
}				t_shell;

typedef struct	s_options
{
	char				opt;
	struct s_options	*next;
}				t_options;

int				msh_prompt();
void			msh_init_env(char **environ, t_shell *shell);
t_var_env		*msh_copy_environ(char **environ, t_shell *shell,
									t_var_env *tmp, t_var_env *new);
t_var_env		*msh_malloc_env(t_shell *shell);
char			*msh_get_var_env(t_var_env *env, const char *name);
void			msh_print_env(t_var_env *env);
void			msh_free_env(t_var_env *env);
void			msh_handle_line(t_shell *shell, char *command);
char			**msh_parse_line(const char *line, char **next, int *ac);
char			**msh_strsplit_spec(char const *s, int *ac, char c, char spec);
int				msh_check_quotes(const char *str);
int				msh_treat_command(int ac, char **av, t_var_env *env);
t_var_env		*msh_update_env(t_shell *shell, char *name, char *value);
t_var_env		*msh_add_to_env(t_shell *shell, char *name, char *value);
void			msh_free_argv(char **av);
void			msh_delete_var_env(t_var_env *env, char *name);

/*
** gestion des signaux
*/

void			msh_get_sigint(int sig);
void			msh_default_catch_sigint(int sig);

/*
** BUILTIN CD
*/

int				msh_builtin_cd(t_var_env *env, int ac, char **av);

/*
** BUILTIN ECHO
*/

void			msh_builtin_echo(int ac, char **av);

/*
** BUILTIN SETENV
*/

void			msh_builtin_setenv(t_shell *shell, int ac, char **av);

/*
** BUILTIN UNSETENV
*/

int				msh_builtin_unsetenv(t_var_env *env, int ac, char **av);

/*
** BUILTIN EXIT
*/

void			msh_builtin_exit(t_shell *shell, int ac, char **av);

#endif
