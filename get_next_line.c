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
#define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

#include "get_next_line.h"


int	copy_nodes_to_str(struct Node **current_node_ptr, char *new_line)
{
	int		i;
	struct Node	*tmp;
	struct Node	*current_node;

	i = 0;
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

	j = 0;
	current_node = *current_node_ptr;
	while(current_node->data[j] && current_node->data[j] != '\n')
		new_line[i++] = current_node->data[j++];
	if (current_node->data[j] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	if (current_node->data[j])
		*current_node_ptr = append(NULL, current_node->data + j + 1);
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
	struct Node* current;
	int size;
	if ((*list_ptr) == NULL)
		return NULL;

	current = *list_ptr;
	size = 0;

	while (current) {
		size += ft_strlen(current->data);
		current = current->next;
	}
	new_line = (char*)malloc((size + 1) * sizeof(char));
	
	i = copy_nodes_to_str(list_ptr, new_line);
	if (handle_last_node(list_ptr, new_line, i) == -1)
		return (NULL);

	return (new_line);
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
	struct Node	*current;

	if (fd == -1)
		return (NULL);
	current = list;
	while (current && current->next)
		current = current->next;
	if (current && ft_strchr(current->data, '\n') != NULL)
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
