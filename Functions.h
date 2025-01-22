// Αποφυγή πολλαπλής συμπερίληψης του αρχείου functions.h 
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_PRODUCTS 20
#define MAX_CLIENTS 5
#define PORT 8080

typedef struct {
    char description[50]; // Περιγραφή προϊόντος
    float price;          // Τιμή προϊόντος
    int item_count;       // Διαθέσιμο απόθεμα
} Product;

typedef struct {
    int client_id;      // ID πελάτη
    int product_id;     // ID προϊόντος
    int quantity;       // Ποσότητα που ζητήθηκε
} Order;

// Δηλώσεις συναρτήσεων
void initialize_catalog(Product catalog[]);
void handle_client(int client_socket, Product catalog[]);
void process_order(Order order, Product catalog[], char *response);
void generate_report(Product catalog[]);

#endif // FUNCTIONS_H

