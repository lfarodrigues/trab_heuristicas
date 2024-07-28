# Trabalho Prático - Otimização combinatória
import Pkg

Pkg.activate(@__DIR__)
Pkg.instantiate()

# Pkg.add("JuMP")
# Pkg.add("HiGHS")

using JuMP
using HiGHS
using Random

# Instancia Uma instancia é composta por uma unica capacidade c, n itens, e m
# arestas.

# Objetivo Determinar quais itens serao colocados na mochila, de forma a maxi-
# mizar a soma do lucro dos itens, enquanto respeitando as restri¸c˜oes de
# que: a soma dos pesos dos itens selecionados nao pode ultrapassar a
# capacidade da mochila; se existe uma aresta (i, j), onde i e j s˜ao dois
# items, a mochila nao pode conter os itens i e j simultaneamente (i.e. a
# mochila pode ter nenhum dos dois itens, ou s´o o item i, ou s´o o item
# j, mas nao os itens i e j).

# Executa o modelo do problema da mochila com grafo de conflito
# Apenas printa na tela os resultados
function knapsack_problem(
	n::Int,	
	c::Int,	
	p::Vector{Int},
	w::Vector{Int},
	E::Vector{Tuple{Int, Int}},
	time_limit_sec::Int,
)
	# Constrói o modelo.
	model = Model(HiGHS.Optimizer)
	set_time_limit_sec(model, time_limit_sec)

	# Variável para cada escolha possível de item
	@variable(model, escolha[1:n], Bin)

	# Padrão do Knapsack problem
	# Objetivo é maximizar o valor escolhido	
	@objective(model, Max, p' * escolha)
	# Não pode exceder o peso da mochila
	@constraint(model, w' * escolha <= c)

	# Adiciona constraint para cada aresta de conflito
	# Garante que apenas 1 dos dois itens (ou nenhum) será escolhido se
	# houver aresta entre os itens
	for e in E @constraint(model, escolha[e[1]] + escolha[e[2]] <= 1) end

	optimize!(model)

	# Valor do modelo
	@show objective_value(model)

	# Capacidade utilizada
	@show value(sum(w' * escolha))

	# Itens escolhidos
	# @show value.(escolha)
	# Quantidade de itens escolhidos
	@show value(sum(escolha))	
end

# Função auxiliar para ler um int do arquivo de input
function parse_int(prefix::String, value::String)
	return parse(Int, strip(value[length(prefix)+1:length(value)-1]))
end

# Função auxiliar para ler uma tupla de valores do arquivo de input
function parse_tuple(value::String)
	S = split(strip(value), " ")
	T = []
	for p in S
		# as tuplas estão tabuladas no arquivo
		# isso causa diversos espaços em branco a mais no input
		isempty(p) && continue
		v = parse(Int, strip(p))
		push!(T, v)
	end
	return Tuple(T)
end

# Parsa o arquivo de input
# Retorna (n,c,p,w,E)
function parse_file(filepath::String)
	n = 0
	c = 0
	p = Int[]
	w = Int[]
	E = Tuple{Int,Int}[]

	open(filepath) do f		
			while !eof(f)	    	
				line = readline(f)

				if occursin("param n :=", line)
					n = parse_int("param n :=", line)
				end

				if occursin("param c :=", line)
					c = parse_int("param c :=", line)
				end

				if occursin("param : V : p w :=", line)
					while true
						line = readline(f)
						occursin(";", line) && break
						T = parse_tuple(line)
						push!(p, T[2])
						push!(w, T[3])
					end
				end				

				if occursin("set E :=", line)
					while true
						line = readline(f)
						occursin(";", line) && break
						T = parse_tuple(line)
						# Os índices estão 0-indexed
						# O +1 é para fazer com que sejam 1-indexed
						push!(E, (T[1] + 1, T[2] + 1))
					end
				end					
			end
	end

	println("n: ", n)
	println("c: ", c)
	println("p: ", length(p))
	println("w: ", length(w))
	println("E: ", length(E))

	return n, c, p, w, E
end

function print_usage()
	println("")
	println("Uso: julia code.jl <caminho> --seed=<semente> --limit=<limite (s)>")
	println("Parâmetros com nome são opcionais")	
end

# Garante que tem pelo menos 1 argumento
if length(ARGS) == 0
	println("ERROR: Faltaram parâmetros")
	print_usage()
	exit()
end

# Parâmetro de ajuda
if lowercase(ARGS[1]) == "-h" || lowercase(ARGS[1]) == "--help"
	print_usage()
	exit()
end

# Função auxiliar para parsar um int de um parâmetro nomeado
function parse_arg_int(name::String, default::Any)
	for arg in ARGS
		occursin(name, arg) || continue
		v = split(strip(arg), "=")
		return parse(Int, v[length(v)])
	end

	return default
end

# Função auxiliar para buscar o parâmetro principal
# Só pra garantir que a ordem que for passado as coisas não importa
function first_positional_param_string()
	for arg in ARGS
		isempty(strip(arg)) && continue
		startswith(strip(arg), "--") && continue
		return String(strip(arg))
	end

	println("ERROR: Faltou parâmetro posicional")
	print_usage()
	exit()
end

# Recebe os inputs da linha de comando
filepath = first_positional_param_string()
random_seed = parse_arg_int("--seed", nothing)
time_limit_sec = parse_arg_int("--limit", 3600)

println("Caminho: ", filepath)
println("Seed: ", random_seed)
println("Limite: ", time_limit_sec)

# Não tenho certeza se é aqui que devo setar a "semente de aleatoriedade"
# Não encontrei o uso disso nos slides nem nada
if random_seed != nothing
	Random.seed!(random_seed)
end

# Parsa o arquivo
n, c, p, w, E = parse_file(filepath)

# Executa o problema
knapsack_problem(n, c, p, w, E, time_limit_sec)
