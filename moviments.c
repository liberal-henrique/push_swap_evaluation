/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:32:24 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/06 18:31:14 by rasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **a)
{
	t_list	*second;

	if (!*a)
		return ;
	second = (*a)->next;
	(*a)->next = second->next;
	second->next = *a;
	*a = second;
	printf("sa\n");
}

void	sb(t_list **b)
{
	t_list	*second;

	if (!*b)
		return ;
	second = (*b)->next;
	(*b)->next = second->next;
	second->next = *b;
	*b = second;
	printf("sb\n");
}

void	ss(t_list **a, t_list **b)
{
	sa(a);
	sb(b);
	printf("ss\n");
}

void	pa(t_list **a, t_list **b)
{
	t_list	*curr;

	if (!*b)
		return ;
	curr = *b;
	*b = curr->next;
	curr->next = *a;
	*a = curr;
	printf("pa\n");
}

void	pb(t_list **b, t_list **a)
{
	t_list	*curr;

	if (!*a)
		return ;
	curr = *a;
	*a = curr->next;
	curr->next = *b;
	*b = curr;
	printf("pb\n");
}

void	ra(t_list **a)
{
	t_list	*curr;
	t_list	*temp;

	if (!*a)
		return ;
	curr = *a;
	temp = *a;
	*a = curr->next;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = temp;
	temp->next = NULL;
	printf("ra\n");
}

void	rb(t_list **b)
{
	t_list	*curr;
	t_list	*temp;

	if (!*b)
		return ;
	curr = *b;
	temp = *b;
	*b = curr->next;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = temp;
	temp->next = NULL;
	printf("rb\n");
}

void	rr(t_list **a ,t_list **b)
{
	ra(a);
	rb(b);
	printf("rr\n");
}

void	rra(t_list **a)
{
	t_list	*curr;
	t_list	*before_last;

	curr = *a;
	before_last = *a;
	while (curr->next != NULL)
		curr = curr->next;
	while (before_last->next != curr)
		before_last = before_last->next;
	curr->next = *a;
	*a = curr;
	before_last->next = NULL;
	printf("rra\n");
}

void	rrb(t_list **b)
{
	t_list	*curr;
	t_list	*before_last;

	curr = *b;
	before_last = *b;
	while (curr->next != NULL)
		curr = curr->next;
	while (before_last->next != curr)
		before_last = before_last->next;
	curr->next = *b;
	*b = curr;
	before_last->next = NULL;
	printf("rrb\n");
}

void	rrr(t_list **a, t_list **b)
{
	rra(a);
	rrb(b);
	printf("rrr\n");
}
