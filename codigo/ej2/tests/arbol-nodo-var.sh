g++ -std=c++0x -o ./ej2-b ./ej2-b.cpp
g++ -std=c++0x -o ./genArbol ./genArboles.cpp

nombre=nodo-var

echo "Config: 200 a 100000 nodos, 150 peso max" > ./$nombre.dat

for (( i = 200; i <= 100000; i=i+200 )); do
	#GENERADOR [CANT_NODOS] [%FABRICAS] [%RUTAS] [PESO_MAX] [$RANDOM]
	# echo -n ".$i."		
	echo -n "$i " >> ./$nombre.dat
	./genArbol $i 150 $RANDOM > /tmp/$nombre.tmp 
	./ej2-b < /tmp/$nombre.tmp 1> /dev/null 2>> ./$nombre.dat

	#statements
done

