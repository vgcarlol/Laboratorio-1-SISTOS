#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>   

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <archivo_origen> <archivo_destino>\n", argv[0]);
        return 1;
    }

    int origen = open(argv[1], O_RDONLY);
    if (origen < 0) {
        perror("Error al abrir el archivo origen");
        return 1;
    }

    int destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destino < 0) {
        perror("Error al crear el archivo destino");
        close(origen);
        return 1;
    }

    char buffer[1024];
    ssize_t bytes_leidos;

    while ((bytes_leidos = read(origen, buffer, sizeof(buffer))) > 0) {
        if (write(destino, buffer, bytes_leidos) != bytes_leidos) {
            perror("Error al escribir en el archivo destino");
            close(origen);
            close(destino);
            return 1;
        }
    }

    if (bytes_leidos < 0) {
        perror("Error al leer el archivo origen");
    }

    close(origen);
    close(destino);

    printf("Copia completada.\n");
    return 0;
}
