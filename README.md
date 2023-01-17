# Olá, seja bem-vindo! 👋🏻

## Considerações iniciais sobre o Labs 4º Edição

Este README.md descreve de maneira sucinta o desafio para a 4º edição do Labs. Caso queira ler o programa de necessidades (subject) completo do desafio e/ou ler detalhadamente sobre a implementação do projeto, consulte o GitHub Wiki correspondente na aba `Wiki` ou diretamente neste link: (https://github.com/ygor-sena/42-labs-challenge-v4/wiki)

## Sobre o projeto

O Labs 4º Edição ocorreu entre os dias 09/01/2023 e 15/01/2023.
O projeto desta edição consiste na implementação de dois programas, `encoder`e `decoder`, com comunicação via memória compartilhada para comprimir e descomprimir um arquivo. O primeiro programa, `encoder`, recebe um arquivo de texto a ser comprimido; o segundo, `decoder`, devolverá ao primeiro uma série de dados sobre o resultado da descompressão a partir das informações iniciais fornecidas pelo `encoder`. O projeto deve ser programado em C e nenhuma biblioteca externa à padrão é permitida.

## Compilação, utilização e funcionamento do projeto

#### 1) Copie este repositório para sua estação de trabalho local

```html
git clone git@github.com:42sp/42labs-selection-process-v4-ygor-sena.git
```

#### 2) Compile o projeto com Makefile

```html
make
```

#### 3) Abra duas instâncias do terminal de comandos e, em um deles, inicialize o programa `decoder`

```html
./decoder
```

Caso queira executar o programa procurando por vazamentos de memória, basta inicializá-lo da seguinte maneira:

```html
valgrind --leak-check=full --show-leak-kinds=all ./decoder
```

#### 4) No outro terminal, inicialize o programa `encoder`

```html
./encoder example.txt
```

O `encoder` lerá o arquivo example.txt, fará sua compressão e enviará informações para descompressão ao `decoder`. Enquanto recebe e processa as informações, o `decoder` exibirá na saída padrão do terminal a mensagem `Waiting for encoder data...`. Após decomprimir o arquivo, o encoder envia as informações sobre o resultado da compilação de volta ao `encoder` e este exibe-as no prompt de comando.

#### 5) Exemplo de utilização

Como exemplo dos resultados de saída do programa mencioados anteriomente, se criarmos um arquivo de teste utilizando o comando...

```
 yes "O melhor lorem ipsum do mundis." | head -c 30 > 30BYTES.txt
```

... o resultado exibido pelo `encoder` será algo semelhante a isto:

```
Unzipped text is: O melhor lorem ipsum do mundis
File size in bytes: 31
Total bytes compressed: 16
Decompression time is: 0.003033
```

## Ferramentas utilizadas

Foram utilizados durante o desafio ferramentas de planejamento e desenvolvimento de projeto, como [Jira Software](https://www.atlassian.com/software/jira?&aceid=&adposition=&adgroup=144583555677&campaign=19313279983&creative=642044821574&device=c&keyword=jira&matchtype=e&network=g&placement=&ds_kids=p74591032830&ds_e=GOOGLE&ds_eid=700000001558501&ds_e1=GOOGLE&gclid=CjwKCAiA5Y6eBhAbEiwA_2ZWIVs7OG0HiV4C44cOCe5FxJGUo46e__WcWF0gflyWMFt_ER08gwYGChoCdeIQAvD_BwE&gclsrc=aw.ds) e fluxo de trabalho por troncos (branch workflow) no prsente GitHub, [Effie](https://www.effie.pro/) para compilação de referências, anotação e visualização de ideias. Para maiores detalhes, consultar a seção correspondente no [GitHub Wiki](https://github.com/ygor-sena/42-labs-challenge-v4/wiki/Ferramentas-utilizadas) do projeto.

## Conceitos aprendidos durante o processo

- Algoritmos greedy 
- Algoritmos de compressão
- Tipos de criptografia
- Árvores e listas encadeadas
- IPC através de memória compartilhada
- IPC através de semáforos
- Operações bitwise
- Leitura e escrita de arquivos
- Conversão de tipos em C
- Organização de fluxo de trabalho
- Planejamento das etapas de desenvolvimento
- Documentação de projeto

## Recursos implementados

#### Mandatório: 
- ✅ Implementação completa do algoritmo de Huffman
- ✅ Compressão e descompressão utilizando o algoritmo supramencionado
- ✅ Comunicação via memória compartilhada
- ✅ Exibição das informações do `decoder` pelo `encoder`
- ✅ README.md básico

#### Bônus:
- ✅ Uso de ferramentas externas para planejamento nas etapas de desenvolvimento
- ❌ Compressão de múltiplos arquivos binários.
- ❌ Criptografia do dado comprimido, utilizando senha fornecida pelo usuário.
- ❌ Verificação de integridade do arquivo comprimido.
- ❌ Opção para escolher mais outro algoritmo de compressão a ser utilizado.

## Referências de projeto

Consultar seção correspondente no [GitHub Wiki](https://github.com/ygor-sena/42-labs-challenge-v4/wiki/Refer%C3%AAncias-de-projeto) do projeto.
