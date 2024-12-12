#
# SAKARYA ÜNİVERSİTESİ 2024 GÜZ DÖNEMİ
# İŞLETİM SİSTEMLERİ PROJE ÖDEVİ
# 
# Grup no 16 - 2. Öğretim - B Şubesi
#
# Grup üyeleri:
# - Bedirhan CAN
# - Zeynep Dilara KURNAZ
# - Ali KOÇ
# - Necib TAVLAŞOĞLU
# - Burak Emre SARIKOÇ
#

program: derle calistir

derle:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c
	gcc -I ./include/ -o ./lib/komut.o -c ./src/komut.c
	gcc -I ./include/ -Wall -Wextra -o ./bin/shell ./lib/prompt.o ./lib/komut.o ./src/shell.c

calistir:
	./bin/shell