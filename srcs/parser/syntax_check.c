/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:46:05 by felayan           #+#    #+#             */
/*   Updated: 2025/08/20 00:46:06 by felayan          ###   ########.fr       */
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

static bool	is_pipe_error(const char **tokens)
{
	int	i;

	i = 0;
	if (is_pipe(tokens[0]))
		return (true);
	while (tokens[i] && tokens[i + 1])
	{
		if (is_pipe(tokens[i]) && is_pipe(tokens[i + 1]))
			return (true);
		i++;
	}
	if (is_pipe(tokens[i]))
		return (true);
	return (false);
}

static bool	is_redir_error(const char **tokens, int *err_loc)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i + 1])
	{
		if (is_redir(tokens[i]) && is_redir(tokens[i + 1]))
		{
			*err_loc = i + 1;
			return (true);
		}
		if (is_redir(tokens[i]) && is_pipe(tokens[i + 1]))
		{
			*err_loc = i + 1;
			return (true);
		}
		i++;
	}
	if (is_redir(tokens[i]))
	{
		*err_loc = i;
		return (true);
	}
	return (false);
}

int	syntax_check(const char **tokens, bool quotes_err)
{
	int	err_loc;

	err_loc = 0;
	if (quotes_err)
	{
		ft_putstr_fd("forking: unclosed quotes\n", 2);
		return (SYNTAX_ERR);
	}
	else if (is_pipe_error(tokens))
	{
		ft_putstr_fd("forking: syntax error near unexpected token `|'\n", 2);
		return (SYNTAX_ERR);
	}
	else if (is_redir_error(tokens, &err_loc))
	{
		ft_putstr_fd("forking: syntax error near unexpected token `", 2);
		if (err_loc == 0)
			ft_putstr_fd("`newline", 2);
		else
			ft_putstr_fd(tokens[err_loc], 2);
		ft_putstr_fd("'\n", 2);
		return (SYNTAX_ERR);
	}
	return (0);
}
