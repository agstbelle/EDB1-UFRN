#include <iostream>
using namespace std;

bool ehPrimo(int numero){
    bool primo = 
}

int main(){
    int testesPassados = 0;
    
    cout << "Teste 1: O valor esperado é 1 e o valor retornado foi " 
<< ehPrimo(5) << endl;
    if (ehPrimo(5) == true) testesPassados++;

    cout << "Teste 2: O valor esperado é 0 e o valor retornado foi " 
<< ehPrimo(10) << endl;
    if (ehPrimo(10) == false) testesPassados++;

    cout << "Teste 3: O valor esperado é 1 e o valor retornado foi " 
<< ehPrimo(13) << endl;
    if (ehPrimo(13) == true) testesPassados++;

    cout << "Teste 4: O valor esperado é 0 e o valor retornado foi " 
<< ehPrimo(1) << endl;
    if (ehPrimo(1) == false) testesPassados++;

    cout << "Teste 5: O valor esperado é 1 e o valor retornado foi " 
<< ehPrimo(17) << endl;
    if (ehPrimo(17) == true) testesPassados++;

    return 0;
}