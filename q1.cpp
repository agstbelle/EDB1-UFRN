#include <iostream>
using namespace std;

bool ehPar(int numero){
    //if (numero % 2 == 0){
        //return true;
    //} 
    //else {
        //return false;
    //}
    bool par = numero % 2 == 0;
    if (par){
        return true;
    }
    else {
        return  false;
    }
}

int main(){
    int testesPassados = 0;

    cout << "Teste 1: O valor esperado é 1 e o valor retornado foi " 
<< ehPar(4) << endl;
    if (ehPar(4) == true) testesPassados++;

    cout << "Teste 2: O valor esperado é 0 e o valor retornado foi " 
<< ehPar(7) << endl;
    if (ehPar(7) == false) testesPassados++;

    cout << "Teste 3: O valor esperado é 1 e o valor retornado foi " 
<< ehPar(0) << endl;
    if (ehPar(0) == true) testesPassados++;

    cout << "Teste 4: O valor esperado é 0 e o valor retornado foi " 
<< ehPar(-5) << endl;
    if (ehPar(-5) == false) testesPassados++;

    cout << "Teste 5: O valor esperado é 1 e o valor retornado foi " 
<< ehPar(-8) << endl;
    if (ehPar(-8) == true) testesPassados++;

    cout << "Sua implementação passou em " << testesPassados << " de 5 testes."
<< endl;

    return 0;
}

