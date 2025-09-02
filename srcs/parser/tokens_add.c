/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:05:37 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:05:38 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	add_single_quotes(t_data *dt, const char *input, int *i)
{
	int		sub_len;
	int		start;
	char	*sub;

	(*i)++;
	sub = NULL;
	start = *i;
	sub_len = 0;
	while (input[*i] && input[*i] != '\'')
	{
		(*i)++;
		sub_len++;
	}
	sub = ft_substr(input, start, sub_len);
	if (!sub)
		clean_data(dt, MALLOC_FAILURE);
	add_token(dt, SINGLE, sub, false);
	if (input[*i] == '\'')
		(*i)++;
}

void	add_double_quotes(t_data *dt, const char *input, int *i)
{
	int		sub_len;
	int		start;
	char	*sub;
	bool	is_expandable;

	(*i)++;
	sub = NULL;
	start = *i;
	sub_len = 0;
	is_expandable = false;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$' && is_var(input[*i + 1]))
			is_expandable = true;
		(*i)++;
		sub_len++;
	}
	sub = ft_substr(input, start, sub_len);
	if (!sub)
		clean_data(dt, MALLOC_FAILURE);
	add_token(dt, DOUBLE, sub, is_expandable);
	if (input[*i] == '\"')
		(*i)++;
}

void	add_operator(t_data *dt, const char *input, int *i)
{
	char	*sub;

	sub = NULL;
	if (is_redir(&input[*i]))
	{
		if (!ft_strncmp(&input[*i], &input[*i + 1], 1))
		{
			sub = ft_substr(input, *i, 2);
			*i += 2;
		}
		else
		{
			sub = ft_substr(input, *i, 1);
			(*i)++;
		}
	}
	else
	{
		sub = ft_substr(input, *i, 1);
		(*i)++;
	}
	add_token(dt, OPERATOR, sub, false);
}

void	add_word(t_data *dt, const char *input, int *i)
{
	int		sub_len;
	int		start;
	char	*sub;
	bool	is_expandable;

	sub = NULL;
	start = *i;
	sub_len = 0;
	is_expandable = false;
	while (input[*i] && is_word(&input[*i]))
	{
		if (input[*i] == '$' && is_var(input[*i + 1]))
			is_expandable = true;
		(*i)++;
		sub_len++;
	}
	sub = ft_substr(input, start, sub_len);
	if (!sub)
		clean_data(dt, MALLOC_FAILURE);
	add_token(dt, WORD, sub, is_expandable);
}
