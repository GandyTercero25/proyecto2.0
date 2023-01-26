/* Sistema de citas 
PENDIENTES:
* Establecer costos de la cita (Posible)
* Crear documento txt donde se puedan visualizar las citas generadas (Pendiente, por el momento sale por consola la informacion)
* Correccion de errores (Faltan unos cuantos errores por corregir)
* funcion para imprimir la informacion de citas en un docuemnto txt (opcion 4. Exportar citas) REALIZADO
* ordenar las citas por orden de fecha al ser exportadas
*/


#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CITAS 100

struct cita {
    char nombre_paciente[100];
    char informacion_contacto[100];
    char fecha_hora[20];
};

int contador_citas = 0;
struct cita citas[MAX_CITAS];

void agendar_cita() {
    if (contador_citas == MAX_CITAS) {
        printf("Lo siento, no se pueden agendar mas citas en este momento. Por favor intente mas tarde.\n");
        return;
    }

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", citas[contador_citas].nombre_paciente);

    printf("Ingrese la informacion de contacto del paciente (teléfono o correo electronico): ");
    scanf("%s", citas[contador_citas].informacion_contacto);


    /* se utiliza para ingresar una fecha en formato "dd/mm/yyyy" a través de la función scanf() y 
    almacenarla en una estructura de tipo tm llamada "fecha". Luego se realiza una operación en la que el valor 
    del campo tm_mon se decrementa en 1 para reflejar el mes en formato de índice (0-11 en lugar de 1-12), y el 
    campo tm_year se decrementa en 1900 para reflejar el año en formato de tiempo desde 1900. Finalmente, se 
    utiliza la función strftime() para formatear la fecha y almacenarla en el campo "fecha_hora" del arreglo "citas"
    en el formato "dd/mm/yyyy".*/

    struct tm fecha;
    printf("Ingrese la fecha de la cita (formato: dd/mm/yyyy): ");
    scanf("%d/%d/%d", &fecha.tm_mday, &fecha.tm_mon, &fecha.tm_year);
    fecha.tm_mon--;
    fecha.tm_year -= 1900;
    strftime(citas[contador_citas].fecha_hora, sizeof(citas[contador_citas].fecha_hora), "%d/%m/%Y", &fecha);
    
    int i;
    for(i=0;i<contador_citas;i++) {
        if(strcmp(citas[i].fecha_hora, citas[contador_citas].fecha_hora) == 0) {
            printf("Ya existe una cita para esa fecha, por favor seleccione otra fecha");
            return;
        }
    }


    printf("Cita agendada exitosamente para el paciente %s en la fecha especificada.\n", citas[contador_citas].nombre_paciente);
    contador_citas++;
}

void cancelar_cita() {
    char fecha[20];
    printf("Ingrese la fecha de la cita a cancelar (formato: dd/mm/yyyy): ");
    scanf("%s", fecha);

    int i, encontrado = 0;
    for (i = 0; i < contador_citas; i++) {
        if (strcmp(citas[i].fecha_hora, fecha) == 0) {
            printf("Cita cancelada exitosamente para el paciente %s en la fecha especificada.\n", citas[i].nombre_paciente);
            int j;
            for (j = i; j < contador_citas - 1; j++) {
                citas[j] = citas[j + 1];
            }
            contador_citas--;
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("No se ha encontrado ninguna cita para la fecha especificada.\n");
    }
}

void ver_citas() {
    int i;
    if (contador_citas == 0) {
        printf("No hay citas agendadas.\n");
    } else {
        printf("Citas agendadas:\n");
        for (i = 0; i < contador_citas; i++) {
            printf("- Paciente: %s, Contacto: %s, Fecha: %s\n", citas[i].nombre_paciente, citas[i].informacion_contacto, citas[i].fecha_hora);
        }
    }
}

// Funcion exportar citas en proceso....


void exportar_citas() {
    FILE *archivo;
    archivo = fopen("citas.txt", "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        return;
    }

    int i;
    for (i = 0; i < contador_citas; i++) {
        fprintf(archivo, "Paciente: %s, Contacto: %s, Fecha: %s\n", citas[i].nombre_paciente, citas[i].informacion_contacto, citas[i].fecha_hora);
    }

    fclose(archivo);
    printf("Citas exportadas exitosamente al archivo citas.txt.\n");
}

int main() {
    while (1) {
        printf("Menu de opciones:\n");
        printf("1. Agendar cita\n");
        printf("2. Cancelar cita\n");
        printf("3. Ver citas\n");
        printf("4. Exportar citas\n");
        printf("5. Salir\n");

        int opcion;
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agendar_cita();
                break;
            case 2:
                cancelar_cita();
                break;
            case 3:
                ver_citas();
                break;
            case 4:
                exportar_citas();
                break;
            case 5:
                return 0;
            default:
                printf("Opcion invalida. Por favor seleccione una opcion valida del menu.\n");
                break;
        }
    }
}


