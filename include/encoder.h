/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:03:33 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/17 18:34:27 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
# define ENCODER_H

# include "huffman.h"
# include "sem_shm.h"

/**
 * @brief t_info is a struct that contains all the information necessary
 * for encoder operations. The content of the variables total_bytes,
 * comp_bytes, unzip_time and decoded comes from decoder program through
 * shared memory.
 * 
 * @param txt_to_zip Gets the content of the file to compress and save it
 * to a string.
 * @param encoded The encoded string from txt_to_zip so that it can be
 * compressed.
 * @param huff Contains the algorithm information necessary to decompress
 * the file from encoder program.
 * @param total_bytes Total file bytes before compression.
 * @param comp_bytes Bytes files compressed, it stands for the binary file
 * @param decoded The decoded string after file decompression.
 * @param unzip_time Time operation of decompression. This variable is a
 * double converted to a string of size SIZE tag, i.e., 256.
 * size after compression.
 */
typedef struct s_info
{
	u_char	*txt_to_zip;
	char	*encoded;
	size_t	*file_size;
	t_huffman	huff;
	size_t	total_bytes;
	size_t	comp_bytes;
	u_char	*unzip_time;
	u_char	*decoded;
}	t_info;

/**
 * @brief This function gets the file size passed as parameter, read its
 * content and saves it to a string variable. After that, it creates a table
 * of characters frequency that will the used to generate a list and a huffman
 * tree. Then, it creates a dictionary of bits for each found character,
 * encodes them and compress the information so that it can be sent to decoder
 * program.
 * @param info Struct with necessary information for enconder operation.
 * @param file File to be compressed.
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	compress_file(t_info *info, char *file);

/**
 * @brief This function frees all allocated memory during encoder program.
 * 
 * @param info Struct with necessary information for enconder operation.
 * @param shm Reads content from encoder shared memory.
 * @param sem Semaphores that were accessed by encoder program.
 * 
 * @return (void) Successfully frees all content that were allocated.
 */
void	free_encoder(t_info *info, t_posix_shm *shm, t_semaphore *sem);

/**
 * @brief This function sends to decoder program the size of the file
 * to be compressed.
 * 
 * @param sem Semaphores that were accessed by encoder program.
 * @param shm_enc Reads content from encoder shared memory.
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	send_file_size(t_semaphore *sem, t_posix_shm *shm_enc, t_info *info);

/**
 * @brief This function sends to decoder program the frequency table which
 * allows the decoder program to recreate the dictionary necessary to unzip
 * the compressed file. It also receives the length of the file before
 * compression from decoder program and prints it to the standard output.
 * 
 * @param sem Semaphores that were accessed by encoder program.
 * @param shm_enc Reads content from encoder shared memory.
 * @param shm_dec Reads content from decoder shared memory.
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	send_freq_table(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_info *info);

/**
 * @brief This function reads from decoder program the length of the 
 * file to be compressed.
 * 
 * @param sem Semaphores that were accessed by encoder program.
 * @param shm_dec Reads content from decoder shared memory.
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully do the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	get_total_bytes(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info);

/**
 * @brief This function reads from decoder program and prints to
 * the standard output the unzipped text after decompression.
 * 
 * @param sem Semaphores that were accessed by encoder program.
 * @param shm_dec Reads content from decoder shared memory.
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	get_unzipped_text(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info);

/**
 * @brief This function reads from decoder program the time of the 
 * decompression operation.
 * 
 * @param sem Semaphores that were accessed by encoder program.
 * @param shm_dec Reads content from decoder shared memory.
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	get_unzipped_time(t_semaphore *sem, t_posix_shm *shm_dec, t_info *info);

/**
 * @brief This function prints to the standard output the the length of the 
 * file to be compressed, the unzipped text after decompression and time
 * of the decompression operation.
 * 
 * @param info Struct with necessary information for enconder operation.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 */
void	print_unzip_result(t_info *info);

#endif