/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:37 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/06 19:08:08 by rasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		midpoint(t_list **a, int i)
{
	t_list	*temp;
	int	value;

	temp = clone_list(a);
	sort_list(&temp);
	i = i/2;
	while (i-- != 0 && temp->next != NULL)
		temp = temp->next;
	value = temp->x;
	deallocate(&temp, 0);
	return (value);
}

int	gv_i(t_list **a, int element)
{
	t_list	*temp;
	int		index_a;

	temp = (*a);
	index_a = 0;
	while (temp->next != NULL && element != temp->x) //FOI AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
	{
		index_a++;
		temp = temp->next;
	}
	return (index_a);
}

void	best_move(t_list **a, t_list **b, int start, int end)
{
	t_list	*temp;
	int	i;
	int	top;
	int	bottom;
	int flag;
	int	md_pnt;

	i = numero_movi(a, end);
	md_pnt = midpoint(a, i);
	while (*a && i != 0)
	{
		flag = 0;
		temp = (*a);
		while (temp->next != NULL)
		{
			if ((temp->x >= start && temp->x <= end) && flag == 0)
			{
				top = temp->x;
				flag = 1;
			}
			if (temp->x >= start && temp->x <= end)
				bottom = temp->x;
			temp = temp->next;
		}
		send_pb(a, b, gv_i(a, top), (cnt_rec(*a) - gv_i(a, bottom)), md_pnt);
		i--;
	}
}

int		sort_biggest_chunks_in_b(t_list **root)
{
	t_list	*last_value;
	t_list	*temp;
	int	biggest;

	last_value = (*root);
	temp = (*root);
	biggest = 0;
	while (last_value->next != NULL)
		last_value = last_value->next;
	while (temp->next != NULL)
	{
		if (temp->x < last_value->x)
			break;
		if (temp->x < temp->next->x)
			biggest = temp->next->x;
		temp = temp->next;
	}
	return (biggest);
}

int		i_last(t_list **root, int finish)
{
	t_list	*temp;
	int	index;

	temp = *root;
	index = 0;
	while (temp->next != NULL)
	{
		if (temp->x == finish)
			break;
		index++;
		temp = temp->next;
	}
	return (index);
}

int		i_first(t_list **root, int start)
{
	t_list	*temp;
	int	index;

	temp = *root;
	index = 0;
	while (temp->next != NULL)
	{
		if (temp->x == start)
			break;
		index++;
		temp = temp->next;
	}
	return (index);
}

int		md_chunk(t_list **root, int start, int finish)
{
	t_list	*temp;
	int		mid;
	int		result;

	temp = clone_list(root);
	sort_list(&temp);
	mid = (i_last(&temp, finish) - i_first(&temp, start)) / 2;
	while (temp->next != NULL)
	{
		if (temp->x == start)
			break;
		temp = temp->next;
	}
	while (mid-- != 0)
		temp = temp->next;
	result = temp->x;
	deallocate(&temp, 0);
	return (result);
}

int		top_small(t_list *b)
{
	t_list *temp;
	t_list *last;
	int	small;
	int	i;

	temp = b;
	last = b;
	while (last->next != NULL)
		last = last->next;
	small = temp->x ;
	i = 0;
	while (temp->x > last->x)
	{
		if (small > temp->x)
			small = temp->x;
		i++;
		temp = temp->next;
	}
	return (small);
}

int		bot_small(t_list *b)
{
	t_list *temp;
	int	small;

	temp = b;
	small = temp->x;
	while (temp->next != NULL)
	{
		if (small > temp->x)
			small = temp->x;
		temp = temp->next;
	}
	return (small);
}

int		top_big(t_list *b)
{
	t_list *temp;
	t_list *last;
	int	big;
	int	i;

	temp = b;
	last = b;
	while (last->next != NULL)
		last = last->next;
	big = temp->x;
	i = 0;
	while (temp->x > last->x)
	{
		if (big < temp->x)
			big = temp->x;
		temp = temp->next;
		i++;
	}
	return (big);
}

int		bot_big(t_list *b)
{
	t_list *temp;
	int	big;

	temp = b;
	big = temp->x;
	while (temp->next != NULL)
	{
		if (big < temp->x)
			big = temp->x;
		temp = temp->next;
	}
	return (big);
}

void	back_ra(t_list **a, int n_control)
{
	int	i;

	i = n_control;
	if (cnt_rec(*a) <= 2 && list_sorted(a))
		return ;
	while (n_control-- != 0)
		rra(a);
	if (i == 2 && !list_sorted(a))
		sa(a);
}

void	back_pb(t_list **a, t_list **b, int n_control)
{
	while (n_control-- != 0)
		pa(a, b);
}

int		find_biggest_chunks_in_a(t_list **root, int n_moviments)
{
	t_list	*temp;
	int		biggest;

	temp = (*root);
	biggest = temp->x;
	while ( --n_moviments > 0)
	{
		if (biggest < temp->next->x)
			biggest = temp->next->x;
		temp = temp->next;
	}
	return (biggest);
}

int		find_smallest_chunks_in_a(t_list **root)
{
	t_list	*temp;
	int		smallest;

	temp = *root;
	smallest = 0;
	while (temp->next != NULL)
	{
		if (temp->x > temp->next->x)
			smallest = temp->next->x;
		temp = temp->next;
	}
	return (smallest);
}

void	sort_a(t_list **a, t_list **b, int n_moviments)
{
	int	mid_pnt;
	int	ra_control;
	int	pb_control;

	ra_control = 0;
	pb_control = 0;
	if (list_sorted(a))
		return ;
	mid_pnt = md_chunk(a, find_smallest_chunks_in_a(a), find_biggest_chunks_in_a(a, n_moviments));
	while (n_moviments-- >= 1)
	{
		if ((*a)->x >= mid_pnt && ++ra_control)
			ra(a);
		else if ((*a)->x < mid_pnt && ++pb_control)
			pb(b, a);
	}
	back_ra(a, ra_control);
	if (!(list_sorted(a)))
		sort_a(a, b, ra_control);
	back_pb(a, b, pb_control);
	if (!(list_sorted(a)))
		sort_a(a, b, pb_control);
}

void	sort_back(t_list **a, t_list **b, int i, int n)
{
	sort_a(a, b, i);
	i = n;
	while (n-- != 0)
		pa(a ,b);
	sort_a(a, b, i);
}

void	printList(t_list *root)
{
	t_list	*curr;

	curr = root;
	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			printf("[*][%ld]", (long int)curr->x);
			break ;
		}
		printf("[*][%ld]->", (long int)curr->x);
		curr = curr->next;
	}
}

t_list	*find_last(t_list **b)
{
	t_list	*temp;
	t_list	*last;
	int		iterate;
	int		n;

	temp = (*b);
	last = (*b);
	iterate = 0;
	n = 0;
	while (last->next != NULL)
	{
		last = last->next;
		iterate++;
		if (last->x > (*b)->x)
			n++;
		else
			n = 0;
	}
	while (temp->next != NULL && iterate-- >= n)
		temp = temp->next;
	return (temp);
}

void	send_bot_b(t_list **a, t_list **b)
{
	t_mid	usable;

	usable.temp = *b;
	usable.last = find_last(b);
	usable.md_pnt = md_chunk(b, bot_small(usable.last), bot_big(usable.last));
	usable.n = 0;
	usable.i = 0;
	while (usable.temp->x != usable.last->x)
	{
		usable.temp = *b;
		while (usable.temp->next != NULL)
			usable.temp = usable.temp->next;
		rrb(b);
		if ((*b)->x >= usable.md_pnt && ++usable.i)
			pa(a, b);
		else
			usable.n++;
	}
	sort_back(a, b, usable.i, usable.n);
}

void	send_top_b(t_list **a, t_list **b)
{
	t_list *last;
	int	i;
	int	n;
	int	md_pnt;

	last = *b;
	while (last->next != NULL)
		last = last->next;
	md_pnt = md_chunk(b, top_small(*b), top_big(*b));
	i = 0;
	n = 0;
	while ((*b)->x > last->x)
	{
		if ((*b)->x >= md_pnt && ++i)
			pa(a, b);
		else if ((*b)->x < md_pnt && ++n)
			rb(b);
	}
	sort_a(a, b, i);
	i = n;
	while (n-- != 0)
	{
		rrb(b);
		pa(a, b);
	}
	sort_a(a, b, i);
}

void	send_rest2(t_list **a, t_list **b)
{
	t_list *last;
	int	md_pnt;
	int	small;
	int	big;
	int	i;
	int	n; 

	last = *b;
	small = last->x;
	big = last->x;
	n = 0;
	i = 0;
	while (last->next != NULL)
	{
		if (small > last->x)
			small = last->x;
		if (big < last->x)
			big = last->x;
		last = last->next;
	}
	md_pnt = md_chunk(b, small, big);
	while ((*b)->x != last->x)
	{
		if ((*b)->x >= md_pnt)
		{
			pa(a, b);
			n++;
		}
		else if ((*b)->x < md_pnt)
		{
			rb(b);
			i++;
		}
	}
	sort_a(a, b, n);
	while ((*b) != NULL)
	{
		pa(a, b);
		i++;
	}
	sort_a(a, b, i);
}

void	send_rest(t_list **a, t_list **b)
{
	t_list *last;
	int	md_pnt;
	int	small;
	int	big;
	int	i;
	int	n;
	int	flag;

	last = *b;
	small = last->x;
	big = last->x;
	n = 0;
	i = 0;
	while (last->next != NULL)
	{
		if (small > last->x)
			small = last->x;
		if (big < last->x)
			big = last->x;
		last = last->next;
	}
	md_pnt = md_chunk(b, small, big);
	while (flag == 0)
	{
		if ((*b)->x == last->x)
			flag = 1;
		if ((*b)->x > md_pnt)
		{
			pa(a, b);
			i++;
		}
		else if ((*b)->x <= md_pnt)
		{
			rb(b);
			n++;
		}
	}
	sort_a(a, b, i);
	i = n;
	while (n != 0)
	{
		pa(a, b);
		n--;
	}
	sort_a(a, b, i);
}

void	sort_biggest(t_list **a, t_list **b)
{
	t_list	*temp;

	while (cnt_rec(*a) != 0)
		best_move(a, b, start(a), end(a));
	while (cnt_rec(*b) > 30)
	{
		temp = (*b);
		while (temp->next != NULL)
			temp = temp->next;
		if ((*b)->x > temp->x)
			send_top_b(a, b);
		else if ((*b)->x < temp->x)
			send_bot_b(a, b);
	}
	send_rest(a, b);
}

void	sort_biggest2(t_list **a, t_list **b)
{
	t_list	*temp;
	int	i;

	while (cnt_rec(*a) != 0)
		best_move(a, b, start(a), end(a));
	while (cnt_rec(*b) > 15)
	{
		temp = (*b);
		while (temp->next != NULL)
			temp = temp->next;
		i = 0;
		while ((*b)->x > temp->x)
		{
			pa(a, b);
			i++;
		}
		sort_a(a, b, i);
		i = 0;
		while ((*b)->x < temp->x)
		{
			rrb(b);
			pa(a, b);
			i++;
			temp = (*b);
			while (temp->next != NULL)
				temp = temp->next;
		}
		sort_a(a, b, i);
	}

	printf("%i\n", cnt_rec(*b));
	printList(*a);
	printf("\n");
	printList(*b);
	//send_rest(a, b);
}
