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

#include "prompt.h"
#include "background_process.h"

static BackgroundProcess* background_processes = NULL;

// Listeye yeni bir proses ekler
void add_background_process(pid_t pid) {
    BackgroundProcess* new_process = (BackgroundProcess*) malloc(sizeof(BackgroundProcess));
    new_process->pid = pid;
    new_process->next = background_processes;
    background_processes = new_process;
}

// Listeden prosesi siler ve çıkış durumu ile proses kimliğini kullanıcıya bildirir
void remove_background_process(pid_t pid, int exit_status, int show_prompt) {
    BackgroundProcess** current = &background_processes;
    while (*current != NULL) {
        if ((*current)->pid == pid) {
            BackgroundProcess* to_free = *current;
            *current = (*current)->next;
            free(to_free);
            printf("\r[%d] retval: %d\n", pid, WEXITSTATUS(exit_status));
            if (show_prompt) prompt_goster();
            fflush(stdout);
            return;
        }
        current = &(*current)->next;
    }
}

// Tamamlanmış arka plan işlemlerini temizlemek için sinyal işleyici
void handle_background_completion(int sig) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        remove_background_process(pid, status, 1);
    }
}

// Arka plan prosesleri için sinyal işleyici kurulumu
void setup_background_process_signal_handler() {
    signal(SIGCHLD, handle_background_completion);
}

// Tüm arka plan işlemlerinin bitmesi beklenir
void wait_for_background_processes() {
    while (background_processes != NULL) {
        int status;
        pid_t pid = waitpid(background_processes->pid, &status, 0);
        if (pid > 0) remove_background_process(pid, status, 0);
    }
}
