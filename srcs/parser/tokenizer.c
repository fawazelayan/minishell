/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:51 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:04:53 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	split_into_tokens(const char *input, t_data *dt)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			add_single_quotes(dt, input, &i);
		else if (input[i] == '\"')
			add_double_quotes(dt, input, &i);
		else if (is_redir(&input[i]) || is_pipe(&input[i]))
			add_operator(dt, input, &i);
		else if (is_word(&input[i]))
			add_word(dt, input, &i);
		else
			i++;
	}
}

int	tokenizer(const char *input, t_data *dt)
{
	int		i;
	bool	is_closed;

	i = skip_whitesp(input);
	is_closed = is_closed_quotes(input, i);
	if (is_closed)
		split_into_tokens(input + i, dt);
	if (syntax_check(dt -> tokens, !is_closed))
	{
		dt -> exit_status = 2;
		return (SYNTAX_ERR);
	}
	return (SUCCESS);
}
