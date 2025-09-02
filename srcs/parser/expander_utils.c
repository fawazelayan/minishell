/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:06:27 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:06:28 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	is_var(char var)
{
	if (ft_isalnum(var) || var == '_' || var == '?')
		return (true);
	return (false);
}

char	*append_char(char *s, char c)
{
	char	*appended;
	int		len;

	if (!s)
	{
		appended = malloc(2);
		if (!appended)
			return (NULL);
		appended[0] = c;
		appended[1] = '\0';
		return (appended);
	}
	len = ft_strlen(s);
	appended = malloc(len + 2);
	if (!appended)
	{
		free(s);
		return (NULL);
	}
	ft_memcpy(appended, s, len);
	appended[len++] = c;
	appended[len] = '\0';
	free(s);
	return (appended);
}

char	*append_str(t_env *env, char *s1, const char *s2, bool is_special)
{
	char	*val;
	char	*appended;

	if (is_special)
	{
		appended = ft_strjoin(s1, s2);
		if (!appended)
		{
			free(s1);
			return (NULL);
		}
	}
	else
	{
		val = get_env_value(env, s2);
		appended = ft_strjoin(s1, val);
		if (!appended)
		{
			free(s1);
			return (NULL);
		}
	}
	free(s1);
	return (appended);
}

int	crt_var(t_env *env, char **expanded, char *key, bool is_special)
{
	if (!key)
	{
		free (*expanded);
		return (MALLOC_FAILURE);
	}
	*expanded = append_str(env, *expanded, key, is_special);
	free(key);
	if (!*expanded)
		return (MALLOC_FAILURE);
	return (0);
}
