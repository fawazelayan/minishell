/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 02:47:22 by felayan           #+#    #+#             */
/*   Updated: 2025/09/11 02:47:22 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	add_redir_cmd(t_cmd *cmd, t_tokenizer **tokens, int	*rdr_i)
{
	if (!ft_strcmp((*tokens)-> token, ">"))
		cmd -> redir[*rdr_i].type = OUT;
	else if (!ft_strcmp((*tokens)-> token, "<"))
		cmd -> redir[*rdr_i].type = IN;
	else if (!ft_strcmp((*tokens)-> token, ">>"))
		cmd -> redir[*rdr_i].type = APPEND;
	else if (!ft_strcmp((*tokens)-> token, "<<"))
		cmd -> redir[*rdr_i].type = HEREDOC;
	(*tokens) = (*tokens)-> next;
	cmd -> redir[*rdr_i].file = ft_strdup((*tokens)-> token);
	if (!cmd -> redir[*rdr_i].file)
		return (MALLOC_FAILURE);
	(*rdr_i)++;
	return (SUCCESS);
}

static int	add_word_cmd(t_cmd *cmd, const char *token, int *wrd_i)
{
	cmd -> tokens[*wrd_i] = ft_strdup(token);
	if (!cmd -> tokens[*wrd_i])
		return (MALLOC_FAILURE);
	(*wrd_i)++;
	return (SUCCESS);
}

static int	add_cmd(t_cmd *cmd, t_tokenizer **tokens, int *rdr_i, int *wrd_i)
{
	while (*tokens && !is_pipe((*tokens)-> token))
	{
		if (is_redir((*tokens)-> token))
		{
			if (add_redir_cmd(cmd, tokens, rdr_i))
				return (MALLOC_FAILURE);
		}
		else
		{
			if (add_word_cmd(cmd, (*tokens)-> token, wrd_i))
				return (MALLOC_FAILURE);
		}
		(*tokens) = (*tokens)-> next;
	}
	return (SUCCESS);
}

static void	tokens_to_cmd(t_data *dt, t_tokenizer *tokens)
{
	t_cmd	*new_cmd;
	int		wrd_index;
	int		rdr_index;

	while (tokens)
	{
		wrd_index = 0;
		rdr_index = 0;
		new_cmd = init_cmd(dt, tokens);
		if (add_cmd(new_cmd, &tokens, &rdr_index, &wrd_index))
		{
			while (wrd_index--)
				free(new_cmd -> tokens[wrd_index]);
			while (rdr_index--)
				free(new_cmd -> redir[rdr_index].file);
			free(new_cmd -> tokens);
			free(new_cmd -> redir);
			clean_data(dt, MALLOC_FAILURE);
		}
		append_cmd(dt, new_cmd);
		if (tokens && is_pipe(tokens -> token))
			tokens = tokens -> next;
	}
}

int	parsing(t_data *dt, const char *input)
{
	if (tokenizer(input, dt) == SYNTAX_ERR)
		return (SYNTAX_ERR);
	expander(dt);
	print_tokens(dt -> tokens);
	tokens_to_cmd(dt, dt -> tokens);
	print_cmds(dt -> cmds);
	clean_tokens(dt ->tokens);
	dt -> tokens = NULL;
	return (SUCCESS);
}
