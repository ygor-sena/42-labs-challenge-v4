/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:00:30 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/17 18:33:55 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H

# include "huffman.h"
# include "sem_shm.h"
# include <unistd.h>
# include <time.h>

/**
 * @brief t_output is a struct that contains the variables to send from the
 * decoder to encoder program.
 * 
 * @param decoded The decoded string after file decompression.
 * @param unzip_time Time operation of decompression. This variable is a
 * double converted to a string of size SIZE tag, i.e., 256.
 * @param comp_bytes Bytes files compressed, it stands for the binary file
 * size after compression.
 * @param total_bytes Total file bytes before compression.
 * @param sb Contains information necessary to read shared memory content.
 */
typedef struct s_output
{
	u_char	*decoded;
	char	unzip_time[SIZE];
	size_t	*comp_bytes;
	size_t	*total_bytes;
}	t_output;

/**
 * @brief t_input is a struct that contains the variables necessary for
 * decoder program operations.
 * 
 * @param huff Contains the algorithm information necessary to decompress
 * the file from encoder program.
 * @param start Begin decompression time count.
 * @param end Stop decompression time count size after compression.
 */
typedef struct s_input
{
	t_huffman	huff;
	clock_t		start;
	clock_t		end;
}	t_input;

/**
 * @brief This function decompress a file after it has received the file size
 * and the frequency table from encoder program. It is executed inside 
 * get_freq_table() function.
 * 
 * @param in Struct with necessary information for decoder operation.
 * @param out Saves information to t_output to send for the encoder program.
 * @param shm_enc Reads content from encoder shared memory.
 * 
 * @return (void) If something goes wrong, the function exits the program with
 * err_exit();
 */
void	decompress_file(t_input *in, t_output *out, t_posix_shm *shm_enc);

/**
 * @brief This function gets the time execution of decompression operation.
 * 
 * @param in Struct with necessary information for decoder operation.
 * @param out Saves information to t_output to send for the encoder program.
 * 
 * @return (void) The function will save the double result in a local variable
 * and convert it to a string of size SIZE tag, i.e. 256.
 */
void	get_decompression_time(t_input *in, t_output *out);

/**
 * @brief This function frees all allocated memory during decoder program.
 * 
 * @param in Struct with necessary information for decoder operation.
 * @param out Saves information to t_output to send for the encoder program.
 * @param shm_dec Reads content from decoder shared memory.
 * @param sem Semaphores that were inicialized by decoder program.
 * 
 * @return (void) Successfully frees all content that were allocated.
 */
void	free_decoder(t_input *in, t_output *out, t_posix_shm *shm_dec, t_semaphore *sem);

/**
 * @brief This function gets the file size sent from encoder program and sends it
 * back as an output information.
 * 
 * @param sem Semaphores that were inicialized by decoder program.
 * @param in Struct with necessary information for decoder operation.
 * @param shm_enc Reads content from encoder shared memory.
 * @param shm_dec Reads content from decoder shared memory.
 * @param out Saves information to t_output to send for the encoder program.
 * 
 * @return (void) Successfully gets and sends file size to encoder program.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	print_total_bytes(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_output *out);

/**
 * @brief This function get the frequency table from encoder program, decompress
 * a file and send back to encoder the number of bytes compressed.
 * 
 * @param sem Semaphores that were inicialized by decoder program.
 * @param in Struct with necessary information for decoder operation.
 * @param shm_enc Reads content from encoder shared memory.
 * @param shm_dec Reads content from decoder shared memory.
 * @param out Saves information to t_output to send for the encoder program.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	get_freq_table(t_semaphore *sem, t_posix_shm *shm_enc, t_posix_shm *shm_dec, t_input *in, t_output *out);

/**
 * @brief This function sends to encoder program the content of the file that
 * was decompressed.
 * 
 * @param sem Semaphores that were inicialized by decoder program.
 * @param shm_enc Reads content from encoder shared memory.
 * @param out Saves information to t_output to send for the encoder program.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	send_decoded_txt(t_semaphore *sem, t_posix_shm *shm_enc, t_output *out);

/**
 * @brief This function sends to encoder program the time of decompression
 * operation.
 * 
 * @param sem Semaphores that were inicialized by decoder program.
 * @param shm_dec Reads content from decoder shared memory.
 * @param in Struct with necessary information for decoder operation.
 * @param out Saves information to t_output to send for the encoder program.
 * 
 * @return (void) Successfully does the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	send_decompression_time(t_semaphore *sem, t_posix_shm *shm_dec, t_input *in, t_output *out);

#endif