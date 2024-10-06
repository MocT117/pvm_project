#include <stdio.h>
#include "pvm3.h"

int main() {
    int tid[4], i, rango, inicio = 1, fin = 100, suma_total = 0, suma_parcial;

    // Inicializar PVM y obtener ID del proceso máster
    pvm_mytid();
    
    // Lanzar 4 esclavos
    pvm_spawn("esclavo", NULL, PvmTaskDefault, NULL, 4, tid);
    
    // Dividir el rango y enviar los datos a los esclavos
    rango = (fin - inicio + 1) / 4;
    for (i = 0; i < 4; i++) {
        int inicio_esclavo = inicio + i * rango;
        int fin_esclavo = (i == 3) ? fin : inicio_esclavo + rango - 1;

        pvm_initsend(PvmDataDefault);
        pvm_pkint(&inicio_esclavo, 1, 1);
        pvm_pkint(&fin_esclavo, 1, 1);
        pvm_send(tid[i], 1);
    }
    
    // Recibir las sumas parciales de cada esclavo
    for (i = 0; i < 4; i++) {
        pvm_recv(tid[i], 1);
        pvm_upkint(&suma_parcial, 1, 1);
        suma_total += suma_parcial;
    }

    // Mostrar el resultado final
    printf("La suma total es: %d\n", suma_total);
    
    pvm_exit();
    return 0;
}

