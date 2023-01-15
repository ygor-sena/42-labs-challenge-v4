/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huff_encode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:57:28 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:41:58 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

static size_t	get_code_size(char **dictionary, u_char *txt);

char	*encode(char **dictionary, u_char *txt)
{
	char	*code;
	size_t	length;
	size_t	i;

	i = 0;
	length = get_code_size(dictionary, txt);
	code = calloc(length, sizeof(code));
	if (!code)
		return (NULL);
	while (txt[i] != '\0')
	{
		strncat(code, dictionary[txt[i]], length);
		i++;
	}
	return (code);
}

static size_t	get_code_size(char **dictionary, u_char *txt)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (txt[i] != '\0')
	{
		length += strlen(dictionary[txt[i]]);
		i++;
	}
	return (length + 1);
}
