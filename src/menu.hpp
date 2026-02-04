#pragma once

struct Menu;

struct MenuItem {
    const char* text;
    bool (*action)();
    Menu* menu;
};

struct MenuPage {
    MenuItem* items;
    int len;
};

struct Menu {
    MenuPage* pages;
    int len;
    int mainPage;
};

struct DynamicVal {
    const char* name;
    int page;
    int index;
};

struct DynamicItem {
    char text[15];
    DynamicVal val;
};

struct DynamicPage {
    DynamicItem items[16];
    int len;
};

struct DynamicMenu {
    DynamicPage pages[3];
    int len;
};

bool back();