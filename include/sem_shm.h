/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_shm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:01:14 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 09:15:36 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef SHARED_DATA_H
# define SHARED_DATA_H

# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include <sys/sem.h>
# include <sys/shm.h>
# include <semaphore.h>
# include "huffman.h"

# define SEM_ENCODER_FNAME "/producer_sem"
# define SEM_DECODER_FNAME "/consumer_sem"

# define SHM_ENCODER_FNAME "/encoder_shm"
# define SHM_DECODER_FNAME "/decoder_shm"

# define PRODUCER 0
# define CONSUMER 1
# define ENCODER 0
# define DECODER 1

/**
 * @brief t_posix_shm is the structure that contains all the variables
 * that are necessary to inicialize a POSIX shared memory and move content
 * to it.
 * 
 * @param fd Accesses fd of shared memory object
 * @param len Memory to be allocated with mmap()
 * @param addr Writes an u_int content type to shared memory
 * @param msg Writes an u_char content type to shared memory
 * @param sb Contains information necessary to read shared memory content
 */
typedef struct s_posix_shm
{
    int         fd;
    size_t      len;
    u_int       *addr;
    u_char      *msg;
    struct stat sb;
}   t_posix_shm;

/**
 * @brief t_semaphore contains two semaphores encoder and decoder that
 * start with values 0 and 1 respectively.
 * 
 * @param encoder The semaphore encoder controls encoder program to execute
 * its tasks.
 * @param decoder The semaphore decoder controls decoder program to execute
 * its tasks.
 */
typedef struct s_semaphore
{
    sem_t   *encoder;
    sem_t   *decoder;
}   t_semaphore;

/**
 * @brief The open_semaphores() function inicializes the semaphores to used
 * between the interprocess communication of the encoder and decoder program.
 *
 * @param sem A struct containing the semaphores to be inicialized.
 * @param process This variable specifies if the semaphore is to be created
 * create by decoder program (i.e. DECODER tag which is equivalent to 0) or 
 * just accessed by encoder (i.e. ENCODER tag which is equivalent to 1)
 * 
 * @return (void) If semaphore inicialization is unsuccessful, then it exits
 * the program with err_exit() function.
 */
void    open_semaphores(t_semaphore *sem, int process);

/**
 * @brief The close_semaphores() closes the semaphores inicialized bu
 * open_semaphore() function.
 *
 * @param sem A struct containing the semaphores to be closed.
 * 
 * @return (void) It tries to close the semaphores if they were inicialized.
 * Otherwise, it will do nothing.
 */
void    close_semaphores(t_semaphore *sem);

/**
 * @brief The close_semaphores() closes the semaphores inicialized bu
 * open_semaphore() function.
 *
 * @param sem A struct containing the semaphores to be closed.
 * 
 * @return (void) It tries to close the semaphores if they were inicialized.
 * Otherwise, it will do nothing.
 */

/**
 * @brief The set_shm_int creates an POSIX shared memory and maps to its address
 * a content of u_int type.
 *
 * @param shm The shared memory struct necessary to its configuration.
 * @param shm_fname The shared memory file descriptor name.
 * @param to_write Content to be written to the shared memory.
 * @param len to_write length necessary to allocate the exact size with mmap().
 * 
 * @return (void) If something go wrong through the proccess of memory shared
 * creation, the function will exits the program with err_exit().
 */
void    set_shm_int(t_posix_shm *shm, char *shm_fname, u_int *to_write, size_t len);

/**
 * @brief The set_shm_char creates an POSIX shared memory and maps to its address
 * a content of u_char type.
 *
 * @param shm The shared memory struct necessary to its configuration.
 * @param shm_fname The shared memory file descriptor name.
 * @param to_write Content to be written to the shared memory.
 * @param len to_write length necessary to allocate the exact size with mmap().
 * 
 * @return (void) If something go wrong through the proccess of memory shared
 * creation, the function will exits the program with err_exit().
 */
void    set_shm_char(t_posix_shm *shm, char *shm_fname, u_char *to_write, size_t len);

/**
 * @brief The read_shm_int reads an u_char content type of an existing POSIX 
 * shared memory.
 *
 * @param shm The shared memory struct with information of the shared memory
 * to be read.
 * @param shm_fname The shared memory file descriptor name to be read.
 * 
 * @return (void) If something go wrong through the proccess of memory shared
 * creation, the function will exits the program with err_exit().
 */
void    read_shm_int(t_posix_shm *shm, char *shm_fname);

/**
 * @brief The read_shm_char reads an u_char content type of an existing POSIX 
 * shared memory.
 *
 * @param shm The shared memory struct with information of the shared memory
 * to be read.
 * @param shm_fname The shared memory file descriptor name to be read.
 * 
 * @return (void) If something go wrong through the proccess of memory shared
 * creation, the function will exits the program with err_exit().
 */
void    read_shm_char(t_posix_shm *shm, char *shm_fname);

/**
 * @brief The free_shm frees an existing POSIX shared memory.
 *
 * @param shm The shared memory struct with information of the shared memory
 * to be freed.
 * @param shm_fname The shared memory file descriptor name to be freed.
 * @param shm_type It can be a shared memory that was created by the encoder
 * or decoder program, i.e. PRODUCER and CONSUMER tag which stands for 0 and 
 * 1 respectively.
 * 
 * @return (void) If something go wrong through the proccess of memory shared
 * creation, the function will exits the program with err_exit().
 */
void    free_shm(t_posix_shm *shm, char *shm_fname, int shm_type);

/**
 * @brief The err_exit() function writes a message error with an associated
 * errno value to the given output stream and exits program with failing
 * exit status (EXIT_FAILURE)
 *
 * @param msg String to be written to the output 
 * 
 * @return (void) The function exits the program with a call of exit()
 */
void    err_exit(char *msg);

#endif