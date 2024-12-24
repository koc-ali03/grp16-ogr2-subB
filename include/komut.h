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

#ifndef KOMUT_H
#define KOMUT_H

#include <unistd.h> // fork ve execvp için gerekli
#include <termios.h> // tcflush için gerekli

void komut_calistir(char*, int);

#endif
