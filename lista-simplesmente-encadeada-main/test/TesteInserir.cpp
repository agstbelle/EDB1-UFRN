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

TEST_CASE("Inserir início - lista vazia e sucessivas inserções")
{
    Lista lista;
    CHECK(lista.inserirInicio("B"));
    verificarEstado(lista, {"B"});
    CHECK(lista.inserirInicio("A"));
    verificarEstado(lista, {"A", "B"});
}

TEST_CASE("Inserir início - preserva a sequência preparada")
{
    Lista lista;
    Helper::preencherLista(lista, {"B", "C"});
    CHECK(lista.inserirInicio("A"));
    verificarEstado(lista, {"A", "B", "C"});
}

TEST_CASE("Inserir fim - lista vazia e sucessivas inserções")
{
    Lista lista;
    CHECK(lista.inserirFim("A"));
    verificarEstado(lista, {"A"});
    CHECK(lista.inserirFim("B"));
    verificarEstado(lista, {"A", "B"});
}

TEST_CASE("Inserir fim - preserva a sequência preparada")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B"});
    CHECK(lista.inserirFim("C"));
    verificarEstado(lista, {"A", "B", "C"});
}

TEST_CASE("Inserir posição - primeira posição em lista vazia")
{
    Lista lista;
    CHECK(lista.inserirNaPosicao(1, "A"));
    verificarEstado(lista, {"A"});
}

TEST_CASE("Inserir posição - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    SUBCASE("Início")
    {
        CHECK(lista.inserirNaPosicao(1, "X"));
        verificarEstado(lista, {"X", "A", "B", "C"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.inserirNaPosicao(2, "X"));
        verificarEstado(lista, {"A", "X", "B", "C"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.inserirNaPosicao(4, "X"));
        verificarEstado(lista, {"A", "B", "C", "X"});
    }
}

TEST_CASE("Inserir posição - índices inválidos preservam a lista")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        for (int posicao : {-1, 0, 2})
        {
            CAPTURE(posicao);
            CHECK_THROWS_AS(lista.inserirNaPosicao(posicao, "X"), std::out_of_range);
            verificarEstado(lista, {});
        }
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"A", "B"});
        for (int posicao : {-1, 0, 4})
        {
            CAPTURE(posicao);
            CHECK_THROWS_AS(lista.inserirNaPosicao(posicao, "X"), std::out_of_range);
            verificarEstado(lista, {"A", "B"});
        }
    }
}

TEST_CASE("Inserir antes - referência ausente preserva o estado")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        CHECK_FALSE(lista.inserirAntes("X", "Y"));
        verificarEstado(lista, {});
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"A", "B"});
        CHECK_FALSE(lista.inserirAntes("X", "Y"));
        verificarEstado(lista, {"A", "B"});
    }
}

TEST_CASE("Inserir antes - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    SUBCASE("Primeiro")
    {
        CHECK(lista.inserirAntes("X", "A"));
        verificarEstado(lista, {"X", "A", "B", "C"});
    }
    SUBCASE("Intermediário")
    {
        CHECK(lista.inserirAntes("X", "B"));
        verificarEstado(lista, {"A", "X", "B", "C"});
    }
    SUBCASE("Último")
    {
        CHECK(lista.inserirAntes("X", "C"));
        verificarEstado(lista, {"A", "B", "X", "C"});
    }
}

TEST_CASE("Inserir antes - usa a primeira ocorrência da referência")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "B", "C"});
    CHECK(lista.inserirAntes("X", "B"));
    verificarEstado(lista, {"A", "X", "B", "B", "C"});
}

TEST_CASE("Inserir ordenado - lista vazia")
{
    Lista lista;
    CHECK(lista.inserirOrdenado("M"));
    verificarEstado(lista, {"M"});
}

TEST_CASE("Inserir ordenado - mantém ordem decrescente")
{
    Lista lista;
    Helper::preencherLista(lista, {"Z", "M", "A"});
    SUBCASE("Início")
    {
        CHECK(lista.inserirOrdenado("ZZ"));
        verificarEstado(lista, {"ZZ", "Z", "M", "A"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.inserirOrdenado("F"));
        verificarEstado(lista, {"Z", "M", "F", "A"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.inserirOrdenado(""));
        verificarEstado(lista, {"Z", "M", "A", ""});
    }
}

TEST_CASE("Inserir ordenado - rejeita duplicatas sem alterar a lista")
{
    Lista lista;
    Helper::preencherLista(lista, {"Z", "M", "A"});
    for (const std::string elemento : {"Z", "M", "A"})
    {
        CAPTURE(elemento);
        CHECK_FALSE(lista.inserirOrdenado(elemento));
        verificarEstado(lista, {"Z", "M", "A"});
    }
}

TEST_CASE("Inserções comuns - aceitam repetição e string vazia")
{
    Lista lista;
    Helper::preencherLista(lista, {"A"});
    SUBCASE("Início")
    {
        CHECK(lista.inserirInicio("A"));
        verificarEstado(lista, {"A", "A"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.inserirFim(""));
        verificarEstado(lista, {"A", ""});
    }
    SUBCASE("Posição")
    {
        CHECK(lista.inserirNaPosicao(2, "A"));
        verificarEstado(lista, {"A", "A"});
    }
    SUBCASE("Antes")
    {
        CHECK(lista.inserirAntes("A", "A"));
        verificarEstado(lista, {"A", "A"});
    }
}
