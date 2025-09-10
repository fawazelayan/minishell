/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:04:21 by felayan           #+#    #+#             */
/*   Updated: 2025/09/02 23:04:22 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

void	clean_tokens(t_tokenizer *tokens)
{
	t_tokenizer	*current;

	current = tokens;
	while (current)
	{
		current = tokens -> next;
		free(tokens -> token);
		free(tokens);
		tokens = current;
	}
}

void	clean_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		wrds;
	int		rdrs;

	while (cmd)
	{
		tmp = cmd -> next;
		wrds = cmd -> word_count;
		rdrs = cmd -> redir_count;
		while (wrds--)
			free(cmd -> tokens[wrds]);
		while (rdrs--)
			free(cmd -> redir[rdrs].file);
		free(cmd -> tokens);
		free(cmd -> redir);
		free(cmd);
		cmd = tmp;
	}
}

void	clean_data(t_data *dt, int status)
{
	clean_env(&dt -> env, dt -> env.entries, SUCCESS);
	clean_tokens(dt -> tokens);
	clean_cmds(dt -> cmds);
	dt -> tokens = NULL;
	dt -> cmds = NULL;
	if (status != SUCCESS)
		exit(status);
}
