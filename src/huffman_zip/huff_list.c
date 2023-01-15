/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:51:42 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:03:35 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	init_list(t_list *list)
{
	list->begin = NULL;
	list->length = 0;
}

t_node	*create_node(size_t i, u_int tab,
			struct s_node *right, struct s_node *left)
{
	t_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->chr = i;
	node->freq = tab;
	node->right = right;
	node->left = left;
	node->next = NULL;
	return (node);
}

void	fill_list(u_int *tab, t_list *list)
{
	t_node	*new;

	for (size_t i = 0; i < SIZE; i++)
	{
		if (tab[i] > 0)
		{
			new = create_node(i, tab[i], NULL, NULL);
			if (!new)
				break ;
			sort_insert(list, new);
		}
	}
}

void	sort_insert(t_list *list, t_node *node)
{
	t_node	*tmp;
	if (list->begin == NULL)
		list->begin = node;
	else if (node->freq < list->begin->freq)
	{
		node->next = list->begin;
		list->begin = node;
	}
	else
	{
		tmp = list->begin;
		while (tmp->next && tmp->next->freq <= node->freq)
			tmp = tmp->next;
		node->next = tmp->next;
		tmp->next = node;
	}
	list->length++;
}
