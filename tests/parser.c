#include <assert.h>
/*#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif*/
#include "../parser.h"

int main() {

    int len = 0;
    CalculateJsonSize(&len, "{{{}}}");
    assert(len == 1);
    
    assert(IsValidJson("{}") == 1);

    assert(IsValidJson("{\"test\": 21 }") == 1);
    
    assert(IsValidJson("{\"te\\\"st\": 21 }") == 1);
    
    assert(IsValidJson("{test: 21 }") == 0);
    
    assert(IsValidJson("[ 1, 2, 3, 4 ]") == 1);
    
    assert(IsValidJson("{\"obj\": { \"array\": [1, 2, 3, 4], \"list\": { \"one\": 1, \"two\": 2}}}") == 1);

    //TODO : improve parsing
    //assert(IsValidJson("{\"232\"2: 2}") == 0);

    return 0;
};