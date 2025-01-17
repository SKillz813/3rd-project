#include "Functions.h"

// Συνάρτηση διαχείρισης πελάτη
void handle_client(int client_socket, Product catalog[]) {
    char buffer[256];
    Order order;
    char response[256];

    // Επικοινωνία με τον πελάτη μέχρι να κλείσει η σύνδεση
    while (read(client_socket, buffer, sizeof(buffer)) > 0) {
        // Ανάλυση παραγγελίας
        sscanf(buffer, "%d %d %d", &order.client_id, &order.product_id, &order.quantity);
        
        // Επεξεργασία παραγγελίας
        process_order(order, catalog, response);
        
        // Αποστολή απάντησης στον πελάτη
        write(client_socket, response, strlen(response) + 1);
    }

    close(client_socket);
    printf("Ο πελάτης αποσυνδέθηκε\n");
    pthread_exit(NULL); // Τερματισμός thread
}
