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
 * - Muhammed Necib TAVLAŞOĞLU
 * - Burak Emre SARIKOÇ
 */
#include "pipeline.h"
#include <unistd.h>
#include <fcntl.h>
void pipeline_calistir(char *komut, int max)
{
    char *komutlar[max / 2 + 1]; // Pipe ile ayrılmış komutlar için dizi
    int num_komutlar = 0;        // Komut sayısını takip eden sayaç


    // Komutları '|' işaretine göre ayır
    char *token = strtok(komut, "|");
    while (token != NULL) {
        komutlar[num_komutlar++] = token; // Ayrıştırılan komutları diziye ekle
        token = strtok(NULL, "|");       // Bir sonraki '|' işaretine kadar ayrıştırmaya devam et
    }
   
    // Çıkış yönlendirme `>`'yi işleyelim
    char *output_redirect = strstr(komutlar[num_komutlar - 1], ">");
    char *output_file = NULL;
    if (output_redirect != NULL) {
        *output_redirect = '\0';
        output_redirect++;
        output_file = strtok(output_redirect, " \t\n");
    }

    int pipes[num_komutlar - 1][2]; // Pipe dizisi: her pipe için bir okuma ve bir yazma ucuna sahip
     // Gerekli pipe'ların oluşturulması
    for (int i = 0; i < num_komutlar - 1; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("Pipe oluşturulamadı.");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_komutlar; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork başarısız.");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // İlk komut için giriş 
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }

            // Son komut için çıkış yönlendirme
            if (i == num_komutlar - 1 && output_file != NULL) {
                int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out < 0) {
                    perror("Çıkış dosyası açılamadı");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            } else if (i < num_komutlar - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Pipe kapatma
            for (int j = 0; j < num_komutlar - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Komutu çalıştır
            char *args[max / 2 + 1];
            int arg_index = 0;
            char *arg_token = strtok(komutlar[i], " \t\n");
            while (arg_token != NULL) {
                args[arg_index++] = arg_token;
                arg_token = strtok(NULL, " \t\n");
            }
            args[arg_index] = NULL;

            if (execvp(args[0], args) < 0) {
                perror("Komut çalıştırılamadı");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < num_komutlar - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_komutlar; i++) {
        wait(NULL);
    }
}