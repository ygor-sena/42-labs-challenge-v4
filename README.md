# Hi, welcome to this page! 👋🏻

##### ⚠️ Caso você não entenda inglês, leia a versão deste README em português [neste link](https://github.com/ygor-sena/42-labs-challenge-v4/blob/main/README-pt.md). ⚠️

## Initial thoughts on Labs 4th Edition

This README.md succinctly describes the challenge for the 4th edition of the Labs. In case you want to read the complete subject of the challenge and/or read in detail about the implementation of the project, check the corresponding GitHub Wiki in the `Wiki` tab or directly in this link: (https://github.com/ygor-sena/42-labs-challenge-v4/wiki)

## About the project

The Labs 4th Edition took place between January 09th, 2023 and January 15th, 2023.
The project of this edition consists of the implementation of two programs, `encoder` and `decoder`, with communication via shared memory to compress and decompress a file. The first program, `encoder`, receives a text file to be compressed; the second, `decoder`, will return to the first a series of data about the result of the decompression from the initial information provided by the `encoder`. The project must be programmed in C and no library outside the standard C ANSI is allowed.

## Compiling, using and running the project

#### 1) Copy this repository to your local workstation

```html
git clone git@github.com:42sp/42labs-selection-process-v4-ygor-sena.git
```

#### 2) Compile the project with Makefile

```html
make
```

#### 3) Open two instances of the command terminal and, in one of them, launch the `decoder` program

```html
./decoder
```

If you want to run the program looking for memory leaks, just start it as follows:

```html
valgrind --leak-check=full --show-leak-kinds=all ./decoder
```

#### 4) In the other terminal, launch the `encoder` program

```html
./encoder example.txt
```

The `encoder` will read the example.txt file, compress it and send the information for decompression to the `decoder`. While receiving and processing the information, the `decoder` will display the message `Waiting for encoder data...` on the terminal's standard output. After decompressing the file, the `decoder` sends information about the compilation result back to the `encoder` which displays it at the command prompt.

#### 5) Usage example

As an example of the aforementioned program output results, if we create a test file using the command...

```
  yes "The best lorem ipsum in the world." | head -c 30 > 30BYTES.txt
```

... the output displayed by `encoder` will look something like this:

```
Unzipped text is: O melhor lorem ipsum do mundis
File size in bytes: 31
Total bytes compressed: 16
Decompression time is: 0.003033
```

## Tools used

Project planning and development tools were used during the challenge, such as [Jira Software](https://www.atlassian.com/software/jira?&aceid=&adposition=&adgroup=144583555677&campaign=19313279983&creative=642044821574&device=c&keyword=jira&matchtype=e&network=g&placement=&ds_kids=p74591032830&ds_e=GOOGLE&ds_eid=700000001558501&ds_e1=GOOGLE&gclid=CjwKCAiA5Y6eBhAbEiwA_2ZWIVs7OG0HiV4C44cOCe5FxJGUo46e__WcWF0gflyWMFt_ER08gwYGChoCdeIQAvD_BwE&gclsrc=aw.ds) and branch workflow on the present GitHub, [Effie](https://www.effie.pro/) for compiling references, annotating and visualizing ideas. For more details, consult the corresponding section in the [GitHub Wiki](https://github.com/ygor-sena/42-labs-challenge-v4/wiki/Tools-used) of the project.

## Concepts learned during the process

- Greedy algorithms
- Compression algorithms
- Types of encryption
- Trees and linked lists
- IPC through shared memory
- IPC through semaphores
- bitwise operations
- Reading and writing files
- Type conversion in C
- Workflow organization
- Planning of development stages
- Project documentation

## Implemented features

#### Mandatory:
- ✅ Full implementation of Huffman algorithm
- ✅ Compression and decompression using the above-mentioned algorithm
- ✅ Communication via shared memory
- ✅ Display of `decoder` information by `encoder`
- ✅ Basic README.md

#### Bonus:
- ✅ Use of external tools for planning in the development stages
- ❌ Compression of multiple binary files.
- ❌ Compressed data encryption, using password provided by the user.
- ❌ Compressed file integrity check.
- ❌ Option to choose another compression algorithm to be used.

## Project References

Check the corresponding section in the project's [GitHub Wiki](https://github.com/ygor-sena/42-labs-challenge-v4/wiki/Refer%C3%AAncias-de-projeto).
