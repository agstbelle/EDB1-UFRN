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

TEST_CASE("Remover - lista vazia lança out_of_range")
{
    Lista lista;
    SUBCASE("Início") { CHECK_THROWS_AS(lista.removerInicio(), std::out_of_range); }
    SUBCASE("Fim") { CHECK_THROWS_AS(lista.removerFim(), std::out_of_range); }
    SUBCASE("Posição") { CHECK_THROWS_AS(lista.removerNaPosicao(1), std::out_of_range); }
    verificarEstado(lista, {});
}

TEST_CASE("Remover - único elemento atualiza as extremidades")
{
    Lista lista;
    Helper::preencherLista(lista, {"A"});
    SUBCASE("Início") { CHECK(lista.removerInicio() == "A"); }
    SUBCASE("Fim") { CHECK(lista.removerFim() == "A"); }
    SUBCASE("Posição") { CHECK(lista.removerNaPosicao(1) == "A"); }
    verificarEstado(lista, {});
}

TEST_CASE("Remover início - preserva a sequência restante")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    CHECK(lista.removerInicio() == "A");
    verificarEstado(lista, {"B", "C"});
}

TEST_CASE("Remover fim - preserva a sequência restante")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    CHECK(lista.removerFim() == "C");
    verificarEstado(lista, {"A", "B"});
}

TEST_CASE("Remover posição - início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    SUBCASE("Início")
    {
        CHECK(lista.removerNaPosicao(1) == "A");
        verificarEstado(lista, {"B", "C"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.removerNaPosicao(2) == "B");
        verificarEstado(lista, {"A", "C"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerNaPosicao(3) == "C");
        verificarEstado(lista, {"A", "B"});
    }
}

TEST_CASE("Remover posição - índices inválidos preservam o estado")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B"});
    for (int posicao : {-1, 0, 3, 4})
    {
        CAPTURE(posicao);
        CHECK_THROWS_AS(lista.removerNaPosicao(posicao), std::out_of_range);
        verificarEstado(lista, {"A", "B"});
    }
}

TEST_CASE("Remover - sucessivas remoções até esvaziar")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "B", "C"});
    SUBCASE("Somente início")
    {
        CHECK(lista.removerInicio() == "A"); verificarEstado(lista, {"B", "C"});
        CHECK(lista.removerInicio() == "B"); verificarEstado(lista, {"C"});
        CHECK(lista.removerInicio() == "C"); verificarEstado(lista, {});
    }
    SUBCASE("Somente fim")
    {
        CHECK(lista.removerFim() == "C"); verificarEstado(lista, {"A", "B"});
        CHECK(lista.removerFim() == "B"); verificarEstado(lista, {"A"});
        CHECK(lista.removerFim() == "A"); verificarEstado(lista, {});
    }
    SUBCASE("Somente posição")
    {
        CHECK(lista.removerNaPosicao(2) == "B"); verificarEstado(lista, {"A", "C"});
        CHECK(lista.removerNaPosicao(2) == "C"); verificarEstado(lista, {"A"});
        CHECK(lista.removerNaPosicao(1) == "A"); verificarEstado(lista, {});
    }
}

TEST_CASE("Remover todos - vazia e elemento ausente retornam zero")
{
    Lista lista;
    SUBCASE("Vazia")
    {
        CHECK(lista.removerTodos("X") == 0);
        verificarEstado(lista, {});
    }
    SUBCASE("Com elementos")
    {
        Helper::preencherLista(lista, {"A", "B", "A"});
        CHECK(lista.removerTodos("X") == 0);
        verificarEstado(lista, {"A", "B", "A"});
    }
}

TEST_CASE("Remover todos - ocorrências consecutivas no início, meio e fim")
{
    Lista lista;
    Helper::preencherLista(lista, {"A", "A", "B", "B", "C", "C"});
    SUBCASE("Início")
    {
        CHECK(lista.removerTodos("A") == 2);
        verificarEstado(lista, {"B", "B", "C", "C"});
    }
    SUBCASE("Meio")
    {
        CHECK(lista.removerTodos("B") == 2);
        verificarEstado(lista, {"A", "A", "C", "C"});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerTodos("C") == 2);
        verificarEstado(lista, {"A", "A", "B", "B"});
    }
}

TEST_CASE("Remover todos - ocorrências separadas em todas as posições")
{
    Lista lista;
    Helper::preencherLista(lista, {"X", "A", "X", "B", "X"});
    CHECK(lista.removerTodos("X") == 3);
    verificarEstado(lista, {"A", "B"});
}

TEST_CASE("Remover todos - todas as ocorrências e único elemento")
{
    Lista lista;
    SUBCASE("Único")
    {
        Helper::preencherLista(lista, {"A"});
        CHECK(lista.removerTodos("A") == 1);
    }
    SUBCASE("Vários")
    {
        Helper::preencherLista(lista, {"A", "A", "A"});
        CHECK(lista.removerTodos("A") == 3);
    }
    verificarEstado(lista, {});
}

TEST_CASE("Remover - string vazia é um elemento válido")
{
    Lista lista;
    Helper::preencherLista(lista, {"", "A", ""});
    SUBCASE("Início")
    {
        CHECK(lista.removerInicio().empty());
        verificarEstado(lista, {"A", ""});
    }
    SUBCASE("Fim")
    {
        CHECK(lista.removerFim().empty());
        verificarEstado(lista, {"", "A"});
    }
    SUBCASE("Posição")
    {
        CHECK(lista.removerNaPosicao(1).empty());
        verificarEstado(lista, {"A", ""});
    }
    SUBCASE("Todos")
    {
        CHECK(lista.removerTodos("") == 2);
        verificarEstado(lista, {"A"});
    }
}
