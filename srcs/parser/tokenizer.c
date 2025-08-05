/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:12:58 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/05 17:21:42 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_buffer(t_buffer *buffer, size_t initial_capacity)
{
        if(!buffer)
                return 0;
        if(initial_capacity == 0)
                initial_capacity = 32;
        buffer->data = malloc(initial_capacity);
        if(!buffer->data)
        {
                buffer->capacity = 0;
                buffer->length = 0;
                return 0;
        }
        buffer->capacity = initial_capacity;
        buffer->length = 0;
        return 1;
}

int buffer_append_char(t_buffer *buffer, char c)
{
    if(!buffer || !buffer->data)
        return 0;
    if(buffer->length + 1 >= buffer->capacity)
    {
        size_t new_capacity = buffer->capacity * 2;
        if (!ft_realloc(buffer, new_capacity))
            return 0;
    }
    buffer->data[buffer->length] = c;
    buffer->length++;
    return 1;
}

char *buffer_to_token(t_buffer *buffer)
{
    if (!buffer || !buffer->data || buffer->length == 0)
        return NULL;

    char *token = malloc(buffer->length + 1);
    if (!token)
        return NULL;

    size_t i = 0;
    while (i < buffer->length)
    {
        token[i] = buffer->data[i];
        i++;
    }
    token[buffer->length] = '\0';

    return token;
}

void buffer_reset(t_buffer *buffer)
{
    if (buffer && buffer->data)
    {
        buffer->length = 0;
    }
}
void buffer_free(t_buffer *buffer)
{
    if (buffer && buffer->data)
    {
        free(buffer->data);
        buffer->data = NULL;
        buffer->capacity = 0;
        buffer->length = 0;
    }
}