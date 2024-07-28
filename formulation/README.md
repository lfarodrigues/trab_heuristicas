# Knapsack with Conflict Graph

## Instancia

Uma instancia é composta por uma unica capacidade c, n itens, e m arestas.

## Objetivo

Determinar quais itens serao colocados na mochila, de forma a maximizar a soma do lucro dos itens, enquanto respeitando as restrições de que a soma dos pesos dos itens selecionados nao pode ultrapassar a capacidade da mochila; se existe uma aresta (i, j), onde i e j s˜ao dois items, a mochila nao pode conter os itens i e j simultaneamente (i.e. a mochila pode ter nenhum dos dois itens, ou s´o o item i, ou s´o o item j, mas nao os itens i e j).

# Execução

Basta executar na linha de comando da seguinte forma:

```sh
julia code.jl <Caminho_Arquivo :: String> --seed=<Seed :: Int> --limit=<Limite (s) :: Int>
```

Ambos `seed` e `limit` são opcionais.

## Requisitos

- Julia
	- JuMP
	- HiGHS

Para instalar os pacotes necessários, basta executar os seguintes comandos em um terminal julia:

```jl
Pkg.add("JuMP")
Pkg.add("HiGHS")
```
