/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 02:53:37 by felayan           #+#    #+#             */
/*   Updated: 2025/09/11 02:53:38 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	token_cmd_count(t_tokenizer *tokens, int *wrds, int *rdrs)
{
	(*wrds) = 0;
	(*rdrs) = 0;
	while (tokens && !is_pipe(tokens -> token))
	{
		if (is_redir(tokens -> token))
		{
			(*rdrs)++;
			tokens = tokens -> next;
		}
		else
			(*wrds)++;
		tokens = tokens -> next;
	}
}

t_cmd	*init_cmd(t_data *dt, t_tokenizer *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		clean_data(dt, MALLOC_FAILURE);
	ft_memset(cmd, 0, sizeof(t_cmd));
	token_cmd_count(tokens, &cmd -> word_count, &cmd -> redir_count);
	cmd -> pipe_fd[0] = -1;
	cmd -> pipe_fd[1] = -1;
	cmd -> pid = -1;
	cmd -> tokens = malloc(sizeof(char *) * (cmd ->word_count + 1));
	if (cmd -> redir_count > 0)
		cmd -> redir = malloc(sizeof(t_redir) * (cmd -> redir_count));
	if (!cmd -> tokens || (!cmd -> redir && cmd ->redir_count > 0))
	{
		free(cmd -> tokens);
		free(cmd -> redir);
		free(cmd);
		clean_data(dt, MALLOC_FAILURE);
	}
	cmd -> tokens[cmd -> word_count] = NULL;
	return (cmd);
}

static t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd && cmd -> next)
		cmd = cmd -> next;
	return (cmd);
}

void	append_cmd(t_data *dt, t_cmd *new)
{
	t_cmd	*last;

	if (!dt -> cmds)
		dt -> cmds = new;
	else
	{
		last = get_last_cmd(dt -> cmds);
		last -> next = new;
	}
}
