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
