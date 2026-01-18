#include "inputMenu.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

namespace input {

    int index = 0;
    char text[13];

    static void add_char(char c) {
        if (index < 12) {
            text[index++] = c;
        }
    }

    void create() {
        for (int i = 0; i < 12; i++) text[i] = ' ';
        text[12] = '\0';
        index = 0;
    }

    #define GEN_CHAR_FUNC(name, ch) \
        bool name() { add_char(ch); return false; }

    // lowercase
    GEN_CHAR_FUNC(a,'a') GEN_CHAR_FUNC(b,'b') GEN_CHAR_FUNC(c,'c')
    GEN_CHAR_FUNC(d,'d') GEN_CHAR_FUNC(e,'e') GEN_CHAR_FUNC(f,'f')
    GEN_CHAR_FUNC(g,'g') GEN_CHAR_FUNC(h,'h') GEN_CHAR_FUNC(i,'i')
    GEN_CHAR_FUNC(j,'j') GEN_CHAR_FUNC(k,'k') GEN_CHAR_FUNC(l,'l')
    GEN_CHAR_FUNC(m,'m') GEN_CHAR_FUNC(n,'n') GEN_CHAR_FUNC(o,'o')
    GEN_CHAR_FUNC(p,'p') GEN_CHAR_FUNC(q,'q') GEN_CHAR_FUNC(r,'r')
    GEN_CHAR_FUNC(s,'s') GEN_CHAR_FUNC(t,'t') GEN_CHAR_FUNC(u,'u')
    GEN_CHAR_FUNC(v,'v') GEN_CHAR_FUNC(w,'w') GEN_CHAR_FUNC(x,'x')
    GEN_CHAR_FUNC(y,'y') GEN_CHAR_FUNC(z,'z')

    // uppercase
    GEN_CHAR_FUNC(A,'A') GEN_CHAR_FUNC(B,'B') GEN_CHAR_FUNC(C,'C')
    GEN_CHAR_FUNC(D,'D') GEN_CHAR_FUNC(E,'E') GEN_CHAR_FUNC(Fchar,'F')
    GEN_CHAR_FUNC(G,'G') GEN_CHAR_FUNC(H,'H') GEN_CHAR_FUNC(I,'I')
    GEN_CHAR_FUNC(J,'J') GEN_CHAR_FUNC(K,'K') GEN_CHAR_FUNC(L,'L')
    GEN_CHAR_FUNC(M,'M') GEN_CHAR_FUNC(N,'N') GEN_CHAR_FUNC(O,'O')
    GEN_CHAR_FUNC(P,'P') GEN_CHAR_FUNC(Q,'Q') GEN_CHAR_FUNC(R,'R')
    GEN_CHAR_FUNC(S,'S') GEN_CHAR_FUNC(T,'T') GEN_CHAR_FUNC(U,'U')
    GEN_CHAR_FUNC(V,'V') GEN_CHAR_FUNC(W,'W') GEN_CHAR_FUNC(X,'X')
    GEN_CHAR_FUNC(Y,'Y') GEN_CHAR_FUNC(Z,'Z')

    // numbers
    GEN_CHAR_FUNC(in0,'0') GEN_CHAR_FUNC(in1,'1') GEN_CHAR_FUNC(in2,'2')
    GEN_CHAR_FUNC(in3,'3') GEN_CHAR_FUNC(in4,'4') GEN_CHAR_FUNC(in5,'5')
    GEN_CHAR_FUNC(in6,'6') GEN_CHAR_FUNC(in7,'7') GEN_CHAR_FUNC(in8,'8')
    GEN_CHAR_FUNC(in9,'9')

    // symbols
    GEN_CHAR_FUNC(in_tec,'.') GEN_CHAR_FUNC(in_car,',')
    GEN_CHAR_FUNC(in_ptr,'_') GEN_CHAR_FUNC(in_dvo,':')
    GEN_CHAR_FUNC(in_onz,'(') GEN_CHAR_FUNC(in_znz,')')
    GEN_CHAR_FUNC(in_dash,'-') GEN_CHAR_FUNC(in_plus,'+')
    GEN_CHAR_FUNC(in_star,'*') GEN_CHAR_FUNC(in_slash,'/')
    GEN_CHAR_FUNC(in_eq,'=') GEN_CHAR_FUNC(in_qm,'?')
    GEN_CHAR_FUNC(in_em,'!')

    #undef GEN_CHAR_FUNC

    bool enter() {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(text);
        delay(500);
        return true;
    }

    MenuItem enterItem = { "Enter", enter, nullptr };
}
