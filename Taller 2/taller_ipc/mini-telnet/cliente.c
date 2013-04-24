#include "header.h"

int main(int argc, char *argv[])
{
    int s, len;
    struct sockaddr_in remote;
    char str[MENSAJE_MAXIMO];

	/* Crear un socket de tipo INET con UDP (SOCK_STREAM). */
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("creando socket");
        exit(1);
    }

	/* Establecer la dirección a la cual conectarse. */
    remote.sin_family = AF_INET;
    remote.sin_port = htons(5555);
    char* ip = argv[1];
    if (inet_aton(ip, remote.sin_addr.s_addr) == 0) {
        perror("eh amigo tengo un error");
        exit(1);
    }
    len = sizeof(remote);

   	/* Conectarse. */
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("conectandose");
        exit(1);
    }

	/* Establecer la dirección a la cual conectarse para escuchar. */
    while(printf("> "), fgets(str, MENSAJE_MAXIMO, stdin), !feof(stdin)) {
        if (send(s, str, strlen(str)+1, 0) == -1) {
            perror("enviando");
            exit(1);
        }
    }

	/* Cerrar el socket. */
    close(s);

    return 0;
}