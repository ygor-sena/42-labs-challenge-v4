/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_sem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:32:34 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/14 23:33:24 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"

void	open_semaphores(t_semaphore *sem, int process)
{
	if (process == DECODER)
	{
		sem_unlink(SEM_ENCODER_FNAME);
		sem_unlink(SEM_DECODER_FNAME);

		sem->encoder = sem_open(SEM_ENCODER_FNAME, O_CREAT, 0660, 0);
		if (sem->encoder == SEM_FAILED)
			err_exit("sem_open/encoder");

		sem->decoder = sem_open(SEM_DECODER_FNAME, O_CREAT, 0660, 1);
		if (sem->decoder == SEM_FAILED)
			err_exit("sem_open/decoder");
	}
	else if (process == ENCODER)
	{
		sem->encoder = sem_open(SEM_ENCODER_FNAME, 0);
		if (sem->encoder == SEM_FAILED)
			err_exit("sem_open/encoder");
		sem->decoder = sem_open(SEM_DECODER_FNAME, 1);
		if (sem->decoder == SEM_FAILED)
			err_exit("sem_open/decoder");
	}
}

void	close_semaphores(t_semaphore *sem)
{
	sem_close(sem->encoder);
	sem_close(sem->decoder);
}
