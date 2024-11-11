## Programa e Bloco

```txt
<programa>::= program <identificador> ; <bloco> .

<bloco> ::= <parte de declarações de variáveis> <comando composto>
```
 

## Declarações

```txt
<parte de declarações de variáveis> ::= { var <declaração de variáveis> {; <declaração de variáveis>} ; }

<declaração de variáveis> ::=<lista de identificadores> : <tipo>

<lista de identificadores> ::= <identificador> { , <identificador> }

<tipo> ::= integer  | real
```
 

## Comandos

```txt
<comando composto> ::= begin <comando> ; { <comando> ; } end

<comado> ::= <atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>

<atribuição> ::= <variável> := <expressão>

<comando condicional> ::= if <expressão> then <comando> [ else <comando> ]

<comando repetitivo> ::= while <expressão> do <comando>
```
 

## Expressões

```txt
<expressão> ::= <expressão simples> [ <relação> <expressão simples> ]

<relação> ::= = | <> | < | <= | >= | >

<expressão simples> ::= [ + | - ] <termo> { ( + | -  ) <termo> }

<termo> ::= <fator> { ( * | /  ) <fator> }

<fator> ::= <variável> | <número> | ( <expressão> )

<variável> ::= <identificador>
```