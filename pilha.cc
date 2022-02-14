#include <iostream>

using namespace std;

class PilhaInt {
    public:
        void empilha(int n) {
            tab[tam++] = n;
        }
        
        int desempilha() {
            return tab[--tam];
        }
    
        void print(ostream& o) {
            o << "[ ";
            for (int i = 0; i < tam-1; i++) {
                o << tab[i] << ", ";
            }
            o << tab[tam-1] << " ]";
        }
        
        PilhaInt& operator << (int n) {
            empilha(n);
            return *this;
        }
        
        const PilhaInt& operator = (const PilhaInt& p) {
            tam = p.tam;
            for (int i = 0; i < tam; i++) {
                tab[i] = p.tab[i];
            }
            
            return *this;
        }
        
        PilhaInt() {}
    
    private:
        int tab[10];
        int tam = 0;
};