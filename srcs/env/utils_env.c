/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:10:19 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:10:20 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	int	i;

	i = 0;
	while (env->key[i])
	{
		if (!ft_strcmp(env->key[i], key))
			return (env->value[i]);
		i++;
	}
	return ("");
}

void	print_env(const t_env *env)
{
	int	i;

	i = 0;
	while (env -> key[i])
	{
		if (env -> value[i] != NULL)
			printf("%s=%s\n", env->key[i], env->value[i]);
		i++;
	}
}

void	print_export(const t_env *env)
{
	int	i;

	i = 0;
	while (env -> key[i])
	{
		printf("declare -x %s", env -> key[i]);
		if (env -> value[i] != NULL)
			printf("=\"%s\"", env -> value[i]);
		printf("\n");
		i++;
	}
}
