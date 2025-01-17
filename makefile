all: main

main: main.o initialize_catalog.o handle_client.o process_order.o generate_report.o
\tgcc -o main main.o initialize_catalog.o handle_client.o process_order.o generate_report.o -lpthread

main.o: main.c Functions.h
\tgcc -c main.c

initialize_catalog.o: initialize_catalog.c Functions.h
\tgcc -c initialize_catalog.c

handle_client.o: handle_client.c Functions.h
\tgcc -c handle_client.c

process_order.o: process_order.c Functions.h
\tgcc -c process_order.c

generate_report.o: generate_report.c Functions.h
\tgcc -c generate_report.c

clean:
\trm -f *.o main
