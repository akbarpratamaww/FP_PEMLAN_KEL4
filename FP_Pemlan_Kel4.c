#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 30
#define MAX_FILMS 5
#define MAX_CITIES 3
#define MAX_THEATERS 4

// Struct untuk ketersediaan kursi
typedef struct {
    int seats[MAX_FILMS][MAX_SEATS]; // Kursi untuk setiap film
} Studio;

// Deklarasi fungsi
void loadSeats(const char *filename, Studio studios[MAX_CITIES][MAX_THEATERS]);
void saveSeats(const char *filename, Studio studios[MAX_CITIES][MAX_THEATERS]);
void bookSeat(Studio *studio, int filmChoice, int seatNumber);
void resetAllSeats(Studio studios[MAX_CITIES][MAX_THEATERS]);
void showMenu();
void searchFilm(char films[MAX_FILMS][20]);
void sortFilms(char films[MAX_FILMS][20]);

int main() {
    char cities[MAX_CITIES][10] = {"Surabaya", "Jakarta", "Bandung"};
    char theaters[MAX_THEATERS][10] = {"CGV1", "CGV2", "XXI1", "XXI2"};
    char films[MAX_FILMS][20] = {"Sonic 3", "Moana 2", "Sekawan Limo", "Star Wars", "PacMan"};
    char filename[] = "seats.csv", paymentMethods[3][10] = {"Cash", "QRIS", "Debit"};
    Studio studios[MAX_CITIES][MAX_THEATERS];
    int cityChoice, theaterChoice, filmChoice, seatChoice, paymentChoice, actionChoice;

    // Memuat data kursi dari file saat program dimulai
    loadSeats(filename, studios);

    // Loop utama untuk terus menampilkan menu setelah setiap aksi
    while (1) {
        // Tampilkan menu utama
        showMenu();

        printf("Masukkan pilihan Anda: ");
        scanf("%d", &actionChoice);

        if (actionChoice == 69420) {
            // Reset semua kursi dengan otentikasi
            char accessCode[10];
            printf("Masukkan kode akses untuk mereset kursi: ");
            scanf(" %9s", accessCode);

            if (strcmp(accessCode, "admin123") == 0) {
                resetAllSeats(studios);
                printf("Semua kursi telah direset.\n");
                saveSeats(filename, studios);  // Simpan status reset ke file
            } else {
                printf("Kode akses salah! Reset kursi dibatalkan.\n");
            }
        } else if (actionChoice == 1) {
            // Proses pemesanan tiket
            printf("=== Pemesanan Tiket Bioskop ===\n");

            // Pilih kota
            printf("Pilih Kota:\n");
            for (int i = 0; i < MAX_CITIES; i++) {
                printf("%d. %s\n", i + 1, cities[i]);
            }
            printf("Masukkan pilihan: ");
            scanf("%d", &cityChoice);
            if (cityChoice < 1 || cityChoice > MAX_CITIES) {
                printf("Pilihan tidak valid!\n");
                continue;
            }

            // Pilih bioskop
            printf("\nPilih Bioskop:\n");
            for (int i = 0; i < MAX_THEATERS; i++) {
                printf("%d. %s\n", i + 1, theaters[i]);
            }
            printf("Masukkan pilihan: ");
            scanf("%d", &theaterChoice);
            if (theaterChoice < 1 || theaterChoice > MAX_THEATERS) {
                printf("Pilihan tidak valid!\n");
                continue;
            }

            // Pilih film
            printf("\nPilih Film:\n");
            for (int i = 0; i < MAX_FILMS; i++) {
                printf("%d. %s\n", i + 1, films[i]);
            }
            printf("Masukkan pilihan: ");
            scanf("%d", &filmChoice);
            if (filmChoice < 1 || filmChoice > MAX_FILMS) {
                printf("Pilihan tidak valid!\n");
                continue;
            }

            // Pilih kursi
            printf("\nPilih kursi (1-%d):\n", MAX_SEATS);
            for (int i = 0; i < MAX_SEATS; i++) {
                printf("%d [%s]\n", i + 1, studios[cityChoice - 1][theaterChoice - 1].seats[filmChoice - 1][i] ? "Terpesan" : "Tersedia");
            }
            printf("Masukkan pilihan: ");
            scanf("%d", &seatChoice);
            if (seatChoice < 1 || seatChoice > MAX_SEATS || studios[cityChoice - 1][theaterChoice - 1].seats[filmChoice - 1][seatChoice - 1]) {
                printf("Kursi tidak valid atau sudah terpesan!\n");
                continue;
            }
            bookSeat(&studios[cityChoice - 1][theaterChoice - 1], filmChoice - 1, seatChoice - 1);

            // Pilih metode pembayaran
            printf("\nPilih Metode Pembayaran:\n");
            for (int i = 0; i < 3; i++) {
                printf("%d. %s\n", i + 1, paymentMethods[i]);
            }
            printf("Masukkan pilihan: ");
            scanf("%d", &paymentChoice);
            if (paymentChoice < 1 || paymentChoice > 3) {
                printf("Pilihan tidak valid!\n");
                continue;
            }

            // Cetak struk
            printf("\n--- Struk Tiket ---\n");
            printf("Kota: %s\n", cities[cityChoice - 1]);
            printf("Bioskop: %s\n", theaters[theaterChoice - 1]);
            printf("Film: %s\n", films[filmChoice - 1]);
            printf("Kursi: %d\n", seatChoice);
            printf("Pembayaran: %s\n", paymentMethods[paymentChoice - 1]);

            // Simpan data kursi yang diperbarui
            saveSeats(filename, studios);
            printf("Pemesanan berhasil disimpan!\n");
        } else if (actionChoice == 2) {
            // Pencarian film
            searchFilm(films);
        } else if (actionChoice == 3) {
            // Pengurutan film
            sortFilms(films);
            printf("Daftar film telah diurutkan:\n");
            for (int i = 0; i < MAX_FILMS; i++) {
                printf("%d. %s\n", i + 1, films[i]);
            }
        } else if (actionChoice == 0) {
            // Keluar dari program
            printf("Terima kasih telah menggunakan sistem kami. Sampai jumpa!\n");
            break;
        } else {
            printf("Pilihan tidak valid! Masukkan 69420 untuk reset, 1 untuk memesan tiket, 2 untuk mencari film, 3 untuk mengurutkan film, atau 0 untuk keluar.\n");
        }
    }

    return 0;
}

// Tampilkan opsi menu utama
void showMenu() {
    printf("\n=== Menu Utama ===\n");
    printf("69420. Reset semua kursi\n");
    printf("1. Pesan Tiket\n");
    printf("2. Cari Film\n");
    printf("3. Urutkan Film\n");
    printf("0. Keluar\n");
}

void searchFilm(char films[MAX_FILMS][20]) {
    char query[20];
    printf("Masukkan nama film yang ingin dicari: ");
    scanf(" %19[^\n]", query);  // Membaca input nama film

    printf("Hasil pencarian:\n");
    int found = 0;
    for (int i = 0; i < MAX_FILMS; i++) {
        if (strstr(films[i], query)) {  // Mencari substring dalam nama film
            printf("- %s\n", films[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("Film tidak ditemukan.\n");
    }

    // Tambahkan pesan untuk kembali ke menu
    printf("\nTekan Enter untuk kembali ke menu utama...");
    while (getchar() != '\n'); // Membersihkan karakter newline jika ada
    getchar(); // Tunggu pengguna menekan Enter
}


// Fungsi untuk mengurutkan daftar film secara alfabetis
void sortFilms(char films[MAX_FILMS][20]) {
    for (int i = 0; i < MAX_FILMS - 1; i++) {
        for (int j = i + 1; j < MAX_FILMS; j++) {
            if (strcmp(films[i], films[j]) > 0) {
                char temp[20];
                strcpy(temp, films[i]);
                strcpy(films[i], films[j]);
                strcpy(films[j], temp);
            }
        }
    }
}

// Fungsi untuk memuat data kursi dari file
void loadSeats(const char *filename, Studio studios[MAX_CITIES][MAX_THEATERS]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File '%s' tidak dapat dibuka!\n", filename);
        exit(1);
    }
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_THEATERS; j++) {
            for (int k = 0; k < MAX_FILMS; k++) {
                for (int l = 0; l < MAX_SEATS; l++) {
                    fscanf(file, "%d", &studios[i][j].seats[k][l]);
                }
            }
        }
    }
    fclose(file);
}

// Fungsi untuk menyimpan data kursi ke file
void saveSeats(const char *filename, Studio studios[MAX_CITIES][MAX_THEATERS]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("File '%s' tidak dapat disimpan!\n", filename);
        exit(1);
    }
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_THEATERS; j++) {
            for (int k = 0; k < MAX_FILMS; k++) {
                for (int l = 0; l < MAX_SEATS; l++) {
                    fprintf(file, "%d ", studios[i][j].seats[k][l]);
                }
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

// Fungsi untuk memesan kursi untuk film tertentu
void bookSeat(Studio *studio, int filmChoice, int seatNumber) {
    studio->seats[filmChoice][seatNumber] = 1;
}

// Fungsi untuk mereset semua kursi untuk semua film di semua bioskop
void resetAllSeats(Studio studios[MAX_CITIES][MAX_THEATERS]) {
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_THEATERS; j++) {
            for (int k = 0; k < MAX_FILMS; k++) {
                for (int l = 0; l < MAX_SEATS; l++) {
                    studios[i][j].seats[k][l] = 0;  // Reset semua kursi ke tersedia (0)
                }
            }
        }
    }
}
