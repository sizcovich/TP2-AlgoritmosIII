g++ -std=c++0x -o ./ej3 ./ej3.cpp
g++ -std=c++0x -o ./generador ./generador.cpp

nombre=nodo-var-denso

echo "Config: 200 a 100000 nodos, 50% fabricas, 50% rutas, 150 peso max" > tests/$nombre.dat

for (( i = 200; i <= 100000; i=i+200 )); do
	#GENERADOR [CANT_NODOS] [%FABRICAS] [%RUTAS] [PESO_MAX] [$RANDOM]
	# echo -n ".$i."		
	echo -n "$i " >> tests/$nombre.dat
	./generador $i 50 50 150 $RANDOM > /tmp/$nombre.tmp 
	./ej3 < /tmp/$nombre.tmp 1> /dev/null 2>> tests/$nombre.dat

	#statements
done

