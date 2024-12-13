/*
* SAKARYA ÜNİVERSİTESİ 2024 GÜZ DÖNEMİ
* İŞLETİM SİSTEMLERİ PROJE ÖDEVİ
* 
* Grup no 16 - 2. Öğretim - B Şubesi
*
* Grup üyeleri:
* - Bedirhan CAN
* - Zeynep Dilara KURNAZ
* - Ali KOÇ
* - Necib TAVLAŞOĞLU
* - Burak Emre SARIKOÇ
*/

#include "komut.h"

void komut_calistir(char *komut, int MAX_KOMUT_UZUNLUGU) {
    char *args[MAX_KOMUT_UZUNLUGU / 2 + 1]; // Maksimum argüman miktarı
    int i = 0;

    // `<` sembolünü kontrol eder
    char *input_redirect = strstr(komut, "<");

    char *input_file = NULL;
    if (input_redirect != NULL) {
        // `<`'den sonraki kısmı giriş dosyası olarak alır
        *input_redirect = '\0'; // `<`'i ve sonrasını ayır
        input_redirect++;
        input_file = strtok(input_redirect, " \t\n");
    }

    // Komut ve argümanları ayrıştırır
    args[i] = strtok(komut, " \t\n");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    }

    if (args[0] == NULL) {
        return; // Boş komut
    }

    // Built-in quit komutu
    if (strcmp(args[0], "quit") == 0) exit(0);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork basarisiz");
        return;
    }

    if (pid == 0) {
        // Çocuk proses
        if (input_file != NULL) {
            FILE *file = fopen(input_file, "r");
            if (file == NULL) {
                // Eğer dosya açılamazsa, hata mesajı yazdırılır
                printf("%s giris dosyasi bulunamadi.\n", input_file);
                exit(1);
            }
            // Standart girişi dosyaya yönlendirir
            dup2(fileno(file), STDIN_FILENO);
            fclose(file);
        }

        if (execvp(args[0], args) < 0) {
            perror("Komut calistirilamadi");
        }
        exit(1);
    } else {
        // Ebeveyn proses
        int status;
        waitpid(pid, &status, 0);
        tcflush(STDIN_FILENO, TCIFLUSH);
    }
}
