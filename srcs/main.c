/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:46:14 by felayan           #+#    #+#             */
/*   Updated: 2025/09/03 00:00:00 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

// THIS IS JUST FOR PRINTING TOKENS FOR DEBUGGING WILL REMOVE LATER
void	print_tokens(t_tokenizer *tokens)
{
	while (tokens)
	{
		printf("%s %d %d\n", tokens -> token, tokens -> token_type, tokens -> is_expandable);
		tokens = tokens -> next;
	}
}

// THIS IS JUST FOR PRINTING CMDS FOR DEBUGGING WILL REMOVE LATER
void	print_cmds(t_cmd *cmd)
{
	int			i;
	const char	*redir_symbols[] = {"<<", ">>", ">", "<"};

	while (cmd)
	{
		i = 0;
		while (i < cmd -> word_count)
			printf("%s ", cmd -> tokens[i++]);
		printf("\n");
		i = 0;
		while (i < cmd -> redir_count)
		{
			printf("%s %s ", redir_symbols[cmd->redir[i].type], cmd -> redir[i].file);
			i++;
		}
		printf("\n");
		cmd = cmd -> next;
	}
}

// THIS IS FOR SIGINT TESTING WILL DO LATER
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
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	ft_memset(&data, 0, sizeof(data));
	start_shell(&data, &line, envp);
	clean_data(&data, SUCCESS);
}
