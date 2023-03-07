/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:32:37 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/07 19:02:52 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	midpoint(t_list **a, int i)
{
	t_list	*temp;
	t_list	*clone;
	int		value;

	clone = clone_list(a);
	temp = clone;
	sort_list(&temp);
	i = i/2;
	while (i-- != 0 && temp->next != NULL)
		temp = temp->next;
	value = temp->x;
	deallocate(&clone, 0);
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
	t_list	*clone;
	int		mid;
	int		result;

	clone = clone_list(root);
	temp = clone;
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
	deallocate(&clone, 0);
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
	if (list_sorted(a))
		return ;
	while (n_control-- != 0 && !list_sorted(a))
		rra(a);
	if (i == 2 && !list_sorted(a))
		sa(a);
}

void	back_pb(t_list **a, t_list **b, int n_control)
{
	int	i;

	while (n_control-- != 0)
	{
		i = (*b)->x;
		if (i > (*a)->x)
		{
			pa(a, b);
			sa(a);
		}
		else
			pa(a, b);
	}
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

int	n_midpoint(t_list **b, int midpoint, int end)
{
	t_list	*temp;
	t_list	*clone;
	int		i;

	clone = clone_list(b);
	temp = clone;
	sort_list(&temp);
	i = 1;
	while (temp->next != NULL && temp->x != midpoint)
		temp = temp->next;
	while (temp->next != NULL && temp->x != end)
	{
		i++;
		temp = temp->next;
	}
	deallocate(&clone, 0);
	return (i);
}

void	sort_back_rest(t_list **a, t_list **b, int i, int n)
{
	back_ra(a, i);
	if (!(list_sorted(a)))
		sort_a(a, b, i);
	back_pb(a, b, n);
	if (!(list_sorted(a)))
		sort_a(a, b, n);
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
	while (n_moviments-- > 0)
	{
		if ((*a)->x >= mid_pnt && !list_sorted(a))
		{
			ra(a);
			ra_control++;
		}
		else if ((*a)->x < mid_pnt)
		{
			pb(b, a);
			pb_control++;
		}
	}
	sort_back_rest(a, b, ra_control, pb_control);
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

//	tentei refatorar esse funcao separando-a em mais funcoes.
//Contudo, estive 2 horas a ter segmentation fault. Todas as
//minhas tentativas de separar big e small em outras funcoes
//retornaram erro e os testes nao foram claros.

void	rest(t_list **a, t_list **b, int i)
{
	int n;

	n = 0;
	sort_a(a, b, i);
	n = cnt_rec(*b);
	while (cnt_rec(*b) > 0)
		pa(a, b);
	sort_a(a, b, n);
}



void	send_rest(t_list **a, t_list **b)
{
	t_list *last;
	int	md_pnt;
	int	small;
	int	big;
	int	i;

	last = *b;
	small = last->x;
	big = last->x;
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
	small = n_midpoint(b, md_pnt, big);
	while (small != 0)
	{
		if ((*b)->x >= md_pnt)
		{
			pa(a, b);
			small--;
			i++;
			if (cnt_rec(*a) > 1 && (*a)->x > (*a)->next->x && (*a)->x != big)
				sa(a);
		}
		else if ((*b)->x < md_pnt)
			rb(b);
	}
	rest(a, b, i);
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
