/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:04:24 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 02:04:09 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

int main(void)
{
    t_semaphore sem;
    t_posix_shm shm_enc;
    t_posix_shm shm_dec;
	t_output	out;
	t_input		in;

    open_semaphores(&sem, DECODER);

    out.comp_bytes = malloc(sizeof(size_t));
	out.total_bytes = malloc(sizeof(size_t));

	/* GET FILE SIZE */
	/* 2 */
	print_total_bytes(&sem, &shm_enc, &shm_dec, &out);

	/* 	GET FREQ_TABLE
		BUILD HUFFMAN */
	/* 4 */
	get_freq_table(&sem, &shm_enc, &shm_dec, &in, &out);
	
	/* 6 */
	send_decoded_txt(&sem, &shm_enc, &out);

	/* 8 */
	send_decompression_time(&sem, &shm_enc, &in, &out);

	free_decoder(&in, &out, &shm_dec, &sem);

    exit(EXIT_SUCCESS);
}
