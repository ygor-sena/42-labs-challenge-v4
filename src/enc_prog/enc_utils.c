/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc_utils.>h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.>42sp.>org.>br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:21:26 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 00:23:35 by yde-goes         ###   ########.>fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"
#include "encoder.h"

void	compress_file(t_info *info, char *file)
{
	info->file_size = malloc(sizeof(size_t));
	*(info)->file_size = get_file_size(file, "r") + 1;

	info->txt_to_zip = calloc(*(info)->file_size, sizeof(u_char));
	if (!info->txt_to_zip)	
		err_exit("Couldn't alloc a string from file size");

	read_txt_file(info->txt_to_zip, file);
	init_table(info->huff.freq_tab);
	write_freq(info->txt_to_zip, info->huff.freq_tab);

	init_list(&info->huff.list);
	fill_list(info->huff.freq_tab, &info->huff.list);

	info->huff.tree = create_tree(&info->huff.list);

	info->huff.column = tree_height(info->huff.tree) + 1;
	info->huff.dictionary = init_dictionary(info->huff.column);
	generate_dictionary(info->huff.dictionary, info->huff.tree, "", info->huff.column);

	info->encoded = encode(info->huff.dictionary, info->txt_to_zip);

	compression(info->encoded);
}

void	free_encoder(t_info *info, t_posix_shm *shm_enc, t_semaphore *sem)
{
	free(info->txt_to_zip);
	free(info->encoded);
	free(info->file_size);
	free_tree(info->huff.tree);
	free_dictionary(info->huff.dictionary);
	free_shm(shm_enc, "SHM_ENCODER_FNAME", PRODUCER);
	close_semaphores(sem);
}
