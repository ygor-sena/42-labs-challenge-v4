/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:21:50 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 02:24:54 by yde-goes         ###   ########.fr       */
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

	compress_file(&info, argv[1]);
    open_semaphores(&sem, ENCODER);
	/* 1 */
    send_file_size(&sem, &shm_enc, &info);
	/* 3 */
	send_freq_table(&sem, &shm_enc, &shm_dec, &info);
	/* 5 */
	get_total_bytes(&sem, &shm_dec, &info);
	/* 7 */
	/* SHOW DECODED */
    get_unzipped_text(&sem, &shm_dec, &info);
	/* 9 */
	get_unzipped_time(&sem, &shm_dec, &info);

	print_unzip_result(&info);
	
	free_encoder(&info, &shm_enc, &sem);

    exit(EXIT_SUCCESS);
}
