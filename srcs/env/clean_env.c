#include "minishell.h"

void	clean_env(t_env *env, int count, int exit_status)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(env -> key[i]);
		free(env -> value[i]);
		i++;
	}
	free(env -> key);
	free(env -> value);
	env -> key = NULL;
	env -> value = NULL;
	if (exit_status != 0)
		exit(exit_status);
}
