################################################################################
##                                  42 LABS                                   ##
################################################################################

NAME		:= 42labs

ENCODER		:= encoder
DECODER		:= decoder

BIN_FILE	:= encoded.ft

CC			:= cc
CYAN  		:= \33[1;36m
RESET 		:= \033[0m
LOG   		:= printf "[$(CYAN)INFO$(RESET)] %s\n"

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR   := obj
INC_DIRS  := include
SRC_DIRS  := huffman_zip data_operations ipc enc_prog dec_prog
SRC_DIRS  := $(addprefix src/, $(SRC_DIRS))
SRC_DIRS  += src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

HEADERS := huffman.h sem_shm.h encoder.h decoder.h

SOURCES_ENC := encoder.c
SOURCES_ENC += huff_decode.c huff_dictionary.c huff_encode.c
SOURCES_ENC += huff_list.c huff_table.c huff_tree.c file.c
SOURCES_ENC += ipc_error.c ipc_sem.c ipc_shm.c enc_utils.c
SOURCES_ENC += dec_utils.c enc_sections.c dec_sections.c

SOURCES_DEC := decoder.c
SOURCES_DEC += huff_decode.c huff_dictionary.c huff_encode.c
SOURCES_DEC += huff_list.c huff_table.c huff_tree.c file.c
SOURCES_DEC += ipc_error.c ipc_sem.c ipc_shm.c enc_utils.c
SOURCES_DEC += dec_utils.c enc_sections.c dec_sections.c

OBJS_ENC := $(addprefix $(OBJ_DIR)/, $(SOURCES_ENC:.c=.o))
OBJS_DEC := $(addprefix $(OBJ_DIR)/, $(SOURCES_DEC:.c=.o))

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))

all: $(NAME)

$(NAME):	$(ENCODER) $(DECODER)

$(ENCODER):	$(OBJS_ENC)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ -lrt -lpthread -o $@

$(DECODER):	$(OBJS_DEC)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ -lrt -lpthread -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(LOG) "Compiling $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

clean:
	@$(RM) -r $(OBJS_ENC) $(OBJS_DEC)
	@$(LOG) "Removing objects"
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing objects directory"

fclean: clean
	@$(RM) -r $(ENCODER) $(DECODER) $(BIN_FILE)
	@$(LOG) "Removing $(ENCODER) $(DECODER)"

re: fclean all

.PHONY: all clean fclean re
