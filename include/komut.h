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

#ifndef KOMUT_H
#define KOMUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //fork ve execvp için gerekli
#include <sys/wait.h> //waitpid için gerekli
#include <termios.h> //tcflush için gerekli

void komut_calistir(char*, int);

#endif