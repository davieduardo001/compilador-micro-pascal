# Analisador Léxico Simples

## Descrição

Este projeto implementa um **analisador léxico** que lê um arquivo de código-fonte e reconhece tokens de uma linguagem fictícia. O analisador identifica e categoriza tokens como:

- **Identificadores**
- **Palavras reservadas**
- **Operadores** (`+`, `-`, `*`, `/`, `>`, `<`, `=`, etc.)
- **Símbolos** (parênteses, chaves, ponto e vírgula, etc.)
- **Números**

O programa recebe um arquivo de entrada, realiza a análise léxica, e gera um arquivo de saída com os tokens identificados.

## Funcionalidades

- **Análise léxica**: Identificação de tokens no arquivo de entrada.
- **Relatório de erros léxicos**: Notificação de caracteres não reconhecidos com a linha e coluna correspondentes.
- **Suporte a múltiplos tokens**: Identificadores, palavras reservadas, operadores, símbolos e números.
- **Ajuda**: Opção de exibir informações de uso e lista de tokens suportados.
- **Geração de arquivo de saída**: Arquivo gerado com a extensão `.lex` que contém os tokens encontrados.

## Estrutura do Código

### Funções Principais

#### `int main(int argc, char *argv[])`
Função principal que coordena a execução do programa.

- **Parâmetros**:
  - `argc`: Contagem de argumentos passados para o programa.
  - `argv[]`: Lista de argumentos.
    - `argv[1]`: Arquivo de entrada.

- **Descrição**:
  - Verifica se o argumento do arquivo de entrada foi fornecido.
  - Abre o arquivo de entrada e o arquivo de saída.
  - Inicia a análise léxica chamando `analisar_lexico()`.
  - Gera um arquivo de saída com os tokens identificados.

#### `void exibir_ajuda(const char *nome_programa)`
Exibe a ajuda detalhada sobre como usar o programa.

- **Parâmetros**:
  - `nome_programa`: Nome do programa executável.

- **Descrição**:
  - Mostra exemplos de uso, opções suportadas e uma breve explicação sobre os tokens e funcionalidades.

#### `void exibir_lista_de_tokens()`
Exibe uma lista de todos os tokens suportados pelo compilador.

- **Descrição**:
  - Lista palavras reservadas, operadores, símbolos e outros tokens como identificadores e números.

#### `void analisar_lexico(FILE *arquivo, FILE *saida)`
Função responsável por analisar léxicamente o arquivo de entrada.

- **Parâmetros**:
  - `arquivo`: Ponteiro para o arquivo de entrada.
  - `saida`: Ponteiro para o arquivo de saída onde os tokens serão gravados.

- **Descrição**:
  - Lê o arquivo de entrada e identifica tokens como palavras reservadas, identificadores, operadores, números e símbolos.
  - Os tokens são gravados no arquivo de saída no formato `<TOKEN_NOME, TOKEN_LEXEMA> na linha X, coluna Y`.

#### `Token obter_token(FILE *arquivo)`
Função que obtém o próximo token do arquivo de entrada.

- **Parâmetros**:
  - `arquivo`: Ponteiro para o arquivo de entrada.

- **Retorno**:
  - `Token`: Estrutura que contém o nome e o lexema do token, assim como sua posição no arquivo.

- **Descrição**:
  - Lê caracteres do arquivo e identifica se o token é um identificador, palavra reservada, número, operador ou símbolo.
  - Retorna o token identificado.

#### `void iniciar_tabela_de_simbolos()`
Inicializa a tabela de símbolos com as palavras reservadas da linguagem.

- **Descrição**:
  - Prepara a tabela com as palavras reservadas da linguagem, como `program`, `var`, `integer`, etc.

#### `void reportar_erro(char *mensagem, int linha, int coluna)`
Reporta um erro léxico quando um caractere não reconhecido é encontrado.

- **Parâmetros**:
  - `mensagem`: Descrição do erro.
  - `linha`: Linha onde o erro ocorreu.
  - `coluna`: Coluna onde o erro ocorreu.

- **Descrição**:
  - Exibe uma mensagem de erro na cor vermelha, indicando o erro léxico e sua posição no arquivo.

### Estruturas

#### `typedef struct Token`
Estrutura que representa um token.

- **Campos**:
  - `char nome[MAX_TOKEN_LENGTH]`: Nome do token (ex: `ID`, `NUM`, `OP_AD`).
  - `char lexema[MAX_TOKEN_LENGTH]`: Lexema correspondente ao token.
  - `int linha`: Linha onde o token foi encontrado.
  - `int coluna`: Coluna onde o token foi encontrado.

### Arquivo de Saída

O programa gera um arquivo de saída com o nome do arquivo de entrada acrescido da extensão `.lex`. O arquivo contém uma linha para cada token identificado, no seguinte formato:

```
<TOKEN_NOME, TOKEN_LEXEMA> na linha X, coluna Y
```

Exemplo:
```
<ID, program> na linha 1, coluna 1
<ID, main> na linha 1, coluna 8
<SMB_OPA, ( > na linha 1, coluna 13
...
```

## Executando o Programa

### Sintaxe

```bash
./analisador_lexico <arquivo_de_entrada>
```

### Opções

- `-h` ou `--help`: Exibe a mensagem de ajuda.
- `--tokens`: Exibe a lista de tokens suportados pelo compilador.

### Exemplos

1. Para analisar um arquivo de código-fonte:

```bash
./analisador_lexico programa.txt
```

2. Para exibir a lista de tokens suportados:

```bash
./analisador_lexico --tokens
```

3. Para exibir a ajuda:

```bash
./analisador_lexico --help
```

## Tokens Suportados

### Palavras Reservadas

- `program`
- `var`
- `integer`
- `real`
- `begin`
- `end`
- `if`
- `then`
- `else`
- `while`
- `do`
- `write`
- `read`

### Operadores

- `+` (Adição)
- `-` (Subtração)
- `*` (Multiplicação)
- `/` (Divisão)
- `=` (Atribuição)
- `>` (Maior que)
- `>=` (Maior ou igual)
- `<` (Menor que)
- `<=` (Menor ou igual)
- `<>` (Diferente)
- `:=` (Atribuição)

### Símbolos

- `;` (Ponto e vírgula)
- `,` (Vírgula)
- `{` (Chave de abertura)
- `}` (Chave de fechamento)
- `(` (Parêntese de abertura)
- `)` (Parêntese de fechamento)
- `.` (Ponto final)
- `:` (Dois pontos)

### Outros Tokens

- `ID` (Identificadores)
- `NUM` (Números)

## Relatório de Erros Léxicos

Se o analisador léxico encontrar um caractere inválido no arquivo de entrada, ele gera uma mensagem de erro como esta:

```
Erro léxico: Caractere não reconhecido na linha X, coluna Y
```

## Requisitos

- **Compilador**: Para compilar este programa, é necessário um compilador C, como o GCC.
  
  Exemplo de comando para compilação:

  ```bash
  gcc -o analisador_lexico lexer.c
  ```

## Autores

Este código foi desenvolvido como parte de um projeto de desenvolvimento de um compilador.