/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_add_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:05:47 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:05:47 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_tokenizer	*get_last_token(t_tokenizer *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens -> next)
		tokens = tokens -> next;
	return (tokens);
}

void	add_token(t_data *dt, t_tk t_type, char *token, bool exp)
{
	t_tokenizer	*new;
	t_tokenizer	*last;

	last = NULL;
	new = malloc(sizeof(t_tokenizer));
	if (!new)
		clean_data(dt, MALLOC_FAILURE);
	new -> token = token;
	new -> token_type = t_type;
	new -> is_expandable = exp;
	new -> next = NULL;
	if (!dt -> tokens)
		dt -> tokens = new;
	else
	{
		last = get_last_token(dt -> tokens);
		last -> next = new;
	}
}
