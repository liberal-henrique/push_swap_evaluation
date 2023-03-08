/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:31:19 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/08 11:26:20 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	small_i(t_list **a)
{
	t_list	*temp;
	int		temp_menor;
	int		index_smallest;

	temp = (*a);
	index_smallest = 0;
	temp_menor = (*a)->x;
	while (temp)
	{
		if (temp_menor > temp->x)
			temp_menor = temp->x;
		temp = temp->next;
	}
	temp = (*a);
	while (temp != NULL)
	{
		if (temp->x == temp_menor)
			break ;
		temp = temp->next;
		index_smallest++;
	}
	return (index_smallest);
}

int	big_i(t_list **a)
{
	t_list	*temp;
	int		temp_maior;
	int		index_biggest;

	temp = (*a);
	index_biggest = 0;
	temp_maior = (*a)->x;
	while (temp)
	{
		if (temp_maior < temp->x)
			temp_maior = temp->x;
		temp = temp->next;
	}
	temp = (*a);
	while (temp != NULL)
	{
		if (temp->x == temp_maior)
			break ;
		temp = temp->next;
		index_biggest++;
	}
	return (index_biggest);
}

int	ft_pultimo(t_list **a)
{
	t_list	*list_temp;
	int		pultimo;

	list_temp = clone_list(a);
	sort_list(&list_temp);
	pultimo = list_temp->next->next->next->x;
	deallocate(&list_temp, 0);
	return (pultimo);
}

int	ft_meio(t_list **a)
{
	t_list	*list_temp;
	int		meio;

	list_temp = clone_list(a);
	sort_list(&list_temp);
	meio = list_temp->next->next->x;
	deallocate(&list_temp, 0);
	return (meio);
}

void	send_desire(t_list **a, t_list **b, int meio, int pnultimo)
{
	if ((*a)->x == meio || (*a)->x == pnultimo)
		ra(a);
	else
		pb(b, a);
}

void	sort_3(t_list **a)
{
	t_list	*tmp;
	int		topo;

	tmp = *a;
	topo = (*a)->x;
	while (tmp->next)
		tmp = tmp->next;
	if (topo > (*a)->next->x && topo > tmp->x && (*a)->next->x < tmp->x)
		ra(a);
	else if (topo > (*a)->next->x && topo > tmp->x && (*a)->next->x > tmp->x)
	{
		sa(a);
		rra(a);
	}
	else if (topo > (*a)->next->x && topo < tmp->x)
		sa(a);
	else if (topo < (*a)->next->x && topo > tmp->x)
		rra(a);
	else if (topo < (*a)->next->x && topo < tmp->x)
	{
		sa(a);
		ra(a);
	}
	return ;
}

void	sort_4_elements(t_list **a, t_list **b)
{
	if (small_i(a) == 0 || big_i(a) == 0)
		pb(b, a);
	else if (small_i(a) == 1 || big_i(a) == 1)
	{
		sa(a);
		if (list_sorted(a))
			return ;
		pb(b, a);
	}
	else if (small_i(a) == 3 || big_i(a) == 3)
	{
		rra(a);
		if (list_sorted(a))
			return ;
		pb(b, a);
	}
	sort_3(a);
	pa(a, b);
	if (!(list_sorted(a)))
		ra(a);
}

void	sort_5_elements(t_list **a, t_list **b)
{
	int	meio;
	int	pnultimo;

	meio = ft_meio(a);
	pnultimo = ft_pultimo(a);
	while (cnt_rec(*a) != 3)
		send_desire(a, b, meio, pnultimo);
	if (!list_sorted(a))
		sort_3(a);
	if ((*b)->x < (*b)->next->x)
		sb(b);
	pa(a, b);
	if (!(list_sorted(a)))
		ra(a);
	pa(a, b);
	if (!(list_sorted(a)))
		sa(a);
}

int	gv_i_mid(t_list **a)
{
	int		mid;
	int		size;

	mid = 0;
	size = cnt_rec(*a);
	if (size % 2 != 0)
		mid = (size / 2) + 1;
	else
		mid = (size / 2);
	return (mid);
}

int	give_value_mid(t_list **a)
{
	t_list	*temp;
	t_list	*clone;
	int		mid_value;
	int		index_mid;

	mid_value = 0;
	clone = clone_list(a);
	temp = clone;
	index_mid = gv_i_mid(a);
	sort_list(&temp);
	while (index_mid >= 0 && temp != NULL)
	{
		if (index_mid == 0)
			mid_value = temp->x;
		index_mid--;
		temp = temp->next;
	}
	deallocate(&clone, 0);
	return (mid_value);
}

void	send_pb(t_list **a, t_list **b, int top, int bottom)
{
	if (top <= bottom)
	{
		while (top-- != 0)
			ra(a);
		pb(b, a);
	}
	else if (bottom < top)
	{
		while (bottom-- != 0)
			rra(a);
		pb(b, a);
	}
}

int	numero_movi(t_list **a, int end)
{
	t_list	*temp;
	t_list	*clone;
	int		i;

	clone = clone_list(a);
	temp = clone;
	sort_list(&temp);
	i = 1;
	while (temp->next != NULL && temp->x != end)
	{
		i++;
		temp = temp->next;
	}
	deallocate(&clone, 0);
	return (i);
}

int	start(t_list **a)
{
	t_list	*temp;
	t_list	*clone;
	int		start;

	clone = clone_list(a);
	temp = clone;
	sort_list(&temp);
	start = temp->x;
	deallocate(&clone, 0);
	return (start);
}

int	end(t_list **a)
{
	t_list	*temp;
	t_list	*clone;
	int		end;

	clone = clone_list(a);
	temp = clone;
	sort_list(&temp);
	end = 0;
	while (temp->next != NULL && end != 29)
	{
		end++;
		temp = temp->next;
	}
	end = temp->x;
	deallocate(&clone, 0);
	return (end);
}
