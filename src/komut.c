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
    //Komuttan argüman dizisi oluşturulur
    char *args[MAX_KOMUT_UZUNLUGU / 2 + 1]; //Maksimum argüman miktarı
    int i = 0;
    //Komut argümanlara ayrılır
    args[i] = strtok(komut, " \t\n"); //Ilk index komutun kendisi olur (örn. ls -lha için ls olur)
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n"); //İşlemin kaldığı yerden devam etmesi için NULL verilir
    }

    if (args[0] == NULL) {
        return; //Boş komut
    }

    //Built-in quit komutu
    if (strcmp(args[0], "quit") == 0) exit(0);

    //Komutu çalıştırması için fork() ile bir çocuk proses oluşturulur
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork basarisiz");
        return;
    }

    if (pid == 0) {
        //pid = 0 çocuk proses olur, 
        if (execvp(args[0], args) < 0) { //Eğer execvp negatif değer döndürürse (false) komut çalıştırılamamış demektir
            perror("Komut calistirilamadi");
        }
        exit(1); //Başarısızlık durumunda çalışır (başarı durumunda execvp çocuk prosesin yerini alacağı için exit(1) çalışmaz)
    }
    else {
        //pid > 0 ise pid = çocuk prosesin proses id'si
        int status;
        waitpid(pid, &status, 0); //Çocuk prosesin bitmesi beklenilir
        tcflush(STDIN_FILENO, TCIFLUSH); //Proses ön planda çalışırken (shell beklemede iken) input yoksayılır
    }
}