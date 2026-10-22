//
//  Pilha.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Pilha__
#define __Pilha__

#include <iostream>
#include <stdexcept>
#include <optional>
#include <sstream>
#include <string>
template <typename T>
class Pilha
{
private:
    T* elementos;
    int capacidade;
    int quantidade;
    
public:
    Pilha(int cap)
    {
        this->quantidade = 0;
        this->capacidade = cap;
        elementos = new T[this->capacidade];
    }
    
    ~Pilha()
    {
        delete [] elementos;
    }
    
    int tamanho() const
    {
        return this->quantidade;
    }

    bool vazia() const
    {
        return this->quantidade == 0;
    }

    bool cheia() const
    {
        return this->quantidade == this->capacidade;
    }

    std::optional<T> topo() const
    {
        if (this->quantidade == 0)
        {
            return std::nullopt;
        }

        
    }

    void empilhar(T elemento)
    {
        if(cheia()){
            std::cout << "Erro: Pilha cheia!\n";
            return;
        }
        elementos[++topo] = elemento;
    }

    void desempilhar()
    {
        if(vazia()){
            std::cout << "Erro: Não tem como desempilhar uma pilha vazia!\n";
            return;
        }

        return elementos[topo--];
    }

    std::string imprimir() const
    {
        std::stringstream resultado;
        resultado << "{ ";
        for (int i = 0; i < tamanho(); ++i) 
        {
            resultado << elementos[i] << " ";
        }
        resultado << "}";
        return resultado.str();
    }
        
};
#endif
