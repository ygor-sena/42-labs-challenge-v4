/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc_sections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:04:07 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/17 18:03:41 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"
#include "encoder.h"

void	send_file_size(t_semaphore *sem, t_posix_shm *shm_enc, t_info *info)
{
	sem_wait(sem->decoder);
	set_shm_int(shm_enc, "SHM_ENCODER_FNAME", (u_int *)info->file_size, sizeof(u_int));
    sem_post(sem->encoder);
	usleep(500);
}

void	send_freq_table(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_info *info)
{
	sem_wait(sem->decoder);
	set_shm_int(shm_enc, "SHM_ENCODER_FNAME", info->huff.freq_tab, 256 * sizeof(u_int));
	read_shm_int(shm_dec, "SHM_DECODER_FNAME");
	info->total_bytes = *(size_t *)shm_dec->addr;
	sem_post(sem->encoder);
	usleep(500);
}

void	get_total_bytes(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info)
{
	sem_wait(sem->decoder);
	read_shm_int(shm_dec, "SHM_DECODER_FNAME");
	info->comp_bytes = *(size_t *)shm_dec->addr;
	sem_post(sem->encoder);
	usleep(500);
}

void	get_unzipped_text(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info)
{
	sem_wait(sem->decoder);
    read_shm_char(shm_dec, "SHM_DECODER_FNAME");
	info->decoded = shm_dec->msg;
	printf("Unzipped text is: %s\n", info->decoded);
    sem_post(sem->encoder);
	usleep(500);
}

void	get_unzipped_time(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info)
{
	sem_wait(sem->decoder);
    read_shm_char(shm_dec, "SHM_DECODER_FNAME");
	info->unzip_time = shm_dec->msg;
    sem_post(sem->encoder);
	usleep(500);
}

void	print_unzip_result(t_info *info)
{
	printf("File size in bytes: %ld\n", info->total_bytes);
	printf("Total bytes compressed: %ld\n", info->total_bytes - info->comp_bytes);
	printf("Decompression time is: %s\n", info->unzip_time);
}
