#include "minishell.h"

t_tokenizer	*get_last_token(t_tokenizer *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens -> next)
		tokens = tokens -> next;
	return (tokens);
}

void	add_token(t_data *dt, t_tk t_type, t_qt q_type, char *token, bool exp)
{
	t_tokenizer	*new;
	t_tokenizer	*last;

	new = malloc(sizeof(t_tokenizer));
	if (!new)
		clean_data(dt, MALLOC_FAILURE);
	new -> token = token;
	new -> token_type = t_type;
	new -> quote_type = q_type;
	new -> is_expandable = exp;
	new -> next = NULL;
	if (!dt -> tokens)
		dt -> tokens = new;
	else
	{
		last = get_last_token(dt -> tokens);
		last -> next = new;
	}
}

void	print_tokens(t_tokenizer *tokens)
{
	while (tokens)
	{
		printf("%s %d %d %d\n", tokens -> token, tokens -> quote_type, tokens -> token_type, tokens -> is_expandable);
		tokens = tokens -> next;
	}
}
void	clean_tokens(t_tokenizer *tokens)
{
	t_tokenizer *current = tokens;
	while (current)
	{
		current = tokens -> next;
		free(tokens -> token);
		free(tokens);
		tokens = current;
	}
}