/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:55:02 by iaskour           #+#    #+#             */
/*   Updated: 2025/04/23 09:41:29 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void gc_clear(t_gc *gc, int is_token) 
{
    t_gc_node *curr = gc->head;
    t_gc_node *prev = NULL;
    t_gc_node *next = NULL;
    
    while (curr) 
    {
        next = curr->next;
        if (curr->is_token == is_token) 
        {
            if (prev)
                prev->next = next;
            else
                gc->head = next;
            if (curr->ptr) {
                free(curr->ptr);
                curr->ptr = NULL;
            }
            free(curr);
        } 
        else 
            prev = curr;
        curr = next;
    }
}

