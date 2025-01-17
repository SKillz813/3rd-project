#include "Functions.h"

int main() {
    Product catalog[MAX_PRODUCTS];
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Αρχικοποίηση του καταλόγου προϊόντων
    initialize_catalog(catalog);

    // Δημιουργία socket για τον server
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Αποτυχία δημιουργίας socket");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση διεύθυνσης server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Ακρόαση σε όλες τις διαθέσιμες διευθύνσεις
    server_addr.sin_port = htons(PORT);      // Μετατροπή θύρας σε μορφή δικτύου

    // Δέσμευση της διεύθυνσης στον server
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Αποτυχία bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Ο server αρχίζει να ακούει για συνδέσεις
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Αποτυχία listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Ο server είναι ενεργός και περιμένει συνδέσεις στη θύρα %d\n", PORT);

    while (1) {
        // Αποδοχή σύνδεσης από πελάτη
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1) {
            perror("Αποτυχία accept");
            continue; // Συνεχίζει να περιμένει άλλες συνδέσεις
        }

        printf("Συνδέθηκε πελάτης\n");
        
        // Διαχείριση του πελάτη σε ξεχωριστό thread
        pthread_t client_thread;
        int *client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = client_socket;

        if (pthread_create(&client_thread, NULL, (void *)handle_client, (void *)client_socket_ptr) != 0) {
            perror("Αποτυχία δημιουργίας thread");
            free(client_socket_ptr);
            close(client_socket);
        }
    }

    close(server_socket);
    return 0;
}
