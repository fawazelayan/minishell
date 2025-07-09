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

#include <readline/readline.h>	//readline funcs
#include <readline/history.h>	//history funcs
#include <unistd.h>	// a lot of unix funcs
#include <stdlib.h>	// malloc, free
#include <stdio.h>	// printf
#include <sys/wait.h>	// wait, waitpid
#include <signal.h>	// signal handling
#include <fcntl.h>	//	open
#include <errno.h>	// error status
#include "libft.h"	// libft
#include <stdbool.h>

volatile sig_atomic_t g_sig = 0;
typedef struct s_data	t_data;
typedef enum e_redir_type t_redir_type;

enum e_redir_type
{
	IN,
	OUT,
	HEREDOC,
	APPEND
};

typedef struct s_redir
{
	int		type;
	char	*file;
}	t_redir;

typedef struct s_exp
{
	char	**key;
	char	**value;
	int		is_null;
}	t_exp;

typedef struct s_cmd
{
	char	**tokens;
	t_redir *redir;
	int		nb_redir;
	bool	is_pipe;
	struct s_cmd	*next;
}	t_cmd;

struct s_data
{
	char	**env;
	char	**exp;
	t_cmd	cmd;
	int		exit_status;
	char	*cmd_line;
};
#endif
