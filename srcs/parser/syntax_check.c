/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:06:04 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:06:07 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	is_closed_quotes(const char *input, int loc)
{
	while (input[loc])
	{
		if (input[loc] == '\"')
		{
			loc++;
			while (input[loc] && input[loc] != '\"')
				loc++;
			if (input[loc] != '\"')
				return (false);
		}
		else if (input[loc] == '\'')
		{
			loc++;
			while (input[loc] && input[loc] != '\'')
				loc++;
			if (input[loc] != '\'')
				return (false);
		}
		loc++;
	}
	return (true);
}

static bool	is_pipe_error(t_tokenizer *tokens, t_tokenizer **tr)
{
	if (is_pipe(tokens -> token))
	{
		*tr = tokens;
		return (true);
	}
	while (tokens && tokens -> next)
	{
		if ((is_pipe(tokens -> token) && is_pipe(tokens -> next -> token))
			|| (is_redir(tokens -> token) && is_pipe(tokens -> next -> token)))
		{
			*tr = tokens -> next;
			return (true);
		}
		tokens = tokens -> next;
	}
	if (is_pipe(tokens -> token))
	{
		*tr = tokens;
		return (true);
	}
	return (false);
}

static bool	is_redir_error(t_tokenizer *tokens, bool *is_new, t_tokenizer **tr)
{
	*is_new = false;
	while (tokens && tokens -> next)
	{
		if (is_redir(tokens -> token) && is_redir(tokens -> next -> token))
		{
			*tr = tokens -> next;
			return (true);
		}
		tokens = tokens -> next;
	}
	if (is_redir(tokens -> token))
	{
		*tr = tokens;
		*is_new = true;
		return (true);
	}
	return (false);
}

static void	print_syntax_error(char *token, bool quotes_err, bool is_new)
{
	if (quotes_err)
		ft_putstr_fd("minishell: unclosed quotes\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (is_new)
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
}

int	syntax_check(t_tokenizer *tokens, bool quotes_err)
{
	bool		is_newline_err;
	t_tokenizer	*tr;

	tr = NULL;
	is_newline_err = false;
	if (quotes_err)
	{
		print_syntax_error(NULL, true, false);
		return (SYNTAX_ERR);
	}
	else if (is_pipe_error(tokens, &tr))
	{
		print_syntax_error(tr -> token, false, false);
		return (SYNTAX_ERR);
	}
	else if (is_redir_error(tokens, &is_newline_err, &tr))
	{
		if (is_newline_err)
			print_syntax_error("newline", false, true);
		else
			print_syntax_error(tr -> token, false, false);
		return (SYNTAX_ERR);
	}
	return (SUCCESS);
}
