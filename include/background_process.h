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

#ifndef BACKGROUND_PROCESS_H
#define BACKGROUND_PROCESS_H

#include <sys/types.h>
#include <sys/wait.h> // waitpid için gerekli
#include <string.h>
#include <stdlib.h>
#include <signal.h>

// Arka plan işlemlerini takip etmek için bağlı liste yapısı
typedef struct BackgroundProcess {
    pid_t pid;
    struct BackgroundProcess* next;
} BackgroundProcess;

void add_background_process(pid_t pid);
void remove_background_process(pid_t pid, int exit_status, int show_prompt);
void handle_background_completion(int sig);
void setup_background_process_signal_handler();
void wait_for_background_processes();

#endif
