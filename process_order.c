#include "Functions.h"

// Συνάρτηση επεξεργασίας παραγγελίας
void process_order(Order order, Product catalog[], char *response) {
    if (order.product_id < 0 || order.product_id >= MAX_PRODUCTS) {
        // Έλεγχος για μη έγκυρο ID προϊόντος
        sprintf(response, "Μη έγκυρο ID προϊόντος\n");
        return;
    }

    Product *product = &catalog[order.product_id];
    if (product->item_count >= order.quantity) {
        // Επαρκές απόθεμα - ενημέρωση παραγγελίας
        product->item_count -= order.quantity;
        sprintf(response, "Επιτυχής παραγγελία: %s x%d, Σύνολο: %.2f€\n",
                product->description, order.quantity, product->price * order.quantity);
    } else {
        // Μη επαρκές απόθεμα
        sprintf(response, "Αποτυχία παραγγελίας: Δεν υπάρχει επαρκές απόθεμα για %s\n", product->description);
    }
}
