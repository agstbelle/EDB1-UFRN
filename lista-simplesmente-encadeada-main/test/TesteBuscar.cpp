#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaSimplesmenteEncadeada.h"
#include "ListaSimplesmenteEncadeadaTestHelper.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using Lista = ListaSimplesmenteEncadeada;
using Helper = ListaSimplesmenteEncadeadaTestHelper;

// Verifica o estado pelo helper, sem depender das operações pendentes.
static void verificarEstado(const Lista& lista, std::initializer_list<std::string> esperados)
{
    REQUIRE(Helper::consistente(lista));
    CHECK(lista.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(Helper::quantidade(lista) == static_cast<int>(esperados.size()));
    CHECK(Helper::mesmosElementos(lista, esperados));
    std::vector<std::string> reversos(esperados);
    std::reverse(reversos.begin(), reversos.end());
    CHECK(Helper::elementosReversos(lista) == reversos);
}

TEST_CASE("Buscar - lista vazia retorna menos um")
{
    Lista lista;
    CHECK(lista.buscar("X") == -1);
    CHECK(lista.buscar("") == -1);
    verificarEstado(lista, {});
}

TEST_CASE("Buscar - posições começam em um")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    const auto& leitura = lista;
    CHECK(leitura.buscar("A") == 1);
    CHECK(leitura.buscar("B") == 2);
    CHECK(leitura.buscar("C") == 3);
    CHECK(leitura.buscar("X") == -1);
    verificarEstado(lista, {"A", "B", "C"});
}

TEST_CASE("Buscar - retorna a primeira ocorrência de um valor repetido")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "B", "A"});
    CHECK(lista.buscar("A") == 1);
    CHECK(lista.buscar("B") == 2);
    verificarEstado(lista, {"A", "B", "B", "A"});
}

TEST_CASE("Buscar - string vazia é um elemento válido")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "", "B"});
    CHECK(lista.buscar("") == 2);
    verificarEstado(lista, {"A", "", "B"});
}

TEST_CASE("Acesso - primeiro, último e todas as posições")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    const auto& leitura = lista;
    CHECK(leitura.primeiroElemento() == "A");
    CHECK(leitura.ultimoElemento() == "C");
    CHECK(leitura.elementoNaPosicao(1) == "A");
    CHECK(leitura.elementoNaPosicao(2) == "B");
    CHECK(leitura.elementoNaPosicao(3) == "C");
    verificarEstado(lista, {"A", "B", "C"});
}

TEST_CASE("Acesso - único elemento e string vazia")
{
    Lista lista;
    Helper::preencherLista(lista, {""});
    CHECK(lista.primeiroElemento().empty());
    CHECK(lista.ultimoElemento().empty());
    CHECK(lista.elementoNaPosicao(1).empty());
    verificarEstado(lista, {""});
}

TEST_CASE("Acesso - lista vazia lança out_of_range")
{
    Lista lista;
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
    for (int posicao : {-1, 0, 1})
    {
        CAPTURE(posicao);
        CHECK_THROWS_AS(lista.elementoNaPosicao(posicao), std::out_of_range);
    }
    verificarEstado(lista, {});
}

TEST_CASE("Acesso - posições inválidas preservam o estado")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B"});
    for (int posicao : {-1, 0, 3, 4})
    {
        CAPTURE(posicao);
        CHECK_THROWS_AS(lista.elementoNaPosicao(posicao), std::out_of_range);
        verificarEstado(lista, {"A", "B"});
    }
}
