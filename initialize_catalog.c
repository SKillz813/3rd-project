#include "Functions.h"

// Συνάρτηση για την αρχικοποίηση του καταλόγου προϊόντων
void initialize_catalog(Product catalog[]) {
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        snprintf(catalog[i].description, sizeof(catalog[i].description), "Προϊόν %d", i + 1);
        catalog[i].price = (float)(10 + i); // Τυχαία τιμή
        catalog[i].item_count = 2;          // Αρχικός αριθμός τεμαχίων
    }
}
