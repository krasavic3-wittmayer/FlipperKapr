#include <iostream>

int index = 0;

extern struct Menu;

struct MenuItem {
    std::string text;
    bool (*action)();
    Menu* menu = nullptr;
};

struct Menu {
    MenuItem* items;
    int len;
};

bool back() {
    return true;
}

void ShowScreen(Menu menu) {
    std::string line1 = menu.items[index].text;
    std::string line2;

    if (index + 1 >= menu.len) {
        line2 = menu.items[0].text;
    }
    else {
        line2 = menu.items[index + 1].text;
    }

    std::cout << line1 << "  <-" << "\n";
    std::cout << line2 << "\n";
}

bool MemuFunction(Menu menu) {
    index = 0;
    int temp_index;
    ShowScreen(menu);
    char input;

    while (true) {
        std::cin >> input;

        if (input == 'u') {
            index += 1;

            if (index >= menu.len) {
                index = 0;
            }

        }
        else if (input == 'd') {
            index -= 1;

            if (index == -1) {
                index = menu.len - 1;
            }

        }
        else if (input == 'e') {
            if (menu.items[index].action == nullptr) {
                temp_index = index;
                MemuFunction(*menu.items[index].menu);
                index = temp_index;

            }
            else {
                if (menu.items[index].action()) {
                    break;
                }
            }
        }

        ShowScreen(menu);
    }

    return false;
}

bool sendIR() { return false; }
bool recIR() { return false; }

bool write125() { return false; }
bool read125() { return false; }
bool saved125() { return false; }

bool write1356() { return false; }
bool read1356() { return false; }
bool saved1356() { return false; }

bool sendUSB() { return false; }
bool newUSB() { return false; }
bool savedUSB() { return false; }


int main() {
    Menu mainMenu;
    Menu IRMenu;
    Menu RFID125Menu;
    Menu RFID1356Menu;
    Menu badUSBMenu;

    MenuItem IRItems[] = {
        {"Send", sendIR},
        {"Receive", recIR},
        {"Back", back},
    }; IRMenu = { IRItems, 3 };

    MenuItem RFID125items[] = {
        {"Write", write125},
        {"Read", read125},
        {"Saved", saved125},
        {"Back", back},
    }; RFID125Menu = { RFID125items, 4 };

    MenuItem RFID1356items[] = {
        {"Write", write1356},
        {"Read", read1356},
        {"Saved", saved1356},
        {"Back", back},
    }; RFID1356Menu = { RFID1356items, 4 };

    MenuItem badUSBitems[] = {
        {"Send payload", sendUSB},
        {"New payload", newUSB},
        {"Saved", savedUSB},
        {"Back", back},
    }; badUSBMenu = { badUSBitems, 4 };

    MenuItem mainMenuItems[] = {
        {"IR", nullptr, &IRMenu},
        {"RFID 125 kHz", nullptr, &RFID125Menu},
        {"RFID 13.56 MHz", nullptr, &RFID1356Menu},
        {"Bad USB", nullptr, &badUSBMenu},
    }; mainMenu = { mainMenuItems, 4 };

    MemuFunction(mainMenu);
}