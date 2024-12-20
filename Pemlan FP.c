#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 30
#define MAX_FILMS 5
#define MAX_CITIES 3
#define MAX_THEATERS 4

// Struct untuk setiap film di dalam studio
typedef struct {
    int seat[MAX_SEATS]; // Seat khusus per film
} Film;

// Struct untuk studio, menyimpan array film
typedef struct {
    Film films[MAX_FILMS]; // Array film per studio
} Studio;

// Function declarations
void loadSeats(const char *filename, Studio studios[MAX_THEATERS]);
void saveSeats(const char *filename, Studio studios[MAX_THEATERS]);
void bookSeat(Film *film, int seatNumber);

int main() {
    char cities[MAX_CITIES][10] = {"Surabaya", "Jakarta", "Bandung"};
    char theaters[MAX_THEATERS][10] = {"CGV1", "CGV2", "XXI1", "XXI2"};
    char films[MAX_FILMS][20] = {"Sonic 3", "Moana 2", "Sekawan Limo", "Star Wars", "PacMan"};
    char filename[50], paymentMethods[3][10] = {"Cash", "QRIS", "Debit"};
    Studio studios[MAX_THEATERS];
    int cityChoice, theaterChoice, filmChoice, seatChoice, paymentChoice;

    printf("=== Cinema Ticket Booking ===\n");

    // Pilih Kota
    printf("Choose City:\n");
    for (int i = 0; i < MAX_CITIES; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    printf("Enter choice: ");
    scanf("%d", &cityChoice);
    if (cityChoice < 1 || cityChoice > MAX_CITIES) {
        printf("Invalid choice!\n");
        return 1;
    }

    // Pilih Bioskop
    printf("\nChoose Theater:\n");
    for (int i = 0; i < MAX_THEATERS; i++) {
        printf("%d. %s\n", i + 1, theaters[i]);
    }
    printf("Enter choice: ");
    scanf("%d", &theaterChoice);
    if (theaterChoice < 1 || theaterChoice > MAX_THEATERS) {
        printf("Invalid choice!\n");
        return 1;
    }

    // Generate nama file berdasarkan kota dan bioskop
    snprintf(filename, sizeof(filename), "%s_%s.csv", cities[cityChoice - 1], theaters[theaterChoice - 1]);

    // Load data seat
    loadSeats(filename, studios);

    // Pilih Film
    printf("\nChoose Film:\n");
    for (int i = 0; i < MAX_FILMS; i++) {
        printf("%d. %s\n", i + 1, films[i]);
    }
    printf("Enter choice: ");
    scanf("%d", &filmChoice);
    if (filmChoice < 1 || filmChoice > MAX_FILMS) {
        printf("Invalid choice!\n");
        return 1;
    }

    // Pilih Seat
    printf("\nChoose a seat (1-%d):\n", MAX_SEATS);
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("%d [%s]\n", i + 1, studios[theaterChoice - 1].films[filmChoice - 1].seat[i] ? "Booked" : "Available");
    }
    printf("Enter choice: ");
    scanf("%d", &seatChoice);
    if (seatChoice < 1 || seatChoice > MAX_SEATS || studios[theaterChoice - 1].films[filmChoice - 1].seat[seatChoice - 1]) {
        printf("Invalid or already booked seat!\n");
        return 1;
    }
    bookSeat(&studios[theaterChoice - 1].films[filmChoice - 1], seatChoice - 1);

    // Pilih Pembayaran
    printf("\nChoose Payment Method:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, paymentMethods[i]);
    }
    printf("Enter choice: ");
    scanf("%d", &paymentChoice);
    if (paymentChoice < 1 || paymentChoice > 3) {
        printf("Invalid choice!\n");
        return 1;
    }

    // Print Receipt
    printf("\n--- Ticket Receipt ---\n");
    printf("City: %s\n", cities[cityChoice - 1]);
    printf("Theater: %s\n", theaters[theaterChoice - 1]);
    printf("Film: %s\n", films[filmChoice - 1]);
    printf("Seat: %d\n", seatChoice);
    printf("Payment: %s\n", paymentMethods[paymentChoice - 1]);

    // Simpan data seat yang diperbarui
    saveSeats(filename, studios);
    printf("Booking saved successfully!\n");

    return 0;
}

// Function untuk load data seat
void loadSeats(const char *filename, Studio studios[MAX_THEATERS]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // File tidak ditemukan, inisialisasi semua seat ke 0
        printf("File not found. Initializing seat data...\n");
        for (int i = 0; i < MAX_THEATERS; i++) {
            for (int j = 0; j < MAX_FILMS; j++) {
                for (int k = 0; k < MAX_SEATS; k++) {
                    studios[i].films[j].seat[k] = 0;
                }
            }
        }
        return;
    }
    for (int i = 0; i < MAX_THEATERS; i++) {
        for (int j = 0; j < MAX_FILMS; j++) {
            for (int k = 0; k < MAX_SEATS; k++) {
                fscanf(file, "%d", &studios[i].films[j].seat[k]);
            }
        }
    }
    fclose(file);
}

// Function untuk save data seat
void saveSeats(const char *filename, Studio studios[MAX_THEATERS]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving file '%s'!\n", filename);
        exit(1);
    }
    for (int i = 0; i < MAX_THEATERS; i++) {
        for (int j = 0; j < MAX_FILMS; j++) {
            for (int k = 0; k < MAX_SEATS; k++) {
                fprintf(file, "%d ", studios[i].films[j].seat[k]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

// Function untuk booking seat
void bookSeat(Film *film, int seatNumber) {
    film->seat[seatNumber] = 1;
}