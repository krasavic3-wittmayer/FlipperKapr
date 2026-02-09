#pragma once

#include <Arduino.h>


DynamicPage load_page(const char* menu, int page);
void load_val(const DynamicVal& val, char* out, int outSize);

uint64_t load_val(const DynamicVal& val);
void load_val(const DynamicVal& val, byte buffer[10]);