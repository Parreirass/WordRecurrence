# WordRecurrence
AEDS II | CEFET-MG

<div style="display: inline-block;">    
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<p> </p>
<p> </p>

## Proposta de Projeto
Esse projeto tem como proposta a leitura de múltiplos arquivos de texto (`.txt`) e a análise da recorrência de palavras ao longo de todos os textos.
Existem algumas regras para a análise textual ser feita corretamente:
- É necessário usar uma estrutura `HASH` para o armazenamento das palavras.
  - São consideradas palavras apenas aquelas que possuem todos os caracteres presentes na tabela `ASCII`.
  - Sinais de pontuação são removidos antes da análise de palavras.
- A recorrência deve ser feita utilizando uma estrutura `HEAP`.
- As `N` palavras mais recorrentes devem ser exibidas no terminal ao fim da execução.
- Existe um arquivo chamado `stopwords.csv` que contém palavras consideradas como *stopwords*, elas não devem ser consideradas como palavras à serem analisadas as recorrências. Caso fossem consideradas como palavras comuns, elas iriam ser as que mais apareceriam nos textos.

|          Sinais de pontuação  | Stop words                                      |
|-------------------------------|-------------------------------------------------|
| `.`,   `!`,   `?`                   |   `artigos(a, o, as,os) ou conjunções(e, ou) `  |


## Arquivos e funções
O projeto é dividido entre três arquivos de códigos própriamente ditos: `leitura.hpp`, `leitura.cpp` e `main.cpp`.

|  Arquivo                        |   Função                                                                                          |
| ------------------------------- | ------------------------------------------------------------------------------------------------- |
|  `main.cpp`                       | Arquivo principal para iniciar e chamar as funções do código                                                    |
|  `leitura.hpp`                  | Define as funções e as estruturas que foram utilizadas no código |
|  `leitura.cpp`                  | Contém o escopo de todas as funções que foram utilizadas |
| `stopwords.csv` | arquivo que contem as stop words|
| `arquivo_de_leitura.txt` | um dos arquivos de entrada principal no qual será feita toda a análise |

> O arquivo `main.cpp` "chama" apenas uma função definida no `leitura.hpp` e processada no `leitura.cpp`, chamada `readPrincipal()`. Ela, por sua vez, organiza todo o processo e as demais funções presentes no projeto. 

## Lógica Implementada

Como foi dito anteriormente, apenas a função `readPrincipal()` é "chamada" na *main.cpp*. Tal função começa inicializando as variáveis necessárias para o funcionamento do código. Além das variáveis consideradas "comuns", como as do tipo *int*, *bool* e *string*, uma struct chamada `palavra_q` armazena a quantidade de cada palavra nos arquivos de texto.
Logo em seguida, uma estrutura é apresentada no código, chamada `unordered_map`, seu funcionamento de baseia em uma tabela HASH.
- `unordered_map` é uma classe da biblioteca padrão do C++ que implementa uma estrutura de dados de tabela hash. Ela funciona como um armazenamento associativo e é utilizada para alocar pares chave-valor, onde cada chave é única e mapeia para um único valor. Essa estrutura se diferencia de um `map` na característica de que a primeira não ordena os elementos, diferentemente da segunda.
- Na situação apresentada, a tabela hash funciona como armazenamento de palavras e também a sua recorrência dentro dos arquivos de texto. Por possuir um tempo de acesso constante *(O(1))*, o extenso número de palavras dos textos não compromete a execução que pode ser feita em um tempo médio relativamente baixo, considerando a massa de dados.

<figure align="center">
    <img src="img/unordered.webp" alt="unordered_map">
    <figcaption><h6>Exemplo de funcionamento da tabela HASH por trás de uma estrutura unordered_map.<h6></figcaption>
</figure>

Partindo para o funcionamento do programa, um *vector* armazena o nome dos arquivos de texto que serão lidos, e seu tamanho irá coordenar quantas vezes uma estrutura `for` irá repetir (cada repetição processa um arquivo de texto).
Caso o arquivo de texto tenha sido aberto corretamente, o processamento do texto finalmente iniciará. Enquanto houverem linhas no arquivo de texto, os seguintes passos serão seguidos acompanhados das suas respectivas funções, linha por linha:
- Todas as letras de todas as palavras serão transformadas em *minúsculas* utilizando o comando `tolower()`, além disso as letras acentuadas também serão transformadas em *minúsculas* (`converterAcentuadasParaMinusculas()`).
- As possíveis reticências presentes na linha também serão retiradas (`tiraReticencia()`).
- 

## Compilação e Execução
Esse exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

| Comando                |  Função                                                                                           |
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

<p> </p>

#### Felipe Parreiras
<div style="display: inline-block;">
<a href="https://t.me/fparreiras">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/felipe-parreiras-56b075277/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

