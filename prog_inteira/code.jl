import Pkg

Pkg.activate(@__DIR__)
Pkg.instantiate()

# Pkg.add("JuMP")
# Pkg.add("HiGHS")

using JuMP
using HiGHS

# Instancia Uma instancia é composta por uma unica capacidade c, n itens, e m
# arestas.

# Objetivo Determinar quais itens serao colocados na mochila, de forma a maxi-
# mizar a soma do lucro dos itens, enquanto respeitando as restri¸c˜oes de
# que: a soma dos pesos dos itens selecionados nao pode ultrapassar a
# capacidade da mochila; se existe uma aresta (i, j), onde i e j s˜ao dois
# items, a mochila nao pode conter os itens i e j simultaneamente (i.e. a
# mochila pode ter nenhum dos dois itens, ou s´o o item i, ou s´o o item
# j, mas nao os itens i e j).

function knapsack_problem(
	c::Int,
	n::Int,
	p::Vector{Int},
	w::Vector{Int},
	E::Vector{Tuple{Int, Int}}
)
	# Constrói o modelo.
	model = Model(HiGHS.Optimizer)

	@variable(model, escolha[1:n], Bin)
	@objective(model, Max, p' * escolha)
	@constraint(model, w' * escolha <= c)
	for e in E @constraint(model, escolha[e[1]] + escolha[e[2]] <= 1) end

	optimize!(model)

	@show value.(escolha)
	@show objective_value(model)
end

c = 9
n = 10

p = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
w = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
E = [(1, 2), (3, 4)]

knapsack_problem(c, n, p, w, E)
