g++ -std=c++0x -o ./ej3 ./ej3.cpp
g++ -std=c++0x -o ./generador ./generador.cpp

rm tests/*.dat

for (( i = 100; i <= 10000; i=i+100 )); do
	#GENERADOR [CANT_NODOS] [%FABRICAS] [%RUTAS] [PESO_MAX] [$RANDOM]

	./generador $i 50 50 150 $RANDOM > /tmp/nodo-fijo-denso.tmp
	./ej3 < /tmp/nodo-fijo-denso.tmp 1>> /dev/null 2>> tests/nodo-fijo-denso.dat

	#statements
done

