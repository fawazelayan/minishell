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

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline("mini-hell$ ");
		if (!input) // Ctrl+D
			break;
		if (*input)
			add_history(input);

		printf("You typed: %s\n", input);
		free(input);
	}
	rl_clear_history();
	printf("exit\n");
	return (0);
}
