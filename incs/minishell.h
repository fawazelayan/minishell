/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:12:29 by felayan           #+#    #+#             */
/*   Updated: 2025/09/03 00:12:31 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# define RED	"\033[1;31m"
# define RST	"\033[0m"
# define MALLOC_FAILURE -42
# define SUCCESS 0
# define SYNTAX_ERR -1

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

typedef struct s_tokenizer		t_tokenizer;
typedef struct s_redir			t_redir;
typedef struct s_data			t_data;
typedef struct s_exp			t_exp;
typedef struct s_env			t_env;
typedef struct s_cmd			t_cmd;

typedef enum e_rdr				t_rdr;
typedef enum e_tk				t_tk;

extern volatile sig_atomic_t	g_sig;

enum e_tk
{
	OPERATOR,
	SINGLE,
	DOUBLE,
	WORD
};

enum e_rdr
{
	HEREDOC,
	APPEND,
	OUT,
	IN
};

struct s_tokenizer
{
	bool			is_expandable;
	t_tk			token_type;
	char			*token;
	t_tokenizer		*next;
};

struct s_redir
{
	char			*file;
	t_rdr			type;
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
	int			exit_status;
	int			cmd_count;
	t_tokenizer	*tokens;
	t_cmd		*cmds;
	t_env		env;
};

void	handle_sigint(int signum); // FOR TESTING ONLY
void	print_tokens(t_tokenizer *tokens); // FOR TESTING ONLY

void	start_shell(t_data *dt, char **line, char **envp);

void	clean_env(t_env *env, int count, int exit_status);
void	clean_data(t_data *dt, int status);
void	clean_tokens(t_tokenizer *tokens);

int		tokenizer(const char *input, t_data *dt);

bool	is_redir(const char *token);
bool	is_pipe(const char *token);
bool	is_word(const char *token);
bool	is_empty(const char *s);
int		skip_whitesp(const char *s);

int		syntax_check(t_tokenizer *tokens, bool quotes_err);
bool	is_closed_quotes(const char *input, int loc);

void	add_token(t_data *dt, t_tk t_type, char *token, bool exp);
void	add_double_quotes(t_data *dt, const char *input, int *i);
void	add_single_quotes(t_data *dt, const char *input, int *i);
void	add_operator(t_data *dt, const char *input, int *i);
void	add_word(t_data *dt, const char *input, int *i);

int		expand_var(t_data *dt, const char *token, char **expanded);
void	expander(t_data *dt);

char	*append_str(t_env *env, char *s1, const char *s2, bool is_special);
char	*append_char(char *s, char c);
int		crt_var(t_env *env, char **expanded, char *key, bool is_special);
bool	is_var(char var);

char	*get_env_value(t_env *env, const char *key);
void	init_env(t_env *env, char **envp);
void	print_export(const t_env *env);
void	print_env(const t_env *env);

int		ft_strcmp(char *s1, const char *s2);

#endif
