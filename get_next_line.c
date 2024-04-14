/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:31:35 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/07 19:57:48 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
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

void append(struct Node* head, char *str)
{
	struct Node	*new_node;
	struct Node	*current_node;

	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
		return;
	current_node = head;
	while (current_node->next != NULL)
		current_node = current_node->next;
	new_node->data = str;
	new_node->next = NULL;
	current_node->next = new_node;
}

char	*mem_alloc(struct Node *head)
{
	struct Node	*current_node;
	int		len;
	int		i;
	char		*new_line;

	// printf("head: %d\n", head);
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
	new_line = (char *)malloc((len + 1) * sizeof(char));
	printf("len: %d\n", len);
	return (new_line);
}

char	*create_line(struct Node *list)
{
	char	*new_line;
	struct Node	*current_node;
	struct Node	*tmp;
	int	i;
	int	j;
	struct Node	*new_node;
	i = 0;
       	new_line = mem_alloc(list);
	current_node = list;
	// printf("before create_line while\n");
	// printf("%d\n", current_node);
	while (current_node->next)
	{
		ft_memcpy(new_line + i, current_node->data, ft_strlen(current_node->data));
		// free(current_node->data); 
		i += ft_strlen(current_node->data);
		// tmp = current_node;
		current_node = current_node->next;
		// free(tmp);
		// printf("new line dla i: %s dla %d\n", new_line, i);
	}
	// printf("after create_line while\n");
	j = 0;
	// '\n' is in the last node
	while(current_node->data[j] && current_node->data[j] != '\n')
	{
		new_line[i] = current_node->data[j];
		j++;
		i++;
		// printf("new line dla i: %s dla %d\n", new_line, i);
	}
	new_line[i] = 0;
	// printf("after current_node while\n");

	new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
		return (NULL);


	new_node->data = ft_strdup(current_node->data + j + 1);
	new_node->next = NULL;

	//printf("new_line: %s\n", new_line);

	// free(current_node->data);
	// free(current_node);

	*list = *new_node;
	
	return (new_line);
}

int any_node_has_newline(struct Node* list)
{
	struct Node	*current;
	char	*res;
	current = list;
	if (!current)
	{
		return 0;
	}
	res = ft_strchr(current->data, '\n');
	if (!res)
	{
		return 0;
	}
	//printf("current %p\n", current);
	//printf("current data %s\n", current->data);
	while (current->next)
	{
		res = ft_strchr(current->data, '\n');
		if (!res)
		{
			return 0;
		}
		current = current->next;	
	}
	return 1;
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int		num_chars;
	static struct Node	*list;
	
	//printf("GET NEXT LINE %p\n", list);

	if (!any_node_has_newline(list)) {
		//printf("last node has newline = false\n");
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return (NULL);
		num_chars = read(fd, buffer, BUFFER_SIZE);
		buffer[num_chars] = '\0';
		//printf("num_chars: %d\n", num_chars);
		//printf("buffer: %s\n", buffer);

		if (!list)
		{
			//printf("!list\n");
			list = (struct Node*)malloc(sizeof(struct Node));
			list->data = buffer;
			list->next = NULL;
		}
		else
		{
			//printf("append\n");
			append(list, buffer);
		}
		//printf("before while\n");
		while (!ft_strchr(buffer, '\n'))
		{
			//printf("in while\n");
			num_chars = read(fd, buffer, BUFFER_SIZE);
			buffer[num_chars] = '\0';
			append(list, buffer);
			//printf("num_chars: %d\n", num_chars);
			//printf("buffer: %s\n", buffer);
		}
	}
	else
	{
		//printf("last node has newline = true\n");
	}
	return (create_line(list));

}

