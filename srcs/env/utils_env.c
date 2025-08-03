#include "minishell.h"

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
