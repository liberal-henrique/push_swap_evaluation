/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:41:11 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/06 18:51:29 by rasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	deallocate(t_list **root, int message)
{
	t_list	*temp;

	while (*root)
	{
		temp = (*root)->next;
		free(*root);
		*root = temp;
	}
	root = NULL;
	if (message == 1)
		exit (write(1, "Error\n", 6));
}

void	sort_list(t_list **a)
{
	t_list	*current;
	t_list	*index;
	int temp;

	temp = 0;
	index = NULL;
	current = *a;
	if(*a == NULL)
		return ;
	else {
		while(current != NULL) {
			index = current->next;
			while(index != NULL) {
				if(current->x > index->x) {
					temp = current->x;
					current->x = index->x;
					index->x = temp;
				}
				index = index->next;
			}
			current = current->next;
		}
	}
}

int	list_sorted(t_list **root)
{
	t_list	*curr;

	curr = *root;
	while (curr->next)
	{
		if (curr->x > curr->next->x)
			return (0);
		curr = curr->next;
	}
	return (1);
}

t_list* clone_list(t_list **head)
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*prev;
	t_list	*current;

	prev = NULL;
	new_list = NULL;
	current = *head;
	while (current != NULL)
	{
		new_node = malloc(sizeof(t_list));
		new_node->x = current->x;
		new_node->next = NULL;
		if (prev != NULL) {
			prev->next = new_node;
		} else {
			new_list = new_node;
		}
		prev = new_node;
		current = current->next;
	}
	return (new_list);
}

int	cnt_rec(t_list *node)
{
	if (node == NULL)
		return (0);
	return (1 + cnt_rec(node->next));
}