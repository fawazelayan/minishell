/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:45:12 by felayan           #+#    #+#             */
/*   Updated: 2025/08/20 00:45:14 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	count_tokens(const char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	// while (input[i])
	// {
			// TODO
	// }
}

// static void	add_token(t_data *dt, int loc)
// {
		// TODO
// }

int	split_into_tokens(const char *input, t_data *dt)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	dt -> input_tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!dt -> input_tokens)
		clean_data(dt, MALLOC_FAILURE);
	// while (input[i])
	// {
			// TODO
	// }
}

int	tokenizer(const char *input, t_data *dt)
{
	int		i;
	bool	is_closed;

	i = skip_starting_whitesp(input);
	is_closed = is_closed_quotes(input, i);
	if (is_closed)
		split_into_tokens(input + i, dt);
	if (syntax_check(dt, !is_closed))
	{
		dt -> exit_status = 2;
		return (SYNTAX_ERR);
	}
	return (0);
}
