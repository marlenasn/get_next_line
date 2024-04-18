/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:41:57 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/15 12:42:00 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	else
		return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

/* I add new node to the existing list */
struct Node* append(struct Node* head, char *str)
{
	struct Node	*new_node;
	struct Node	*current_node;

	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL) 
		return (NULL);
	new_node->data = (char*)malloc(ft_strlen(str) + 1);
	ft_memcpy(new_node->data, str, ft_strlen(str) + 1);
	new_node->next = NULL;
	if (head == NULL)
		return (new_node);
	current_node = head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
	return (head);
}
