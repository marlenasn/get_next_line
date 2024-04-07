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
		return (NULL);
	while (current_node->next != NULL)
		current_node = current_node->next;
	new_node->data = str;
	new_node->next = NULL;
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int		num_chars;
	struct Node	*list;

	list = (struct Node*)malloc(sizeof(struct Node));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	num_chars = read(fd, buffer, BUFFER_SIZE);
	buffer(num_chars) = '\0';
	list->data = buffer;
	list->next = NULL;
	while (!ft_strchr(buffer, '\n'))
	{
        	num_chars = read(fd, buffer, BUFFER_SIZE);
        	buffer(num_chars) = '\0';
		append(list, buffer);
	}
	return (create_line(list));
}

