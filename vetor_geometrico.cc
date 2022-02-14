#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template <int n, typename T> 
class Vetor {
    public:
        Vetor() {}
        
        Vetor(const Vetor& v) {
            tam = v.tam;
            for (int i = 0; i < v.tam; i++) {
                espacos[i] = v.espacos[i];
            }
        }
        
        T operator * (const Vetor& v) {
            T soma = 0;
            for (int i = 0; i < tam; i++) {
                soma += espacos[i] * v.espacos[i];
            }
            
            return soma;
        }
        
        Vetor operator + (const Vetor& v) {
            Vetor<n, T> novoVetor{v};
            for (int i = 0; i < v.tam; i++) {
                novoVetor.espacos[i] += espacos[i];
            }
            
            return novoVetor;
        }
        
        Vetor operator - (const Vetor& v) {
            Vetor<n, T> novoVetor{v};
            for (int i = 0; i < v.tam; i++) {
                novoVetor.espacos[i] = espacos[i] - novoVetor.espacos[i];
            }
            
            return novoVetor;
        }
        
        Vetor operator / (auto num) {
            Vetor<n, T> novoVetor{*this};
            for (int i = 0; i < tam; i++) {
                novoVetor.espacos[i] /= num;
            }
            
            return novoVetor;
        }
        
        friend Vetor operator * (const Vetor& v, auto num) {
            Vetor<n, T> novoVetor{v};
            for (int i = 0; i < v.tam; i++) {
                novoVetor.espacos[i] *= num;
            }
            
            return novoVetor;
        }
        
        friend Vetor operator * (auto num, const Vetor& v) {
            return v * num;
        }
        
        friend ostream& operator << (ostream& out, Vetor<n, T> v) {
            out << "[ ";
            for (int i = 0; i < v.tam - 1; i++) {
                out << v.espacos[i] << ", ";
            }
            return out << v.espacos[v.tam - 1] << " ]";
        }
        
        void operator = (vector<T> v) {
            for (int i = 0; i < tam; i++) {
                espacos[i] = v[i];
            }
        }
        
        struct MeioDoProdutoVetorial {
            T espacos[n];
                
            MeioDoProdutoVetorial(const Vetor& v) {
                for (int i = 0; i < v.tam; i++) {
                    espacos[i] = v.espacos[i];
                }
            }
        };
        
        MeioDoProdutoVetorial operator * () {
            MeioDoProdutoVetorial meio{*this};
            
            return meio;
        }
        
        Vetor operator * (MeioDoProdutoVetorial v) {
            Vetor<n, T> novoVetor;
            
            /*if (n == 2) {
                return espacos[0] * v.espacos[1] - espacos[1] * v.espacos[0];
            }*/
            
            if (n == 3)  {
                novoVetor.espacos[0] = espacos[1] * v.espacos[2] - espacos[2] * v.espacos[1];
                novoVetor.espacos[1] = espacos[2] * v.espacos[0] - espacos[0] * v.espacos[2];
                novoVetor.espacos[2] = espacos[0] * v.espacos[1] - espacos[1] * v.espacos[0];
            }
            
            return novoVetor;
        }
        
    private:
        T espacos[n];
        int tam = n;
};