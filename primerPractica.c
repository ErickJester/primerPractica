#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <regex.h>

#define MAX_ALFABETO 256
#define MAX_CADENA 100
#define MAX_PALABRAS 100

char l1[MAX_PALABRAS][MAX_CADENA];
char l2[MAX_PALABRAS][MAX_CADENA];
char ld[MAX_PALABRAS][MAX_CADENA];
char alfabeto[MAX_ALFABETO];
int alfabeto_len = 0;

int es_prefijo(char *w1, char *w2) {
    return strncmp(w1, w2, strlen(w1)) == 0;
}

int es_sufijo(char *w1, char *w2) {
    int longitud1 = strlen(w1);
    int longitud2 = strlen(w2);
    return (longitud1 <= longitud2) && (strncmp(w1, w2 + longitud2 - longitud1, longitud1) == 0);
}

int es_subsecuencia(char *w1, char *w2) {
    while (*w1 && *w2) {
        if (*w1 == *w2) w1++;
        w2++;
    }
    return !*w1;
}

int es_subcadena(char *w1, char *w2) {
    return strstr(w2, w1) != NULL;
}

void leer_cadena_valida(char *cadena, char *alfabeto, char *mensaje) {
    int valida;
    do {
        printf("%s", mensaje);
        scanf(" %s", cadena);
        valida = 1;
        for (int i = 0; cadena[i] && valida; i++) {
            if (!strchr(alfabeto, cadena[i])) {
                printf("Entrada invalida. La cadena contiene caracteres que no estan en el alfabeto.\n");
                valida = 0;
            }
        }
    } while (!valida);
}

void generar_lenguajes(char *alfabeto, int np, int l) {
    int alfabeto_len = strlen(alfabeto);
    printf("Lenguaje L1:\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < l; j++) {
            int rand_idx = rand() % alfabeto_len;
            l1[i][j] = alfabeto[rand_idx];
            l1[i][j+1] = '\0';
        }
        printf("%s\n", l1[i]);
    }
    printf("Lenguaje L2:\n");
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < l; j++) {
            int rand_idx = rand() % alfabeto_len;
            l2[i][j] = alfabeto[rand_idx];
            l2[i][j+1] = '\0';
        }
        printf("%s\n", l2[i]);
    }
}

void imprimir_cadenas_de_longitud(char *str, int idx, int n) {
    if (idx == n) {
        printf("%s\n", str);
        return;
    }
    for (int i = 0; i < alfabeto_len; i++) {
        str[idx] = alfabeto[i];
        imprimir_cadenas_de_longitud(str, idx + 1, n);
    }
}

void calcular_potencia(int n) {
    char str[MAX_CADENA] = {0};
    if (n > 0) {
        imprimir_cadenas_de_longitud(str, 0, n);
    } else if (n == 0) {
        printf("Cadena vacía\n");
    } else {
        printf("Conjunto vacío\n");
    }
}

void verificar_regex(char *cadena, char *patron) {
    regex_t regex;
    int resultado;
    char msgbuf[100];

    // Compila la expresión regular
    resultado = regcomp(&regex, patron, REG_EXTENDED);
    if (resultado) {
        fprintf(stderr, "No se pudo compilar la expresión regular\n");
        exit(1);
    }

    // Ejecuta la expresión regular
    resultado = regexec(&regex, cadena, 0, NULL, 0);
    if (!resultado) {
        printf("Palabra correcta\n");
    } else if (resultado == REG_NOMATCH) {
        printf("Palabra incorrecta\n");
    } else {
        regerror(resultado, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Error al evaluar regex: %s\n", msgbuf);
    }

    // Libera la memoria asignada a la expresión regular
    regfree(&regex);
}
int main() {
    char w1[MAX_CADENA], w2[MAX_CADENA], entrada[MAX_CADENA];
    char inicio, fin;
    int opcion, np, l, potencia;

    srand(time(NULL)); 

    printf("Introduce tu alfabeto (i para individual, r para rango): ");
    char metodo;
    scanf(" %c", &metodo);

    if (metodo == 'r') {
        printf("Introduce el caracter inicial y final del rango: ");
        scanf(" %c %c", &inicio, &fin);
        for (char c = inicio; c <= fin; c++) {
            alfabeto[alfabeto_len++] = c;
        }
    } else {
        printf("Introduce caracteres individualmente, termina con .: ");
        char entrada;
        while (scanf(" %c", &entrada) && entrada != '.') {
            if (!strchr(alfabeto, entrada)) {
                alfabeto[alfabeto_len++] = entrada;
            }
        }
    }

    leer_cadena_valida(w1, alfabeto, "Introduce la cadena w1: ");
    leer_cadena_valida(w2, alfabeto, "Introduce la cadena w2: ");

    do {
        printf("\nElige una opción:\n");
        printf("1. Prefijos y sufijos\n");
        printf("2. Generar los lenguajes L1 y L2\n");
        printf("3. Calcular la potencia del alfabeto\n");
        printf("4. Verificar cadenas con todas las vocales en orden. ");
        printf("0. Salir\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
            printf("\n\n");
                printf("w1 %s es un prefijo de w2\n", es_prefijo(w1, w2) ? "" : "no");
                printf("w1 %s es un sufijo de w2\n", es_sufijo(w1, w2) ? "" : "no");
                printf("w1 %s es una subcadena de w2\n", es_subcadena(w1, w2) ? "" : "no");
                printf("w1 %s es una subsecuencia de w2\n", es_subsecuencia(w1, w2) ? "" : "no");
                break;
            case 2:
            printf("\n\n");
                printf("Introduce el numero de palabras (np) y la longitud de las palabras (l): ");
                scanf("%d %d", &np, &l);
                generar_lenguajes(alfabeto, np, l);
                break;
            case 3:
            printf("\n\n");
                printf("Introduce la potencia del alfabeto (-5 a 5): ");
                scanf("%d", &potencia);
                if (potencia >= -5 && potencia <= 5) {
                    printf("Resultado de la potencia %d del alfabeto:\n", potencia);
                    calcular_potencia(potencia);
                } else {
                    printf("La potencia debe estar en el rango de -5 a 5.\n");
                }
                break;
            case 4:
            printf("\n\n");
                printf("Introduce una cadena para verificar (a-z con todas las vocales en orden): ");
                scanf("%s", entrada);
                verificar_regex(entrada, ".*a.*e.*i.*o.*u.*");
                break;
            case 0:
            printf("\n\n");
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, elige una opción válida.\n");
        }
    } while (opcion != 0);

    return 0;
}
