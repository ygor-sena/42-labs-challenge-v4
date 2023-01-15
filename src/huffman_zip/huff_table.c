/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:49:48 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 11:08:52 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	init_table(u_int *tab)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		tab[i] = 0;
	}
}

void	write_freq(u_char *txt, u_int *tab)
{
	size_t	i;

	i = 0;
	while (txt[i] != '\0')
	{
		tab[txt[i]]++;
		i++;
	}
}
