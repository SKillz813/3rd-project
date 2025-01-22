#include "Functions.h"

int main() {
    Product catalog[MAX_PRODUCTS];  // Πίνακας που αποθηκεύει τα προϊόντα του καταστήματος
    int server_socket, client_socket; // Υποδοχές για τον server και τον πελάτη
    struct sockaddr_in server_addr, client_addr; // Δομές για τις διευθύνσεις του server και του client
    socklen_t client_len = sizeof(client_addr);  // Μέγεθος της διεύθυνσης του client

    // Αρχικοποίηση του καταλόγου προϊόντων
    initialize_catalog(catalog); 

    // Δημιουργία socket για τον server
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Δεν ήταν δυνατό να δημιουργηθεί το socket για τον server.");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση της διεύθυνσης του server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Ακρόαση σε όλες τις διαθέσιμες διευθύνσεις
    server_addr.sin_port = htons(PORT);      // Ρύθμιση της θύρας του server

    // Δέσμευση της διεύθυνσης στον server
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Αποτυχία δέσμευσης διεύθυνσης στο socket.");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Ο server αρχίζει να ακούει για συνδέσεις
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Αποτυχία στην ακοή συνδέσεων.");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Ο server είναι έτοιμος και περιμένει συνδέσεις στη θύρα %d\n", PORT);

    while (1) {
        // Αναμονή και αποδοχή σύνδεσης από πελάτη
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Αποτυχία κατά την αποδοχή σύνδεσης από πελάτη.");
            continue; // Συνεχίζει να περιμένει νέες συνδέσεις
        }

        printf("Επιτυχής σύνδεση από πελάτη.\n");

        // Δημιουργία ξεχωριστού thread για την εξυπηρέτηση του πελάτη
        pthread_t client_thread;
        int *client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = client_socket;

        if (pthread_create(&client_thread, NULL, (void *)handle_client, (void *)client_socket_ptr) != 0) {
            perror("Αποτυχία δημιουργίας νέου thread για τον πελάτη.");
            free(client_socket_ptr);
            close(client_socket);
        }
    }

    // Κλείσιμο του socket του server όταν τερματίσει ο server
    close(server_socket);
    return 0;
}

