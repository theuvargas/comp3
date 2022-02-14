#include <iostream>
#include <stdlib.h>

using namespace std;
  
class PilhaInt {  
    public:  
        void empilha(int n) {  
            if (tam == capacidadeAtual) {  
                redimensiona(capacidadeAtual*2);  
            }  
              
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
          
        void redimensiona(int n) {  
            while (tam > n) {  
                desempilha();  
            }  
              
            capacidadeAtual = n;  
            tab = (int*) realloc(tab, n * sizeof(int));  
        }  
          
        int capacidade() {  
            return capacidadeAtual;  
        }  
          
        PilhaInt(int capacidade = 10) {  
            capacidadeAtual = capacidade;  
            tab = (int*) malloc(capacidadeAtual * sizeof(int));  
        }  
         
        void copia(const PilhaInt& p) { 
            tam = p.tam;  
            capacidadeAtual = p.capacidadeAtual;  
            
            free(tab);
            tab = (int*) malloc(capacidadeAtual * sizeof(int));  
              
            for (int i = 0; i < tam; i++) {  
                tab[i] = p.tab[i];  
            } 
        } 
          
        const PilhaInt& operator = (const PilhaInt& p) {  
            if (&p == this) { 
                return *this; 
            } 
            copia(p); 
            return *this;  
        }  
         
        PilhaInt(const PilhaInt& p) {
            tab = (int*) malloc(p.capacidadeAtual * sizeof(int));
            copia(p);
        }  
          
        ~PilhaInt() {  
            free(tab); 
        }  
      
    private:  
        int tam = 0;  
        int* tab;  
        int capacidadeAtual;
};