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

#include "prompt.h"

void prompt_goster() {
    printf("> ");
    fflush(stdout);
}

void prompt_gizle() {
    fclose(stdin);
}
