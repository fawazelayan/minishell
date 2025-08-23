#include "minishell.h"

void	clean_data(t_data *dt, int status)
{
	clean_env(&dt -> env, dt -> env.entries, SUCCESS);
	clean_tokens(dt -> tokens);
	if (status != SUCCESS)
		exit(status);
}
