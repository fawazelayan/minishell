/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:46:14 by felayan           #+#    #+#             */
/*   Updated: 2025/07/01 20:48:00 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

// int	main(int ac, char **av, char **envp)
// {
// 	t_data data;

// 	(void)ac;
// 	(void)av;
// 	ft_memset(&data, 0, sizeof(data));
// 	start_shell(&data, envp);
// 	clean_shell(&data, 0);
// }

// THIS IS A TEST MAIN ONLY TO TEST IF ENV WORKS RIGHT, THE REAL MAIN IS ABOVE
void	handle_sigint(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	char	*input;
	t_data	data;
	ft_memset(&data, 0, sizeof(data));
	(void)ac;
	(void)av;
	init_env(&env, envp);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!(input[0] == '\0' || is_empty(input)))
			add_history(input);
		//tokenizer(input, &data);
		if (!ft_strncmp(input, "export", 6))
			print_export(&env);
		else if (!ft_strncmp(input, "env", 3))
			print_env(&env);
		free(input);
	}
	clean_env(&env, env.entries, 0);
	return (0);
}
