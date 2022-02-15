#include <iostream>
#include <vector>

using namespace std;

class PilhaInt {
    public:  
        void empilha(int n) {
            if (tab.size() == capacidade()) {
                redimensiona(capacidade()*2);
            }
            
            tab.push_back(n);
        }
        
        int desempilha() {
            int n = tab.back();
            tab.pop_back();
            return n;
        }  
      
        void print(ostream& o) {  
            o << "[ ";  
            for (size_t i = 0; i < tab.size()-1; i++) {  
                o << tab[i] << ", ";  
            }
            o << tab.back() << " ]";  
        } 
          
        PilhaInt& operator << (int n) {  
            empilha(n);  
            return *this;  
        } 
          
        void redimensiona(size_t cap) {  
            while (tab.size() > cap) {
                desempilha();
            }  
            
            tab.shrink_to_fit();
            
            if (cap > capacidade()) {
                tab.reserve(cap);
            }
        }
        
        size_t capacidade() const {
            return tab.capacity();
        }
        
        PilhaInt(int capacidade = 10) {  
            tab.reserve(capacidade);
        }
        
        void copia(const PilhaInt& p) {
            tab = p.tab;
            redimensiona(p.capacidade());
        }
        
        const PilhaInt& operator = (const PilhaInt& p) {  
            if (&p == this) { 
                return *this; 
            }
            copia(p);
            return *this;  
        }  
         
        PilhaInt(const PilhaInt& p) {
            copia(p);
        }  
      
    private:
        vector<int> tab;
};