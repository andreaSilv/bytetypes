# bytetypes
Mapping of few native trypes to byte vector. This little library is born to handle bytes
intended to be send on sockets, i'm tring to make diameter library to encode and decode
messages.

### Handled types
- **Int24** - an int mapped on three bytes (cut the fourth)
- **Int32** - int
- **Int64** - long long int
- **Float32** - float
- **Float64** - double
- **Octetstring** - std::string

### Main example
Main used by me to make tries

```c++
/* main.cpp */
#include <iostream>
#include "customtype.h"

int main(int argc, char const *argv[])
{
    Int32 val(255, false);

    for(size_t i=0 ; i<val.size() ; i++)
        std::cout << (int) val.getBytes().at(i) << ' ';

    std::cout << '\n' << "value: " << val.get() << '\n';
    std::cout << "Hex DUMP: " << val.getHexString() << '\n';
    return 0;
}
```
Build library
```bash
make install
```
Build *main.cpp*
```bash
g++ -o executable main.cpp customtype.a
```

**Pull requests are welcome!!**
