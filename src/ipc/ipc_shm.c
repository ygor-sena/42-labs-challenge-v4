/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_shm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:38:50 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 11:00:15 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_shm.h"

void	set_shm_int(t_posix_shm *shm, char *shm_fname, u_int *to_write, size_t len)
{
	shm->fd = shm_open(shm_fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (shm->fd == -1)
		err_exit("shm_open");
	shm->len = len;
	if (ftruncate(shm->fd, shm->len) == -1)
		err_exit("ftruncate");
	shm->addr = mmap(NULL, shm->len, \
					PROT_READ | PROT_WRITE, MAP_SHARED, shm->fd, 0);
	if (shm->addr == MAP_FAILED)
		err_exit("mmap");
	if (close(shm->fd) == -1)
		err_exit("close");
	memcpy(shm->addr, (u_int *)to_write, shm->len);  
}

void	set_shm_char(t_posix_shm *shm, char *shm_fname, u_char *to_write, size_t len)
{
	shm->fd = shm_open(shm_fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (shm->fd == -1)
		err_exit("shm_open");
	shm->len = len;
	if (ftruncate(shm->fd, shm->len) == -1)
		err_exit("ftruncate");
	shm->msg = mmap(NULL, shm->len, \
					PROT_READ | PROT_WRITE, MAP_SHARED, shm->fd, 0);
	if (shm->msg == MAP_FAILED)
		err_exit("mmap");
	if (close(shm->fd) == -1)
		err_exit("close");
	memcpy(shm->msg, (u_char *)to_write, shm->len);
}

void	read_shm_int(t_posix_shm *shm, char *shm_fname)
{
	shm->fd = shm_open(shm_fname, O_RDONLY, 0);
	if (shm->fd == -1)
		err_exit("shm_open");
	if (fstat(shm->fd, &shm->sb) == -1)
		err_exit("fstat");
	shm->addr = mmap(NULL, shm->sb.st_size, \
					PROT_READ, MAP_SHARED, shm->fd, 0);
	if (shm->addr == MAP_FAILED)
		err_exit("mmap");
	if (close(shm->fd) == -1)
		err_exit("close");
}

void	read_shm_char(t_posix_shm *shm, char *shm_fname)
{
	shm->fd = shm_open(shm_fname, O_RDONLY, 0);
	if (shm->fd == -1)
		err_exit("shm_open");
	if (fstat(shm->fd, &shm->sb) == -1)
		err_exit("fstat");
	shm->msg = mmap(NULL, shm->sb.st_size, \
					PROT_READ, MAP_SHARED, shm->fd, 0);
	if (shm->msg == MAP_FAILED)
		err_exit("mmap");
	if (close(shm->fd) == -1)
		err_exit("close");
}

void	free_shm(t_posix_shm *shm, char *shm_fname, int shm_type)
{
	(void)shm;
	if (shm_type == PRODUCER)
	{
		munmap(shm->addr, sizeof(u_int));
		munmap(shm->addr, sizeof(u_int) * 256);
	}	
	else if (shm_type == CONSUMER)
	{
		munmap(shm->addr, sizeof(u_int) * 2);
	}	
	if (shm_unlink(shm_fname) == -1)
		err_exit("Couldn't unlink encoder_shm");
}
