/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:36:16 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:36:16 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	start_shell(t_data *data, char **line, char **envp)
{
	init_env(&data -> env, envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		data -> cmd_count = 0;
		*line = readline("minishell$ ");
		if (!*line)
		{
			printf("exit\n");
			break ;
		}
		if (!(*line[0] == '\0' || is_empty(*line)))
		{
			add_history(*line);
			if (tokenizer(*line, data) != -1)
			{
				expander(data);
				print_tokens(data -> tokens);
			}
			clean_tokens(data ->tokens);
			data -> tokens = NULL;
		}
		free(*line);
	}
}
