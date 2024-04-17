/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:31:35 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/15 15:43:32 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "get_next_line.h"

struct Node
{
	char *data;
	struct Node* next;
};
/* I add new node to the existing list */
void append(struct Node* head, char *str)
{
	struct Node	*new_node;
	struct Node	*current_node;

	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
		return;
	current_node = head;
	while (current_node->next != NULL) {
		current_node = current_node->next;
	}
	new_node->data = ft_strdup(str);
	new_node->next = NULL;
	current_node->next = new_node;
}
/* Memory allocation for next line string*/
char	*mem_alloc(struct Node *head)
{
	struct Node	*current_node;
	int		len;
	int		i;
	char		*new_line;

	if (head == NULL)
		return (NULL);
	current_node = head;
	len = 0;
	while(current_node->next)
	{
		len += ft_strlen(current_node->data);
		current_node = current_node->next;
	}
	i = 0;
	while(current_node->data[i] != '\n' && current_node->data[i]) {
		i++;
	}
	len = len + i;
	new_line = (char *)malloc((len + 2) * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
/*next line string creation*/
char	*create_line(struct Node **list)
{
	char	*new_line;
	struct Node	*current_node;
	int	i;
	int	j;
	struct Node	*new_node;
	struct Node	*tmp;
	if ((*list) == NULL) {
		return NULL;
	}
	i = 0;
       	new_line = mem_alloc(*list);
	current_node = *list;
	while (current_node->next)
	{
		ft_memcpy(new_line + i, current_node->data, ft_strlen(current_node->data));
		i += ft_strlen(current_node->data);
		tmp = current_node;
		current_node = current_node->next;
		free(tmp->data);
		free(tmp);
	}
	j = 0;
	while(current_node->data[j] && current_node->data[j] != '\n')
	{
		new_line[i] = current_node->data[j];
		j++;
		i++;
	}
	if (current_node->data[j] == '\n') {
		new_line[i] = '\n';
		i++;
	}
	new_line[i] = '\0';
	if (current_node->data[j]) {
		new_node = (struct Node*)malloc(sizeof(struct Node));
		if (new_node == NULL)
			return (NULL);
		new_node->data = ft_strdup(current_node->data + j + 1);
		new_node->next = NULL;
		*list = new_node;
	}
	else 
	{
		*list = NULL;
	}
	free(current_node->data);
	free(current_node);

	
	return (new_line);
}

int last_node_has_newline(struct Node* list)
{
	struct Node	*current;
	current = list;
	if (!current)
	{
		return 0;
	}
	while (current->next)
	{
		current = current->next;	
	}
	return ft_strchr(current->data, '\n') != NULL;
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int		num_chars;
	static struct Node	*list;
	if (fd == -1) {
		return NULL;
	}

	if (!last_node_has_newline(list)) 
	{
		buffer = (char *)malloc((BUFFER_SIZE) * sizeof(char));
		if (buffer == NULL) {
			free(list);
			return (NULL);
		}
		num_chars = read(fd, buffer, BUFFER_SIZE);
		if (num_chars <= 0) {
			free(buffer);
			return create_line(&list);
		}
		char * buf2;
		buf2 = (char*)malloc(num_chars + 1);
		ft_memcpy(buf2, buffer, num_chars);
		buf2[num_chars] = '\0';

		if (!list)
		{
			list = (struct Node*)malloc(sizeof(struct Node));
			if (list == NULL)
			{
				free(buffer);
				return (NULL);
			}
			list->data = ft_strdup(buf2);
			list->next = NULL;
		}
		else
		{
			append(list, buf2);
		}
		while (!ft_strchr(buf2, '\n'))
		{
			free(buf2);
			num_chars = read(fd, buffer, BUFFER_SIZE);
			buf2 = (char*)malloc(num_chars + 1);
			ft_memcpy(buf2, buffer, num_chars);
			buf2[num_chars] = '\0';
			if (!num_chars) {
				free(buffer);
				free(buf2);
				return (create_line(&list));
			}
			append(list, buf2);
		}
		free(buf2);
		free(buffer);
	}
	return (create_line(&list));
}
