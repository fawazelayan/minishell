#include "minishell.h"

// void	start_shell(t_data *dt, char **envp)
// {
// 	char	*line;

// 	init_env(&dt -> env, envp);
// 	while (42)
// 	{
// 		line = readline("mini-hell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*line)
// 			add_history(line);
// 		if (tokenizer(line, &dt)) // Sara
// 			executioner(&dt); // Fawaz
// 		free_parse_tokens(&dt -> parse_tokens);
// 		free(line);
// 	}
// }
