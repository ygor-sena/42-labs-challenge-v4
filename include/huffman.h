/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:46:06 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/15 12:54:18 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>

# define SIZE 				256
# define ZIPPED_FILE_NAME	"encoded.ft"

/**
 * @brief t_node struct is both a singular linked list and a tree. It will 
 * be used to encode, decode, compress and decompress string on a given file.
 * 
 * @param chr Saves the character of a file text. Since it is an unsigned char,
 * it supports special characters.
 * @param freq Saves the frequency upon which each character occurs in a given
 * text.
 * @param left Goes to the left node of the tree.
 * @param right Goes to the right node of the tree.
 * @param next Goes to the next node of the singular linked list.
 **/
typedef struct s_node
{
	u_char			chr;
	size_t			freq;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}					t_node;

/**
 * @brief t_list is an auxiliary struct to the struct t_node. It is used to
 * pointer to a pointer.
 * 
 * @param begin Points to the first element of the t_node struct.
 * @param length Total nodes t_node of the t_list struct.
 */
typedef struct s_list
{
	t_node	*begin;
	size_t	length;
}			t_list;

/**
 * @brief t_huffman contains all the necessary information for the Huffman
 * compression algorithm.
 * 
 * @param freq_tab Stores the characters and its occurence in an array from
 * 0 to 255.
 * @param list Points to the first element of the t_node struct and its size.
 * @param tree Saves the Huffman tree of the encoded characters.
 * @param column Contains the size of the biggest encoded character and creates
 * the necessary columns size for the dictionary of encoded characters.
 * @param dictionary Saves the encoded character of the given string from
 * frequency table.
 */
typedef struct s_huffman
{
	u_int	freq_tab[SIZE];
	t_list	list;
	t_node	*tree;
	size_t	column;
	char	**dictionary;
}	t_huffman;

/**
 * @brief This function inicializes the frequency table to store the
 * characters occurrences.
 * @param tab Array that stores the characters frequency. It has a size of
 * SIZE tag, i.e. 256, which stands for the characters between 0 and 255.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	init_table(u_int *tab);

/**
 * @brief This function writes to the frequency table the
 * characters occurrences.
 * @param txt The string that has the content of the file.
 * @param tab Array that stores the characters frequency. It has a size of
 * SIZE tag, i.e. 256, which stands for the characters between 0 and 255.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	write_freq(u_char *txt, u_int *tab);

/**
 * @brief This function inicializes the list that stores the
 * first node of the tree.
 * @param list Points to the first element of the t_node struct and its size.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	init_list(t_list *list);

/**
 * @brief This function creates a node that is both the tree and the singular
 * linked list necessary for the Huffman algorithm. 
 * @param i Value of the characted to be stored.
 * @param tab Value of the frequency of the character i.
 * @param right Value of the right node of the tree.
 * @param left Value of the left node of the tree.
 * @return (t_node) Successfully create a node. Otherwise, it retuns NULL
 * if the function could not allocate the required memory for its creation.
 */
t_node	*create_node(size_t i, u_int tab, struct s_node *right, struct s_node *left);

/**
 * @brief This function creates a node that is both the tree and the singular
 * linked list necessary for the Huffman algorithm. 
 * @param i Value of the characted to be stored.
 * @param tab Value of the frequency of the character i.
 * @param list Node of the singular linked list that stores the first and
 * second parameter.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	fill_list(u_int *tab, t_list *list);

/**
 * @brief This function inserts a new node on a given first sorted by
 * character frequency. The node with the lowest character occurrence value
 * is the first and the biggest one is the last.
 * @param list A list the contains existing sorted nodes of frequencies.
 * @param node Node to be inserted and sorted into the list.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	sort_insert(t_list *list, t_node *node);

/**
 * @brief This function removes the first node of the list.
 * @param list A list the contains existing sorted nodes of frequencies.
 * @return (t_node) In case of non existing nodes to be removed, it returns
 * NULL.
 */
t_node	*remove_begin_node(t_list *list);

/**
 * @brief This function removes the first two elements of the singular linked
 * list and create a new tree node with t_node left and t_node right that
 * stores the removed list nodes. In other words, this function converts a singular
 * linked list to a tree.
 * @param list A list the contains existing sorted nodes of frequencies.
 * @return (t_node) In case of success, it returns a root node tree that contains all
 * the t_node from the singular linked list. In case of failure, it returns NULL.
 */
t_node	*create_tree(t_list *list);

/**
 * @brief This function free a tree.
 * @param tree t_node containing the root node to a tree.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	free_tree(t_node *tree);

/**
 * @brief This function counts the level or depth of a tree starting
 * from the root node.
 * @param root t_node containing the root node to a tree.
 * @return (size) if the root note doesn't exist, it returns -1. Otherwise,
 * it returns the levels of the given tree.
 */
size_t	tree_height(t_node *root);

/**
 * @brief This function allocates the necessary memory to create dictionary.
 * Its size will depend on the column size.
 * @param column The size of the biggest encoded character.
 * @return (char) If the function could not allocate sufficient memory, it
 * will return NULL. Otherwise, it will return the necessary memory to fill
 * the dictionary.
 */
char	**init_dictionary(size_t column);

/**
 * @brief This function creates a dictionary of encoded characters.
 * @param dict The dictionary to be filled.
 * @param root t_node containing the root node to a tree.
 * @param path The path in a tree until a leaf is found. The path receives
 * a sequence of 0 and 1 where 0 is a node to the right and 1 is a node to
 * the left.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	generate_dictionary(char **dict, t_node *root, char *path, size_t column);

/**
 * @brief This function free a dictionary.
 * @param tree The bidimensional array storing the dictionary.
 * @return (void) Successfully do the operations descrited at brief.
 */
void	free_dictionary(char **dictionary);

/**
 * @brief This function converts the file context stored in the second
 * parameter to a stream of 0's and 1's.
 * @param dictionary The dicionary to search for a character and get
 * its corresponding encoded character.
 * @param txt The string that has the content of the file.
 * @return (char) Successfully returns the encoded string. Otherwise,
 * it returns NULL if the function could not allocate enough memory
 * for the operation.
 */
char	*encode(char **dictionary, u_char *txt);

/**
 * @brief This function receives the encoded string and compress it 
 * to binary. The result is written in a binary file, which is the
 * compressed file.
 * @param str The encoded text to be zipped.
 * @return (void) Successfully do the operations descrited at brief.
 * Otherwise, it exits with err_exit() if something go wrong.
 */
void	compression(char *str);

/**
 * @brief This function counts each byte on a given file and returns
 * its total size.
 * @param filename The filename to get its size.
 * @param read_mode Its the same second parameter of the function
 * fopen(). It says how the file should be read.
 * @return (size_t) Successfully returns the file size. Otherwise, the
 * function exits with err_exit() the file does not exist or could not
 * be read.
 */
char	*decode(u_char *encoded_txt, t_node *root);

/**
 * @brief This function decompress a binary file. To this, the function needs
 * the encoded text of the original file and its huffman tree.
 * @param encoded_txt The encoded text of the original file.
 * @param root The built Huffman tree of the original file.
 * @return (void) Successfully decompress the binary file and return the data
 * the was zipped, i.e. the original file content. Otherwise, it returns
 * NULL if the function could not open or read the binary file.
 */
u_char	*decompression(size_t encoded_txt, t_node *root);

/**
 * @brief This function counts each byte on a given file and returns
 * its total size.
 * @param filename The filename to get its size.
 * @param read_mode Its the same second parameter of the function
 * fopen(). It says how the file should be read.
 * @return (size_t) Successfully returns the file size. Otherwise, the
 * function exits with err_exit() the file does not exist or could not
 * be read.
 */
size_t	get_file_size(char *filename, char *read_mode);

/**
 * @brief This function reads the content of a file and stores its text
 * in the first variable passed as a parameter.
 * @param txt The string to store the content of the file.
 * @param filename The file to be read.
 * @return (void) Successfully returns the file content stored in the
 * first parameter. Otherwise, the function exits with err_exit() 
 * the file does not exist or could not be read.
 */
void	read_txt_file(u_char *txt, char *filename);

#endif