#include "Conjunto.h"
#include <iostream>

Conjunto::Conjunto(const int capacidade)
{
}

Conjunto::~Conjunto()
{
}

bool Conjunto::contem(int elemento) const
{
    return elemento != 0;
}

bool Conjunto::inserir(int elemento)
{
    return elemento != 0;
}

bool Conjunto::remover(int elemento)
{
    return elemento != 0;
}

int Conjunto::tamanho() const
{
    return this->quantidade;
}

void Conjunto::imprimir() const
{
    std::cout << "{ ";
    for(int i = 0; i < quantidade; ++i)
    {
        std::cout << this->elementos[i] << " ";
    }
    std::cout << "}" << std::endl;
}
