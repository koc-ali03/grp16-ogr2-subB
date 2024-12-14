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
#include "prompt.h"
#include "background_process.h"

void komut_calistir(char* komut, int MAX_KOMUT_UZUNLUGU) {
    char* args[MAX_KOMUT_UZUNLUGU / 2 + 1]; // Maksimum argüman miktarı
    int is_background_process = 0;
    int quit_flag = 0;
    int i = 0;

    // `<` ve `>` sembollerini kontrol eder
    char* input_redirect = strstr(komut, "<");
    char* output_redirect = strstr(komut, ">");

    // `&` sembolünü kontrol eder
    char* background_indicator = strstr(komut, "&");

    char* input_file = NULL;
    char* output_file = NULL;

    // komutta `&` sembolü olması durumunda arka plan prosesi olduğunu gösteren değişken ayarlanır
    if (background_indicator != NULL) {
        is_background_process = 1;
        *background_indicator = '\0';
    }

    // Giriş dosyasını ayır
    if (input_redirect != NULL) {
        *input_redirect = '\0';
        input_redirect++;
        input_file = strtok(input_redirect, " \t\n");
    }

    // Çıkış dosyasını ayır
    if (output_redirect != NULL) {
        *output_redirect = '\0';
        output_redirect++;
        output_file = strtok(output_redirect, " \t\n");
    }

    // Komut ve argümanları ayrıştır
    args[i] = strtok(komut, " \t\n");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    }

    if (args[0] == NULL) return; // Boş komut

    // Built-in quit komutu
    if (strcmp(args[0], "quit") == 0) {
        // Prompt gizlenir ve çalışmakta olan arka plan prosesleri bittikten sonra uygulama sonlanır
        prompt_gizle();
        wait_for_background_processes();
        exit(0);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork basarisiz.");
        return;
    }

    if (pid == 0) {
        // Çocuk proses

        // Giriş yönlendirme
        if (input_file != NULL) {
            FILE* file = fopen(input_file, "r");
            if (file == NULL) {
                printf("%s giris dosyasi bulunamadi.\n", input_file);
                exit(1);
            }
            dup2(fileno(file), STDIN_FILENO);
            fclose(file);
        }

        // Çıkış yönlendirme
        if (output_file != NULL) {
            FILE* file = fopen(output_file, "w");
            if (file == NULL) {
                printf("%s cikis dosyasi acilamadi.\n", output_file);
                exit(1);
            }
            dup2(fileno(file), STDOUT_FILENO);
            fclose(file);
        }

        // Komut çalıştırma
        if (execvp(args[0], args) < 0) {
            perror("Komut calistirilamadi.");
            exit(1);
        }
    }
    else {
        // Ebeveyn proses
        if (is_background_process) {
            add_background_process(pid);
        }
        else {
            int status;
            waitpid(pid, &status, 0);
            tcflush(STDIN_FILENO, TCIFLUSH);
        }
    }
}
