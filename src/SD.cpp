#include <Arduino.h>

#include "menu.hpp"

DynamicPage load_page(const char* menu, int page) {
    DynamicPage result;
    result.len = 16;

    for (int i = 0; i < 16; i++) {
        DynamicItem& item = result.items[i];

        int pos = 0;

        while (menu[pos] != '\0' && pos < 12) {
            item.text[pos] = menu[pos];
            pos++;
        }

        if (pos < 14) {
            item.text[pos++] = 'A' + page;
        }

        if (pos < 14) {
            item.text[pos++] = 'A' + i;
        }

        item.text[pos] = '\0';

        item.val.name = menu;
        item.val.page = page;
        item.val.index = i;
    }

    return result;
}

void load_val(const DynamicVal& val, char* out, int outSize) {
    int i = 0;

    while (val.name[i] != '\0' && i < outSize - 3) {
        out[i] = val.name[i];
        i++;
    }

    if (i < outSize - 2) out[i++] = 'A' + val.page;
    if (i < outSize - 1) out[i++] = 'A' + val.index;

    out[i] = '\0';
}

uint64_t load_val(const DynamicVal& val) {
    return 0;
}

void load_val(const DynamicVal& val, byte buffer[10]) {
    for (int i = 0; i < 10; i += 1) {
        buffer[i] = 0;
    }
}