/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjaber <sjaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:24:06 by sjaber            #+#    #+#             */
/*   Updated: 2025/08/05 15:27:15 by sjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_realloc(t_buffer *buffer, size_t new_capacity)
{
    if (!buffer || !buffer->data)
        return 0;
    if (new_capacity <= buffer->capacity)
        return 1; // No need to reallocate

    char *new_data = malloc(new_capacity);
    if (!new_data)
        return 0; 
    size_t i = 0;
    while (i < buffer->length)
    {
        new_data[i] = buffer->data[i];
        i++;
    }

    free(buffer->data);
    buffer->data = new_data;
    buffer->capacity = new_capacity;
    return 1;
}
