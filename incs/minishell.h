/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:45:25 by felayan           #+#    #+#             */
/*   Updated: 2025/07/01 20:45:48 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>	// readline funcs
#include <readline/history.h>	// history funcs
#include <sys/wait.h>	// wait, waitpid
#include <stdbool.h>	// bool def
#include <unistd.h>	// a lot of unix funcs
#include <stdlib.h>	// malloc, free
#include <signal.h>	// signal handling
#include <stdio.h>	// printf
#include <fcntl.h>	//	open
#include <errno.h>	// error status
#include "libft.h"	// libft

typedef enum e_redir_type	t_redir_type;

typedef struct s_redir	t_redir;
typedef struct s_data	t_data;
typedef struct s_exp	t_exp;
typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

volatile sig_atomic_t	g_sig = 0;

enum e_redir_type
{
	HEREDOC,
	APPEND,
	NONE,
	OUT,
	IN
};

struct s_redir
{
	char	*file;
	int		type;
};

struct s_exp
{
	bool	*is_null;
	char	**value;
	char	**key;
};

struct s_env
{
	char	**value;
	char	**key;
};

struct s_cmd
{
	pid_t	pid;
	char	**tokens;
	int		redir_count;
	bool	is_pipe;
	t_redir	*redir;
	t_cmd	*next;
};

struct s_data
{
	char	**parse_tokens;
	int		exit_status;
	char	*cmd_line;
	t_env	env;
	t_exp	exp;
	t_cmd	*cmd;
};

#endif