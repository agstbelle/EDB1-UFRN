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

TEST_CASE("Lista - Construtor estabelece uma lista vazia consistente")
{
    Lista lista;
    verificarEstado(lista, {});
    CHECK(lista.tamanho() == 0);
    CHECK(lista.vazia());
    CHECK(lista.imprimir() == "{}");
    CHECK_THROWS_AS(lista.primeiroElemento(), std::out_of_range);
    CHECK_THROWS_AS(lista.ultimoElemento(), std::out_of_range);
}

TEST_CASE("Lista - Tamanho, impressão e extremidades refletem os dados preparados")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    verificarEstado(lista, {"A", "B", "C"});
    CHECK(lista.tamanho() == 3);
    CHECK_FALSE(lista.vazia());
    CHECK(lista.primeiroElemento() == "A");
    CHECK(lista.ultimoElemento() == "C");
    CHECK(lista.imprimir() == "{A, B, C}");
}

TEST_CASE("Lista - Lista com um elemento e string vazia")
{
    Lista lista;
    Helper::preencherLista(lista, {""});
    verificarEstado(lista, {""});
    CHECK(lista.tamanho() == 1);
    CHECK_FALSE(lista.vazia());
    CHECK(lista.primeiroElemento().empty());
    CHECK(lista.ultimoElemento().empty());
}

TEST_CASE("Lista - Helper pode substituir os dados e voltar ao estado vazio")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "A", "B"});
    verificarEstado(lista, {"A", "A", "B"});
    Helper::preencherLista(lista, {"X"});
    verificarEstado(lista, {"X"});
    Helper::preencherLista(lista, {});
    verificarEstado(lista, {});
    CHECK(lista.tamanho() == 0);
    CHECK(lista.vazia());
}
