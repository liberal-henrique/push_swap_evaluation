/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasantos <rasantos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:55:36 by lliberal          #+#    #+#             */
/*   Updated: 2023/03/03 19:47:34 by rasantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int	count_items(t_list	*root)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = root;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

t_list	*ft_split_create_str(t_list *a, char *argv, char delimiter)
{
	char	**new_node;
	int		i;

	i = -1;
	new_node = ft_split(argv, delimiter);
	while (new_node[++i])
		insert_end(&a, ft_atoi_check_numbers(new_node[i], a));
	free_all(new_node);
	return (a);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((unsigned char )s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char )s1[i] == '\0')
			break ;
		i++;
	}
	return (1);
}

int	ft_isnum_compare(const char *str, t_list *a)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if ((str[i] > '9' || str[i] < '0'))
			deallocate(&a, 1);
	}
	if (ft_strncmp("-2147483648", str, 11) == 1)
		return (1);
	return (0);
}

long int	ft_atoi_check_numbers(const char *str, t_list *a)
{
	int			i;
	int			sign;
	int			flag;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	flag = ft_isnum_compare(str, a);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res >= 2147483648 && flag != 1)
			deallocate(&a, 1);
		i++;
	}
	return (res * sign);
}

char	write_word(char *dest, const char *from, char set)
{
	int	i;

	i = 0;
	while (from[i] != '\0')
	{
		if (from[i] != set)
			dest[i] = from[i];
		if (from[i] == set)
			break ;
		i++;
	}
	dest[i] = '\0';
	return (*dest);
}

int	word_count(const char *sr, char del)
{
	int	j;
	int	word;

	j = 0;
	word = 0;
	while (sr[j])
	{
		if (sr[j] != del && ((sr[j + 1] == del) || (sr[j + 1] == '\0')))
			word++;
		j++;
	}
	return (word);
}

void	add_split(char **dst, const char *string, char delimiter)
{
	int	l;
	int	j;
	int	letter;

	l = 0;
	letter = 0;
	while (string[l])
	{
		if (string[l] == delimiter)
			l++;
		else
		{
			j = 0;
			while (string[l + j] != delimiter && string[j + l])
				j++;
			dst[letter] = malloc (sizeof(char) * (j + 1));
			if (!dst[letter])
				return ;
			write_word(dst[letter], string + l, delimiter);
			if (string[j + l] == '\0')
				break ;
			l = l + j;
			letter++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	res = malloc (sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res[words] = NULL;
	add_split(res, s, c);
	return (res);
}

void	free_all(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free (result);
}

void	print_array_2d(char **arr_bidimensional)
{
	int	i;

	i = -1;
	while (arr_bidimensional[++i])
		printf("%s", arr_bidimensional[i]);
}

t_list	*initialize_list(char **argv, t_list *a)
{
	int		i;
	int		j;
	int		flag;
	t_list	*new_node;

	i = -1;
	new_node = NULL;
	while (argv[++i])
	{
		j = 0;
		flag = 0;
		while (argv[i][j++])
		{
			if ((argv[i][j] >= 9 && argv[i][j] <= 13) || argv[i][j] == 32)
			{
				flag = 1;
				new_node = ft_split_create_str(new_node, argv[i], argv[i][j]);
				break ;
			}
		}
		if (flag == 0)
			insert_end(&new_node, ft_atoi_check_numbers(argv[i], a));
	}
	return (new_node);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	a = initialize_list(argv + 1, a);
	if (count_items(a) <= 1)
	{
		deallocate(&a, 1);
		exit(1);
	}
	if (list_sorted(&a) == 1)
	{
		deallocate(&a, 1);
		exit(1);
	}
	if (cnt_rec(a) <= 3)
		sort_3(&a);
	else if (cnt_rec(a) <= 5)
		sort_5_elements(&a, &b);
	else
		sort_biggest(&a, &b);
	deallocate(&a, 0);
	return (0);
}