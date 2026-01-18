#pragma once
#include "menu.hpp"

namespace input {

    extern int index;
    extern char text[13];

    void create();

    // lowercase
    bool a(); bool b(); bool c(); bool d(); bool e(); bool f();
    bool g(); bool h(); bool i(); bool j(); bool k(); bool l();
    bool m(); bool n(); bool o(); bool p(); bool q(); bool r();
    bool s(); bool t(); bool u(); bool v(); bool w(); bool x();
    bool y(); bool z();

    // uppercase
    bool A(); bool B(); bool C(); bool D(); bool E(); bool Fchar();
    bool G(); bool H(); bool I(); bool J(); bool K(); bool L();
    bool M(); bool N(); bool O(); bool P(); bool Q(); bool R();
    bool S(); bool T(); bool U(); bool V(); bool W(); bool X();
    bool Y(); bool Z();

    // numbers
    bool in0(); bool in1(); bool in2(); bool in3(); bool in4();
    bool in5(); bool in6(); bool in7(); bool in8(); bool in9();

    // symbols
    bool in_tec(); bool in_car(); bool in_ptr(); bool in_dvo();
    bool in_onz(); bool in_znz();
    bool in_dash(); bool in_plus(); bool in_star();
    bool in_slash(); bool in_eq(); bool in_qm(); bool in_em();

    bool enter();

    extern MenuItem enterItem;
}
