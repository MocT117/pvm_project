#include <stdio.h>
#include "pvm3.h"

int main() {
    int inicio, fin, suma = 0;

    // Inicializar PVM
    pvm_mytid();
    
    // Recibir los datos del máster
    pvm_recv(-1, 1);
    pvm_upkint(&inicio, 1, 1);
    pvm_upkint(&fin, 1, 1);
    
    // Calcular la suma
    for (int i = inicio; i <= fin; i++) {
        suma += i;
    }
    
    // Enviar la suma al máster
    pvm_initsend(PvmDataDefault);
    pvm_pkint(&suma, 1, 1);
    pvm_send(pvm_parent(), 1);
    
    pvm_exit();
    return 0;
}

