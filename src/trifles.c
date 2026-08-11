#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include "../include/trifles.h"
#include "../include/game.h"


void remove_last_utf8_char(char *str) {
    if (str == NULL || *str == '\0') return;

    int len = strlen(str);
    int i = len - 1;

    // В UTF-8 продолжающие байты начинаются с 10xxxxxx (маска 0xC0 == 0x80)
    // Идем назад, пока не найдем первый байт символа
    while (i > 0 && (str[i] & 0xC0) == 0x80)
        i--;

    str[i] = '\0'; // Обрезаем строку
}
