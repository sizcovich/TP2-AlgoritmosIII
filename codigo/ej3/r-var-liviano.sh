g++ -std=c++0x -o ./ej3 ./ej3.cpp
g++ -std=c++0x -o ./generador ./generador.cpp

nombre=r-var-liviano

echo "Config: 3000 nodos, 1% fabricas, 1% a 100% rutas, 150 peso max" > tests/$nombre.dat

for (( i = 1; i <= 100; i++ )); do
	#GENERADOR [CANT_NODOS] [%FABRICAS] [%RUTAS] [PESO_MAX] [$RANDOM]
	# echo -n ".$i."		
	echo -n "$i " >> tests/$nombre.dat
	./generador 3000 1 $i 150 $RANDOM > /tmp/$nombre.tmp 
	./ej3 < /tmp/$nombre.tmp 1> /dev/null 2>> tests/$nombre.dat

	#statements
done

