/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_decode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:59:00 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:42:13 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

char	*decode(u_char encoded_txt[], t_node *root)
{
	size_t	i;
	t_node	*tmp;
	char	*decoded;
	char	chr_to_decode[2];

	i = 0;
	tmp = root;
	decoded = calloc(strlen((char *)encoded_txt), sizeof(chr_to_decode));
	if (!decoded)
		return (NULL);
	while (encoded_txt[i] != '\0')
	{
		if (encoded_txt[i] == '0')
			tmp = tmp->left;
		else
			tmp = tmp->right;
		if (!tmp->left && !tmp->right)
		{
			chr_to_decode[0] = tmp->chr;
			chr_to_decode[1] = '\0';
			strcat(decoded, chr_to_decode);
			tmp = root;
		}
		i++;
	}
	return (decoded);
}
