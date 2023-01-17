/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:21:50 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/17 18:22:52 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"
#include "encoder.h"


int main(int argc, char *argv[])
{
    t_posix_shm shm_enc;
    t_posix_shm shm_dec;
    t_semaphore sem;
	t_info		info;
	
	if (argc != 2)
		err_exit("Usage: ./encoder <string_to_write>");

    open_semaphores(&sem, ENCODER);
	compress_file(&info, argv[1]);

	/*	[ENCODER/DECODER SEMAPHORE AND SHM IPC]
		1st step: send file size content */
    send_file_size(&sem, &shm_enc, &info);

	/*	3rd step: send frequency table to decoder */
	send_freq_table(&sem, &shm_enc, &shm_dec, &info);

	/*	5th step: get file size from decoder */
	get_total_bytes(&sem, &shm_dec, &info);

	/*	7th step: get decoded text */
    get_unzipped_text(&sem, &shm_dec, &info);

	/*	9th step: get decompression run time */
	get_unzipped_time(&sem, &shm_dec, &info);

	/*	10th step: print information received from decoder */
	print_unzip_result(&info);
	
	free_encoder(&info, &shm_enc, &sem);

    exit(EXIT_SUCCESS);
}
