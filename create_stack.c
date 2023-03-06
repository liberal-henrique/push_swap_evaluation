/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:56:40 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/03 19:38:45 by rasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_end(t_list **root, int value)
{
	t_list	*new_node;
	t_list	*curr;

	curr = *root;
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->x = value;
	if (*root == NULL)
	{
		*root = new_node;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

// void	insert_end(t_list **root, int value)
// {
// 	t_list	*new_node;
// 	t_list	*curr;

// 	curr = *root;
// 	new_node = malloc(sizeof(t_list));
// 	if (new_node == NULL)
// 		return ;
// 	new_node->next = NULL;
// 	new_node->x = value;
// 	if (*root == NULL)
// 	{
// 		new_node->next = *root;
// 		*root = new_node;
// 		return ;
// 	}
// 	if (curr->x == value)
// 		deallocate(root, 1);
// 	while (curr->next)
// 	{
// 		if (curr->x == value)
// 			deallocate(root, 1);
// 		curr = curr->next;
// 	}
// 	if (curr->x == value)
// 		deallocate(root, 1);
// 	curr->next = new_node;
// }