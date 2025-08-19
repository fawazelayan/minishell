#include "minishell.h"

// void	start_shell(t_data *dt, char **envp)
// {
// 	char	*line;

// 	init_env(&dt -> env, envp);
// 	while (42)
// 	{
// 		dt -> cmd_count = 0;
// 		line = readline("forking-hell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (!is_empty(line))
// 			add_history(line);
// 		if (!is_empty(line) && !tokenizer(line, dt))    FAWAz: removed & from dt
// 			executioner(dt);
// 		free_cmds(dt -> cmd);
// 		free_tokens(dt -> input_tokens);
// 		free(line);
// 	}
// }
