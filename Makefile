
# Universidade Federal de Pelotas
# Ciencia da Computacao
# Matrizes com Multithreads em C++11
# Rodrigo Oliveira
# Gerson Cavalheiro

#########################################################################

tudo: comp help

comp: makeMatrix.cpp

	@echo  ..............................................................
	@echo   Making...

	g++ -std=c++11 -pthread makeMatrix.cpp -o mkm

help:
	@echo  ..............................................................
	@echo   
	@echo   Exemplo:
	@echo   Para criar uma matriz 100x100, densidade 10%, valor minimo -300, maximo 300, elemento nulo 0,
	@echo   digite:
	@echo   ./mkm 100 100 dens=0.1 min=-300 max=300 null=0
	@echo   
	@echo   Os parametros densidade, valor minimo, valor maximo e elemento nulo sao opcionais.
	@echo   Se nao informados, os valores sao, respectivamente, 100%, menor e maior aleatorios e zero.
	@echo   
	@echo  ..............................................................
	@echo

clean:
	@rm mkm* || tru
