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

#include <stdio.h>
#include <string.h>

#include "prompt.h"
#include "komut.h"

const int MAX_KOMUT_UZUNLUGU = 1024; // Komutun max uzunluğu

int main() {
    char komut[MAX_KOMUT_UZUNLUGU];

    while (1) {
        // Prompt (>) ekrana yazdırılır
        prompt_goster();

        // Kullanıcıdan input alınır, okuma hatası olursa veya end-of-file ulaşılırsa (Ctrl+D) çıkış yapılır
        if (fgets(komut, MAX_KOMUT_UZUNLUGU, stdin) == NULL) break;

        // Komut çalıştırılır
        komut_calistir(komut, MAX_KOMUT_UZUNLUGU);
    }

    return 0;
}
