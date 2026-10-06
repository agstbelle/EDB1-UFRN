#include "ListaSimplesmenteEncadeada.h"
#include <sstream>
#include <stdexcept>

namespace
{
// Floyd: O(n) em tempo e O(1) em memória, sem usar o contador da lista.
template <typename Proximo>
bool temCiclo(const No<std::string>* inicio, Proximo proximo)
{
    auto lento = inicio;
    auto rapido = inicio;
    while (rapido != nullptr && proximo(rapido) != nullptr)
    {
        lento = proximo(lento);
        rapido = proximo(proximo(rapido));
        if (lento == rapido)
        {
            return true;
        }
    }
    return false;
}
}

ListaSimplesmenteEncadeada::ListaSimplesmenteEncadeada() : primeiro(nullptr), ultimo(nullptr), quantidade(0) {}

ListaSimplesmenteEncadeada::~ListaSimplesmenteEncadeada()
{
    auto atual = primeiro;
    while (atual != nullptr)
    {
        auto seguinte = atual->proximo;
        delete atual;
        atual = seguinte;
    }
}

bool ListaSimplesmenteEncadeada::inserirInicio(const std::string& elemento)
{
    throw std::runtime_error("Método ainda não implementado.");
}

bool ListaSimplesmenteEncadeada::inserirFim(const std::string& elemento)
{
    throw std::runtime_error("Método ainda não implementado.");
}

bool ListaSimplesmenteEncadeada::inserirNaPosicao(int posicao, const std::string& elemento)
{
    throw std::runtime_error("Método ainda não implementado.");
}

bool ListaSimplesmenteEncadeada::inserirAntes(const std::string& elemento, const std::string& referencia)
{
    throw std::runtime_error("Método ainda não implementado.");
}

bool ListaSimplesmenteEncadeada::inserirOrdenado(const std::string& elemento)
{
    throw std::runtime_error("Método ainda não implementado.");
}

std::string ListaSimplesmenteEncadeada::removerInicio()
{
    throw std::runtime_error("Método ainda não implementado.");
}

std::string ListaSimplesmenteEncadeada::removerFim()
{
    throw std::runtime_error("Método ainda não implementado.");
}

std::string ListaSimplesmenteEncadeada::removerNaPosicao(int posicao)
{
    throw std::runtime_error("Método ainda não implementado.");
}

int ListaSimplesmenteEncadeada::removerTodos(const std::string& elemento)
{
    throw std::runtime_error("Método ainda não implementado.");
}

int ListaSimplesmenteEncadeada::buscar(const std::string& elemento) const
{
    throw std::runtime_error("Método ainda não implementado.");
}

std::string ListaSimplesmenteEncadeada::elementoNaPosicao(int posicao) const
{
    throw std::runtime_error("Método ainda não implementado.");
}

std::string ListaSimplesmenteEncadeada::primeiroElemento() const
{
    if (quantidade == 0)
    {
        throw std::out_of_range("Lista vazia.");
    }
    return primeiro->valor;
}

std::string ListaSimplesmenteEncadeada::ultimoElemento() const
{
    if (quantidade == 0)
    {
        throw std::out_of_range("Lista vazia.");
    }
    return ultimo->valor;
}

int ListaSimplesmenteEncadeada::tamanho() const
{
    return quantidade;
}

bool ListaSimplesmenteEncadeada::vazia() const
{
    return quantidade == 0;
}

std::string ListaSimplesmenteEncadeada::imprimir() const
{
    std::ostringstream resultado;
    resultado << "{";
    for (auto atual = primeiro; atual != nullptr; atual = atual->proximo)
    {
        if (atual != primeiro) resultado << ", ";
        resultado << atual->valor;
    }
    resultado << "}";
    return resultado.str();
}

ConsistenciaStatus ListaSimplesmenteEncadeada::checarConsistencia() const
{
    if (temCiclo(primeiro, [](auto no) { return no->proximo; }))
        return ConsistenciaStatus::CICLO_DETECTADO;
    if (quantidade < 0)
        return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    if (primeiro == nullptr)
    {
        if (ultimo != nullptr) return ConsistenciaStatus::EXTREMIDADE_INCORRETA;
        return quantidade == 0 ? ConsistenciaStatus::OK : ConsistenciaStatus::QUANTIDADE_INCORRETA;
    }
    if (ultimo == nullptr) return ConsistenciaStatus::EXTREMIDADE_INCORRETA;

    std::size_t contagem = 0;
    const No<std::string>* ultimoVisitado = nullptr;
    for (auto atual = primeiro; atual != nullptr; atual = atual->proximo)
    {
        ultimoVisitado = atual;
        ++contagem;
    }
    if (ultimoVisitado != ultimo) return ConsistenciaStatus::EXTREMIDADE_INCORRETA;
    if (contagem != static_cast<std::size_t>(quantidade)) return ConsistenciaStatus::QUANTIDADE_INCORRETA;
    return ConsistenciaStatus::OK;
}
