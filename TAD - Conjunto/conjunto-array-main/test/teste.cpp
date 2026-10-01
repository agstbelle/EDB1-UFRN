#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conjunto.h"

// Teste do estado inicial do Conjunto (Construtor)
TEST_CASE("Conjunto - Estado Inicial") {
    Conjunto conjunto(3);
    CHECK(conjunto.tamanho() == 0);
    CHECK(conjunto.contem(999) == false);
    CHECK(conjunto.remover(999) == false); // Remoção de elemento inexistente
}

// Testes da operação de Inserção
TEST_CASE("Conjunto - Inserção de Elementos") {
    Conjunto conjunto(3);

    CHECK(conjunto.inserir(10) == true);
    CHECK(conjunto.inserir(20) == true);
    CHECK(conjunto.tamanho() == 2);

    // Inserção de elemento duplicado
    CHECK(conjunto.inserir(10) == false);
    CHECK(conjunto.tamanho() == 2);

    // Inserção até a capacidade máxima
    CHECK(conjunto.inserir(30) == true);
    CHECK(conjunto.inserir(40) == false); // Capacidade atingida
    CHECK(conjunto.tamanho() == 3);
}

// Testes da operação de Remoção
TEST_CASE("Conjunto - Remoção de Elementos") {
    Conjunto conjunto(3);
    conjunto.inserir(5);
    conjunto.inserir(6);

    CHECK(conjunto.remover(5) == true);
    CHECK(conjunto.contem(5) == false);
    CHECK(conjunto.tamanho() == 1);

    // Remoção de elemento inexistente
    CHECK(conjunto.remover(99) == false);

    // Remover todos os elementos
    CHECK(conjunto.remover(6) == true);
    CHECK(conjunto.tamanho() == 0);
}

// Testes da operação de Contém
TEST_CASE("Conjunto - Verificação de Elementos com contem()") {
    Conjunto conjunto(3);

    conjunto.inserir(100);
    conjunto.inserir(200);

    CHECK(conjunto.contem(100) == true);
    CHECK(conjunto.contem(200) == true);
    CHECK(conjunto.contem(300) == false);

    conjunto.remover(100);
    CHECK(conjunto.contem(100) == false);
}
