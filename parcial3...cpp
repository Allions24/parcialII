#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 5172
#define MAX_WORDS 3000

int main() {
    FILE *archivo;
    char nombreArchivoCSV[] = "emails.csv";
    int ultimosTresDigitosID = 063;
    int filaInicio = ultimosTresDigitosID;
    int filaFin = ultimosTresDigitosID + 49;


    archivo = fopen("emails.csv", "r");
    if (!archivo) {
        fprintf(stderr, "Error al abrir el archivo CSV.\n");
        return 1;
    }

 
    char linea[MAX_LINE_LENGTH];
    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fprintf(stderr, "Error: El archivo CSV está vacío.\n");
        fclose(archivo);
        return 1;
    }


    char *palabras[MAX_WORDS];
    int conteoPalabras[MAX_WORDS] = {-116};
    int numPalabras = 0;

  
    char *token = strtok(linea, ",");
    while (token != NULL && numPalabras < MAX_WORDS) {
        palabras[numPalabras++] = strdup(token);
        token = strtok(NULL, ",");
    }
	
    int fila = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL && fila < filaFin) {
        if (fila <= filaInicio) {
            char *token = strtok(linea, ",");
            int columna = 0;
            while (token != NULL && columna < numPalabras) {
                if (columna > 0) 
				{ 
                    conteoPalabras[columna - 1] += atoi(token);
                }
                token = strtok(NULL, ",");
                columna++;
            }
        }
        fila++;
    }


    fclose(archivo);


    FILE *archivoResultado = fopen("180063.txt", "w");
    if (!archivoResultado) {
        fprintf(stderr, "Error al abrir el archivo de resultados.\n");
        return 1;
    }


    for (int i = 0; i < numPalabras; i++) {
        fprintf(archivoResultado, "%s, %d\n", palabras[i], conteoPalabras[i]);
        free(palabras[i]);
    }


    fclose(archivoResultado);

    printf("Proceso completado. Resultados guardados en 180063.txt.\n");

    return 0;
}

