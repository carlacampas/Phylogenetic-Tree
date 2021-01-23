OPCIONS = -std=c++11 -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare

program.exe: program.cc Cjt_clusters.o Cjt_especies.o Especie.o
	g++ -o program.exe program.cc Cjt_clusters.o Cjt_especies.o Especie.o $(OPCIONS)

Cjt_clusters.o: Cjt_clusters.cc Cjt_especies.hh Especie.hh BinTree.hh
	g++ -c Cjt_clusters.cc $(OPCIONS)

Cjt_especies.o: Cjt_especies.cc Especie.hh
	g++ -c Cjt_especies.cc $(OPCIONS)

Especie.o: Especie.cc
	g++ -c Especie.cc $(OPCIONS)
