/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:24:06 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/05 15:27:15 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	is_empty(const char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (true);
	while (s[i])
	{
		if (!((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			return (false);
		i++;
	}
	return (true);
}

int	skip_whitesp(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	return (i);
}

bool	is_pipe(const char *token)
{
	return (!ft_strncmp(token, "|", 1));
}

bool	is_redir(const char *token)
{
	if (!ft_strncmp(token, ">>", 2))
		return (true);
	if (!ft_strncmp(token, "<<", 2))
		return (true);
	if (!ft_strncmp(token, ">", 1))
		return (true);
	if (!ft_strncmp(token, "<", 1))
		return (true);
	return (false);
}

bool	is_word(const char *token)
{
	if (is_pipe(token) || is_redir(token)
		|| token[0] == '\'' || token[0] == '\"'
		|| token[0] == ' ' || (token[0] >= 9 && token[0] <= 13))
		return (false);
	return (true);
}
