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
int	main(int ac, char **av, char **envp)
{
	t_env	env;
	char	*input;

	(void)ac;
	(void)av;
	init_env(&env, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!ft_strncmp(input, "export", 6))
			print_export(&env);
		else if (!ft_strncmp(input, "env", 3))
			print_env(&env);
	}
	clean_env(&env, env.entries, 0);
	return (0);
}
