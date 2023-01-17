/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:04:24 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/17 18:22:04 by yde-goes         ###   ########.fr       */
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
	printf("Waiting for encoder data...\n");

	/*	2nd step: read file size from encoder and send it back */
	print_total_bytes(&sem, &shm_enc, &shm_dec, &out);

	/*	4th step: get frequency table and send compressed bytes content */
	get_freq_table(&sem, &shm_enc, &shm_dec, &in, &out);

	/*	6th step: send decoded text to encoder */
	send_decoded_txt(&sem, &shm_enc, &out);

	/*	8th step: send decompression run time to encoder */
	send_decompression_time(&sem, &shm_enc, &in, &out);

	free_decoder(&in, &out, &shm_dec, &sem);

    exit(EXIT_SUCCESS);
}
