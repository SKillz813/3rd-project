all: main
# Δημιουργεί το εκτελέσιμο πρόγραμμα "main".


# Το αρχείο Functions.h περιλαμβάνεται για τις δηλώσεις συναρτήσεων.

main: main.o initialize_catalog.o handle_client.o process_order.o generate_report.o
	# Συνδέει όλα τα αντικείμενα (.o) σε ένα εκτελέσιμο αρχείο "main".
	# Χρησιμοποιείται η βιβλιοθήκη pthread (-lpthread) για τα threads.
	gcc -o main main.o initialize_catalog.o handle_client.o process_order.o generate_report.o -lpthread

main.o: main.c Functions.h
	# Δημιουργεί το αντικείμενο (main.o) από το αρχείο main.c.
	# Ελέγχει ότι το αρχείο Functions.h είναι επίσης ενημερωμένο.
	gcc -c main.c

initialize_catalog.o: initialize_catalog.c Functions.h
	# Δημιουργεί το αντικείμενο (initialize_catalog.o) από το αρχείο initialize_catalog.c.
	gcc -c initialize_catalog.c

handle_client.o: handle_client.c Functions.h
	# Δημιουργεί το αντικείμενο (handle_client.o) από το αρχείο handle_client.c.
	gcc -c handle_client.c

process_order.o: process_order.c Functions.h
	# Δημιουργεί το αντικείμενο (process_order.o) από το αρχείο process_order.c.
	gcc -c process_order.c

generate_report.o: generate_report.c Functions.h
	# Δημιουργεί το αντικείμενο (generate_report.o) από το αρχείο generate_report.c.
	gcc -c generate_report.c

clean:
	# Διαγράφει όλα τα αρχεία αντικειμένων (.o) και το εκτελέσιμο πρόγραμμα "main".
	# Καθαρίζει το φάκελο από ενδιάμεσα αρχεία που δημιουργούνται κατά τη μεταγλώττιση.
	rm -f *.o main
