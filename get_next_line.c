/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:31:35 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/19 15:31:32 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include "get_next_line.h"

int	copy_nodes_to_str(struct s_Node **current_node_ptr, char *n_l)
{
	struct s_Node	*tmp;
	struct s_Node	*current_node;
	int				i;

	i = 0;
	current_node = *current_node_ptr;
	while (current_node->next)
	{
		ft_memcpy(n_l + i, current_node->data, ft_strlen(current_node->data));
		i += ft_strlen(current_node->data);
		tmp = current_node;
		current_node = current_node->next;
		free(tmp->data);
		free(tmp);
	}
	*current_node_ptr = current_node;
	return (i);
}

int	handle_last_node(struct s_Node **nd_ptr, char *new_line, int i)
{
	struct s_Node	*nd;
	int				j;

	j = 0;
	nd = *nd_ptr;
	while (nd->data[j] && nd->data[j] != '\n')
		new_line[i++] = nd->data[j++];
	if (nd->data[j] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	if (nd->data[j] && nd-> data[j + 1])
		*nd_ptr = append(NULL, nd->data + j + 1);
	else
		*nd_ptr = NULL;
	free(nd->data);
	free(nd);
	return (0);
}

/*next line string creation*/
char	*create_line(struct s_Node **list_ptr)
{
	struct s_Node	*current;
	char			*new_line;
	int				i;
	int				size;

	if ((*list_ptr) == NULL)
		return (NULL);
	current = *list_ptr;
	size = 0;
	while (current)
	{
		size += ft_strlen(current->data);
		current = current->next;
	}
	new_line = (char *)malloc((size + 1) * sizeof(char));
	i = copy_nodes_to_str(list_ptr, new_line);
	if (handle_last_node(list_ptr, new_line, i) == -1)
		return (NULL);
	return (new_line);
}

char	*read_until_newline(int fd, struct s_Node **list_ptr, char *buffer)
{
	int	num_chars;

	while (!ft_strchr(buffer, '\n'))
	{
		num_chars = read(fd, buffer, BUFFER_SIZE);
		buffer[num_chars] = '\0';
		if (num_chars <= 0)
		{
			free(buffer);
			return (create_line(list_ptr));
		}
		*list_ptr = append(*list_ptr, buffer);
		if (!*list_ptr)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (create_line(list_ptr));
}

char	*get_next_line(int fd)
{
	static struct s_Node	*list;
	struct s_Node			*current;
	char					*buffer;

	if (fd == -1)
		return (NULL);
	current = list;
	while (current && current->next)
		current = current->next;
	if (current && ft_strchr(current->data, '\n') != NULL)
		return (create_line(&list));
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
	{
		free(list);
		return (NULL);
	}
	buffer[0] = '\0';
	return (read_until_newline(fd, &list, buffer));
}
