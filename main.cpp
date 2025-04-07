#include <ForthDictionary.h>
#include "ForthSystem.h"
#include "Quit.h"






int main() {

    ForthSystem::initialize();
    code_generator_initialize();

    Quit();
    return 0;


}
