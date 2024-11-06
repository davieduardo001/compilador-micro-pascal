
# Especificação de Sintaxe

## Programa e Bloco

### Programa

```plaintext
<programa> ::= 
program <identificador> ; <bloco> .
```

### Bloco

```plaintext
<bloco> ::= 
<parte de declarações de variáveis> <comando composto>
```

## Declarações

### Parte de Declarações de Variáveis

```plaintext
<parte de declarações de variáveis> ::= 
{ var <declaração de variáveis> {; <declaração de variáveis>} ; }
```

### Declaração de Variáveis

```plaintext
<declaração de variáveis> ::= 
<lista de identificadores> : <tipo>
```

#### Lista de Identificadores

```plaintext
<lista de identificadores> ::= 
<identificador> { , <identificador> }
```

#### Tipo

```plaintext
<tipo> ::= 
integer | real
```

## Comandos

### Comando Composto

```plaintext
<comando composto> ::= 
begin <comando> { ; <comando> } end
```

### Comando

```plaintext
<comando> ::= 
<atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>
```

#### Atribuição

```plaintext
<atribuição> ::= 
<variável> := <expressão>
```

#### Comando Condicional

```plaintext
<comando condicional> ::= 
if <expressão> then <comando> [ else <comando> ]
```

#### Comando Repetitivo

```plaintext
<comando repetitivo> ::= 
while <expressão> do <comando>
```

## Expressões

### Expressão

```plaintext
<expressão> ::= 
<expressão simples> [ <relação> <expressão simples> ]
```

### Relação

```plaintext
<relação> ::= 
= | <> | < | <= | >= | >
```

### Expressão Simples

```plaintext
<expressão simples> ::= 
[ + | - ] <termo> { ( + | - ) <termo> }
```

### Termo

```plaintext
<termo> ::= 
<fator> { ( * | / ) <fator> }
```

### Fator

```plaintext
<fator> ::= 
<variável> | <número> | ( <expressão> )
```

### Variável

```plaintext
<variável> ::= 
<identificador>
```