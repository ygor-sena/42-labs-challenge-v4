/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 00:39:53 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 00:59:20 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"
#include "decoder.h"

void	decompress_file(t_input *in, t_output *out, t_posix_shm *shm_enc)
{
	init_table(in->huff.freq_tab);
	for (size_t i = 0; i < SIZE; i++)
	{
		in->huff.freq_tab[i] = *(u_int *)shm_enc->addr;
		shm_enc->addr++;
	}
	init_list(&in->huff.list);
	fill_list(in->huff.freq_tab, &in->huff.list);
	in->huff.tree = create_tree(&in->huff.list);
	in->huff.column = tree_height(in->huff.tree) + 1;
	in->huff.dictionary = init_dictionary(in->huff.column);
	generate_dictionary(in->huff.dictionary, in->huff.tree, "", in->huff.column);
	//descompactar
	*(out)->comp_bytes = get_file_size(ZIPPED_FILE_NAME, "rb") + 1;
	in->start = clock();
	out->decoded = decompression(out->total_bytes[0], in->huff.tree);
	in->end = clock(); 
}

void	get_decompression_time(t_input *in, t_output *out)
{
	double	duration;
	
	duration = ((double)in->end - in->start)/CLOCKS_PER_SEC;
	snprintf(out->unzip_time, sizeof(out->unzip_time), "%.6f", duration);
}

void	free_decoder(t_input *in, t_output *out, t_posix_shm *shm_dec, t_semaphore *sem)
{
	free(out->decoded);
	free(out->total_bytes);
	free(out->comp_bytes);
	free_tree(in->huff.tree);
	free_dictionary(in->huff.dictionary);
	free_shm(shm_dec, "SHM_DECODER_FNAME", CONSUMER);
    close_semaphores(sem);
}
