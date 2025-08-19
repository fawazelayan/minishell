/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:45:25 by felayan           #+#    #+#             */
/*   Updated: 2025/08/05 18:53:36 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MALLOC_FAILURE -42
# define SUCCESS 0
# define FAIL -1

# include <readline/readline.h>	// readline funcs
# include <readline/history.h>	// history funcs
# include <sys/wait.h>	// wait, waitpid
# include <stdbool.h>	// bool def
# include <unistd.h>	// a lot of unix funcs
# include <stdlib.h>	// malloc, free
# include <signal.h>	// signal handling
# include <stdio.h>		// printf
# include <fcntl.h>		//	open
# include <errno.h>		// error status
# include "libft.h"		// libft

typedef enum e_redir_type	t_redir_type;

typedef struct s_redir		t_redir;
typedef struct s_data		t_data;
typedef struct s_exp		t_exp;
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;

extern volatile sig_atomic_t	g_sig;

enum e_redir_type
{
	HEREDOC,
	APPEND,
	OUT,
	IN
};

struct s_redir
{
	char			*file;
	t_redir_type	type;
};

struct s_env
{
	int		entries;
	char	**value;
	char	**key;
};

struct s_cmd
{
	int		redir_count;
	int		pipe_fd[2];
	char	**tokens;
	t_redir	*redir;
	t_cmd	*next;
	pid_t	pid;
};

struct s_data
{
	char	**input_tokens;
	int		exit_status;
	int		cmd_count;
	t_cmd	*cmd;
	t_env	env;
};

void	start_shell(t_data *dt, char **envp);

int		split_into_tokens(const char *input, t_data *dt);
int 	tokenizer(const char *input, t_data *dt);

int		skip_starting_whitesp(const char *s);
bool	is_empty(const char *s);
bool	is_redir(char *token);
bool	is_pipe(char *token);

int		syntax_check(const char **tokens, bool quotes_err);
bool	is_closed_quotes(const char *input, int loc);

void	clean_env(t_env *env, int count, int exit_status);
void	init_env(t_env *env, char **envp);
void	print_export(const t_env *env);
void	print_env(const t_env *env);

#endif