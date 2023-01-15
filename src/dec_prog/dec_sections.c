/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:03:55 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 02:59:29 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"
#include "decoder.h"

void	print_total_bytes(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_output *out)
{
	sem_wait(sem->encoder);
	read_shm_int(shm_enc, "SHM_ENCODER_FNAME");
	printf("Reading from encoder...\n");
	*(out)->total_bytes = *(size_t *) shm_enc->addr;
	set_shm_int(shm_dec, "SHM_DECODER_FNAME", (u_int *)out->total_bytes, sizeof(u_int));
	read_shm_int(shm_enc, "SHM_ENCODER_FNAME");
	sem_post(sem->decoder);
	usleep(500);
}

void	get_freq_table(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_input *in, t_output *out)
{
	sem_wait(sem->encoder);
	read_shm_int(shm_enc, "SHM_ENCODER_FNAME");
	decompress_file(in, out, shm_enc);
	set_shm_int(shm_dec, "SHM_DECODER_FNAME", (u_int *)out->comp_bytes, sizeof(u_int));
	sem_post(sem->decoder);
	usleep(500);
}

void	send_decoded_txt(t_semaphore *sem, t_posix_shm *shm_dec, t_output *out)
{
	sem_wait(sem->encoder);
	set_shm_char(shm_dec, "SHM_DECODER_FNAME", out->decoded, strlen((char *)out->decoded) + 1);
	sem_post(sem->decoder);
	usleep(500);
}

void	send_decompression_time(t_semaphore *sem, t_posix_shm *shm_dec, t_input *in, t_output *out)
{
	sem_wait(sem->encoder);
	get_decompression_time(in, out);
	set_shm_char(shm_dec, "SHM_DECODER_FNAME", (u_char *)out->unzip_time, strlen(out->unzip_time) + 1);
	sem_post(sem->decoder);
	usleep(500);
}
