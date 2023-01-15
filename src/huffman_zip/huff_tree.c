/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:53:30 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 11:51:23 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

t_node	*remove_begin_node(t_list *list)
{
	t_node	*tmp;

	tmp = NULL;
	if (list->begin)
	{
		tmp = list->begin;
		list->begin = tmp->next;
		tmp->next = NULL;
		list->length--;
	}
	return (tmp);
}

t_node	*create_tree(t_list *list)
{
	t_node	*first;
	t_node	*second;
	t_node	*new;

	while (list->length > 1)
	{
		first = remove_begin_node(list);
		second = remove_begin_node(list);
		new = create_node(0, first->freq + second->freq, first, second);
		if (!new)
			return (NULL);
		sort_insert(list, new);
	}
	return (list->begin);
}

void	free_tree(t_node *tree)
{
	if (tree)
	{
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree);
	}
}

size_t	tree_height(t_node *root)
{
	size_t	left;
	size_t	right;

	if (!root)
		return (-1);
	else
	{
		left = tree_height(root->left) + 1;
		right = tree_height(root->right) + 1;
		if (left > right)
			return (left);
		else
			return (right);
	}
}
