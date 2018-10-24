# virtmem
Operating Systems and Networks - Virtual Memory Assignment (Tarea 2)

Emilio Vélez

Problemas:

21/10:
Error por uso de malloc(solucionado)
Problemas "out of bound" (solucionado)
Random genera errores(solucionado)

22/10:
Loop infinito (solucionado)
Método implementado no funciona (Eliminado)
incoherencias en resultados (solucionado)
segmentation fault(en revision)
modificar input programa con flags (REVISAR)

23/10:
-Empezar todo denuevo
-uninitialized in this function [-Wmaybe-uninitialized] (solucionado)
-Error de uso de memoria en la funcion de añadir nodo (solucioando)
-Error causado por uso de Do While en vez de While(solucionado)
-Error causado por uso de recursividad en las funciones (solucionado)

Informe:

Para esta tarea se debió implementar un algoritmo de reemplazo de páginas. Método FIFO, Random y uno custom creado por nosotros; elegí uno simple y totalmente arbitrario y sin intención de eficiencia. Un método circular en el cual libera el ultimo, penultimo, antepenultimo, hasta llegar al primero para comenzar denuevo, es una especie de fifo alreves por lo que a veces eliminara al mas nuevo y otras al mas viejo.

Si tratara de predecir los resultados mi custom se comportara similar al FIFO y el random tendra comportamientos diferentes a los dos. no sé si en algunos casos mejores o peores.

Luego de probar cada uno de los algoritmos con los diferentes programas obtuve los siguiente resultados:



------------------------------------------------------------------------------------------
				         SCAN
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 custom scan
scan result is 522240000
Pages Faults: 1080
Disk Writes: 1065
Disk Reads: 1080
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 fifo scan
scan result is 522240000
Pages Faults: 1100
Disk Writes: 1085
Disk Reads: 1100
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 random scan
scan result is 522240000
Pages Faults: 1099
Disk Writes: 1084
Disk Reads: 1099





					FOCUS
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 custom focus
focus result is -2533
Pages Faults: 281
Disk Writes: 266
Disk Reads: 281
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 fifo focus
focus result is -2533
Pages Faults: 279
Disk Writes: 264
Disk Reads: 279
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 random focus
focus result is -2533
Pages Faults: 283
Disk Writes: 268
Disk Reads: 283




					SORT

pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 custom sort
sort result is -311357
Pages Faults: 797
Disk Writes: 782
Disk Reads: 797
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 fifo sort
sort result is -5576384
Pages Faults: 726
Disk Writes: 711
Disk Reads: 726
pbn@pbn-VirtualBox:~/Desktop/Tarea2/tarea-2-tarea-2-ev-master$ ./virtmem 100 15 random sort
sort result is -311357
Pages Faults: 883
Disk Writes: 868
Disk Reads: 883


--------------------------------------------------------------------------------------------

Con estos resultados podemos ver que custom no genera tanta falta de paginas en scan y podría llegar a ser más ultil en comparacion a rand y fifo.
En sort random tuvo el peor desempeño seguido de lejos por custom, siendo el mejor fifo.
En focus los resutados fueron similares, debera compararse para otra cantidad de frames, y no se llega a conclusion clara.

Podemos concluir de este trabajo que no hay métodos mejores ni peores que otros, dependera de la tarea que se quiera realizar. Tambien aprendí a la fuerza que WHILE no es lo mismo que DO-WHILE aun que son parecidos, error que me hizo tener que partir todo denuevo.

