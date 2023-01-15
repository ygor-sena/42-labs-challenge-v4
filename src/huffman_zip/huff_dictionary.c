/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_dictionary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:55:55 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:09:49 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

char	**init_dictionary(size_t column)
{
	char	**dictionary;
	size_t	i;

	dictionary = malloc(sizeof(*dictionary) * SIZE);
	if (!dictionary)
		return (NULL);
	for (i = 0; i < SIZE; i++)
	{
		dictionary[i] = calloc(column, sizeof(**dictionary));
		if (!dictionary[i])
			return (NULL);
	}
	return (dictionary);
}

void	generate_dictionary(char **dict, t_node *root,
			char *path, size_t column)
{
	char	left[column];
	char	right[column];

	if (!root->left && !root->right)
		strncpy((char *)dict[root->chr], path, column);
	else
	{
		strncpy(left, path, column);
		strncpy(right, path, column);
		strncat(left, "0", column);
		strncat(right, "1", column);
		generate_dictionary(dict, root->left, left, column);
		generate_dictionary(dict, root->right, right, column);
	}
}

void	free_dictionary(char **dictionary)
{
	size_t	str;

	str = 0;
	if (!dictionary)
		return ;
	while (str < SIZE)
		free(dictionary[str++]);
	free(dictionary);
}
