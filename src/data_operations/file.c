/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:20:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:47:28 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"
#include "encoder.h"

static u_int	is_bit_one(u_char byte, int i);

size_t	get_file_size(char *filename, char *read_mode)
{
	FILE	*txt_file;
	size_t	file_size;

	file_size = 0;
	txt_file = fopen(filename, read_mode);
	if (!txt_file)
		err_exit("Couldn't get file size. File doesn't exist");
	while (fgetc(txt_file) != -1)
		file_size++;
	fclose(txt_file);
	return (file_size);
}

u_char	*decompression(size_t encoded_txt, t_node *root)
{
	FILE	*bit_file;
	t_node	*tmp;
	int		offset;
	u_char	byte;
	size_t	i;
	u_char	*decompressed;

	bit_file = fopen(ZIPPED_FILE_NAME, "rb");
	tmp = root;
	decompressed = calloc(encoded_txt, sizeof(u_char));
	i = 0;
	if (!bit_file)
		perror("Couldn't open file to decompress");
	while (fread(&byte, sizeof(byte), 1, bit_file))
	{
		for (offset = 7; offset >= 0; offset--)
		{
			if (is_bit_one(byte, offset))
				tmp = tmp->right;
			else
				tmp = tmp->left;
			if (!tmp->left && !tmp->right)
			{
				decompressed[i] = tmp->chr;
				i++;
				tmp = root;
			}
		}
	}
	fclose(bit_file);
	return (decompressed);
}

void	compression(char *str)
{
	FILE	*bit_file;
	size_t	i;
	int		j;
	u_char	byte;
	u_char	mask;

	bit_file = fopen(ZIPPED_FILE_NAME, "wb");
	i = 0;
	j = 7;
	byte = 0;
	if (!bit_file)
		perror("Couldn't open file to compress it");
	while (str[i] != '\0')
	{
		mask = 1;
		if (str[i] == '1')
		{
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0)
		{
			fwrite(&byte, sizeof(byte), 1, bit_file);
			byte = 0;
			j = 7;
		}
		i++;
	}
	if (j != 7)
		fwrite(&byte, sizeof(byte), 1, bit_file);
	fclose(bit_file);
}

static u_int	is_bit_one(u_char byte, int i)
{
	u_char	mask;

	mask = (1 << i);
	return (byte & mask);
}

void	read_txt_file(u_char *txt, char *filename)
{
	FILE	*txt_file;
	char	chr;
	size_t	i;

	txt_file = fopen(filename, "r");
	i = 0;
	if (!txt_file)
		err_exit("Couldn't read file to get its content");
	while (!feof(txt_file))
	{
		chr = fgetc(txt_file);
		if (chr != -1)
		{
			txt[i] = chr;
			i++;
		}	
	}
	fclose(txt_file);
}
