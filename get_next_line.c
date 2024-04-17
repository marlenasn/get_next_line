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
#define BUFFER_SIZE 1
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
struct Node* append(struct Node* head, char *str)
{
	struct Node	*new_node;
	struct Node	*current_node;

	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL) 
		return (NULL);
	new_node->data = ft_strdup(str);
	new_node->next = NULL;
	if (head == NULL)
		return (new_node);
	current_node = head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	current_node->next = new_node;
	return (head);
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
	while(current_node->data[i] != '\n' && current_node->data[i])
		i++;
	len = len + i;
	new_line = (char *)malloc((len + 2) * sizeof(char));
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}

int copy_nodes_to_str(struct Node** current_node_ptr, char* new_line)
{
	int i;
	struct Node	*tmp;

	i = 0;

	struct Node * current_node;

	current_node = *current_node_ptr;

	while (current_node->next)
	{
		ft_memcpy(new_line + i, current_node->data, ft_strlen(current_node->data));
		i += ft_strlen(current_node->data);
		tmp = current_node;
		current_node = current_node->next;
		free(tmp->data);
		free(tmp);
	}
	*current_node_ptr = current_node;
	return (i);
}


int handle_last_node(struct Node** current_node_ptr, char* new_line, int i)
{
	int j;
	struct Node * current_node;
	struct Node	*new_node;

	j = 0;
	current_node = *current_node_ptr;

	while(current_node->data[j] && current_node->data[j] != '\n')
		new_line[i++] = current_node->data[j++];
	if (current_node->data[j] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	if (current_node->data[j])
	{
		new_node = (struct Node*)malloc(sizeof(struct Node));
		if (new_node == NULL)
			return (-1);
		new_node->data = ft_strdup(current_node->data + j + 1);
		new_node->next = NULL;
		*current_node_ptr = new_node;
	}
	else 
		*current_node_ptr = NULL;
	free(current_node->data);
	free(current_node);	
	return 0;
}


/*next line string creation*/
char	*create_line(struct Node **list_ptr)
{
	char	*new_line;
	int	i;
	if ((*list_ptr) == NULL)
		return NULL;
       	new_line = mem_alloc(*list_ptr);
	i = copy_nodes_to_str(list_ptr, new_line);
	if (handle_last_node(list_ptr, new_line, i) == -1)
	{
		return (NULL);
	}

	return (new_line);
}

int last_node_has_newline(struct Node* list)
{
	struct Node	*current;
	current = list;
	if (!current)
		return (0);
	while (current->next)
		current = current->next;
	return (ft_strchr(current->data, '\n') != NULL);
}

char * read_until_newline(int fd, struct Node ** list_ptr, char * buffer) 
{
	int num_chars;

	while (!ft_strchr(buffer, '\n'))
	{
		num_chars = read(fd, buffer, BUFFER_SIZE);
		buffer[num_chars] = '\0';

		if (num_chars <= 0) 
		{
			free(buffer);
			return create_line(list_ptr);
		}
		*list_ptr = append(*list_ptr, buffer);
		if (!*list_ptr)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return create_line(list_ptr);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static struct Node	*list;
	if (fd == -1)
		return (NULL);
	if (last_node_has_newline(list)) 
		return create_line(&list);

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL) 
	{
		free(list);
		return (NULL);
	}
	buffer[0] = '\0';


	return read_until_newline(fd, &list, buffer);
}
