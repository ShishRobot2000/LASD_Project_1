#include "zlasdtest/test.hpp"  // test ufficiali
#include "zmytest/test.hpp"    // miei test

#include <iostream>
#include <string>

int main() {
  std::cout << "=== LASD Libraries 2025 ===\n" << std::endl;

  bool continua = true;

  while (continua) {
    std::cout << "Scegli il test da eseguire:\n";
    std::cout << "1. Test ufficiali (zlasdtest)\n";
    std::cout << "2. Test personalizzati - Parte 1 [Vector, List, Set, SetVec, SetLst]\n";
    std::cout << "3. Test personalizzati - Parte 2 [Heap, HeapVec, PQ, PQHeap]\n";
    std::cout << "4. Test personalizzati - Tutti\n";
    std::cout << "0. Esci\n";
    std::cout << ">> ";
  
    int scelta;
    std::cin >> scelta;
  
    switch (scelta) {
      case 1:
        std::cout << "\n== Avvio test ufficiali ==\n" << std::endl;
        lasdtest();
        break;
  
      case 2:
        std::cout << "\n== Avvio test personalizzati - Parte 1 ==\n" << std::endl;
        lasd::RunAllTests1();
        break;
  
      case 3:
        std::cout << "\n== Avvio test personalizzati - Parte 2 ==\n" << std::endl;
        lasd::RunAllTests2();
        break;
  
      case 4:
        std::cout << "\n== Avvio tutti i test personalizzati ==\n" << std::endl;
        lasd::RunAllTests();
        break;
  
      case 0:
        std::cout << "Uscita dal programma." << std::endl;
        continua = false;
        break;
  
      default:
        std::cout << "Scelta non valida. Riprova." << std::endl;
        break;
    }
  
    if (scelta >= 1 && scelta <= 4) {
      std::cout << "\nVuoi eseguire un altro test? (s/n): ";
      std::string risposta;
      std::cin >> risposta;
      if (risposta != "s" && risposta != "S") {
        continua = false;
        std::cout << "Chiusura del programma." << std::endl;
      }
    }
  }
  

  return 0;
}
