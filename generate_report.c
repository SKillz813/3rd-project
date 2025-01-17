#include "Functions.h"

// Συνάρτηση για τη δημιουργία αναφοράς πωλήσεων
void generate_report(Product catalog[]) {
    printf("Αναφορά Πωλήσεων");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%s: %d τεμάχια διαθέσιμα\n", catalog[i].description, catalog[i].item_count);
    }
}
