# Simulated Annealing - Knapsack with Conflict Graph

# Intância

As instâncias do problema podem ser encontradas no subdiretório ./metaheuristicas/kcpg_instances. Cada arquivo ´e uma se¸c˜ao
data de uma formula¸c˜ao matem´atica do GLPK/MathProg2. Os parˆametros
n e c se referem ao n´umero de itens e a capacidade, respectivamente.
O set V se refere aos n´umeros de 0 a n − 1. Os parˆametros p e w
se referem aos lucros (profits) e pesos (weights) dos itens. O set E se
refere as arestas (edges) entre os itens (cada aresta ´e denotada por um
par de ´ındices de itens).

## Objetivo

Determinar quais itens serao colocados na mochila, de forma a maximizar a soma do lucro dos itens, enquanto respeitando as restrições de que a soma dos pesos dos itens selecionados nao pode ultrapassar a capacidade da mochila; se existe uma aresta (i, j), onde i e j s˜ao dois items, a mochila nao pode conter os itens i e j simultaneamente (i.e. a mochila pode ter nenhum dos dois itens, ou s´o o item i, ou s´o o item j, mas nao os itens i e j).


## Parâmetros do Algoritmo

- Temperatura inicial
- Temperatura final
- Taxa de resfriamento
- Número máximo de iterações

# Execução

Para sistemas Linux provemos o arquivo Makefile:

No diretório ./metaheuristic execute os seguintes comandos para compilar o código ou para remover binários
```sh
 make
 make clean
```

Para executar o programa escreva na linha de comando o caminho para a instância e a semente de aleatoriedade da seguinte forma:

```sh
 ./main <caminho> <semente>
```

## Requisitos
Compilador GCC com suporte para C++11

