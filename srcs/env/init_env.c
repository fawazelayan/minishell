#include "minishell.h"

static int	count_env_entries(char **envp)
{
	int	entries;

	entries = 0;
	while (envp[entries])
		entries++;
	return (entries);
}

static int	split_env(char *envp_line)
{
	int	i;

	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
		i++;
	return (i);
}

static void	copy_env(t_env *env, char **envp)
{
	int		i;
	int		splitted;

	i = 0;
	while (i < env -> entries)
	{
		splitted = split_env(envp[i]);
		env -> key[i] = malloc(splitted + 1);
		if (!env -> key[i])
			clean_env(env, i, MALLOC_FAILURE);
		ft_strlcpy(env -> key[i], envp[i], splitted + 1);
		env -> value[i] = ft_strdup(envp[i] + splitted + 1);
		if (!env -> value[i])
			clean_env(env, i, MALLOC_FAILURE);
		i++;
	}
	env -> key[i] = NULL;
	env -> value[i] = NULL;
}

void	init_env(t_env *env, char **envp)
{
	env -> entries = count_env_entries(envp);
	env -> key = malloc(sizeof(char *) * (env -> entries + 1));
	env -> value = malloc(sizeof(char *) * (env -> entries + 1));
	if (!env -> key || !env -> value)
		clean_env(env, 0, MALLOC_FAILURE);
	copy_env(env, envp);
}
