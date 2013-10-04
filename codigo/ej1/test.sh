

# Vamos a testear de 100 en 100 en cantidad de trabajos
# con un random modulo 150 para no poner valores mas grandes q 150
# despues pruebo desde 100 a 15000 de 100 en 100, en cada iteracion el programa se corre 
# y despues el programa se ejecuta 100 veces para cada instancia y se calcula el promedio


g++ -std=c++0x -o ./ej1 ./ej1.cpp
g++ -std=c++0x -o ./generador ./generador.cpp
rm tests/in/*.in
rm tests/test.out
rm tests/test.dat

echo "Corriendo tests ... Iteración: "
for ((it=15000; it<=15000; it=it+100))
do
	echo -n "$it "
	
	./generador $it 1> tests/test.in
	cat tests/test.in | ./ej1 1>> /dev/null 2>> tests/test.dat
done
echo " --> Terminé!"
