# better-cpp-enum
Implementação de uma classe de Enum melhorada para C++11 baseada na encontrada neste [link](http://www.drdobbs.com/when-enum-just-isnt-enough-enumeration-c/184403955?pgno=1).

**Exemplo de uso**:
```c++
#include "better_enum.hpp"
#include <string>

class TestEnum : public Enum<std::string, TestEnum> {

private:
    explicit TestEnum(const std::string& value)
        : Enum<std::string, TestEnum>(value) {

    }

public:
    // Enum values
    static const TestEnum T;
    static const TestEnum T2;

};

// Declare set of instances
template<>
std::set<const Enum<std::string, TestEnum>*, Enum<std::string, TestEnum>::Enum_Ptr_Less>
    Enum<std::string, TestEnum>::instances{};

// Declare enum values
const TestEnum2 TestEnum::T("aaa");
const TestEnum2 TestEnum::T2("bbb");

int main(int argc, char const *argv[]) {

    std::cout << "Count: " << TestEnum::size() << std::endl;
	std::cout << "Values:" << std::endl;

    for( auto i = TestEnum::begin(); i != TestEnum::end(); ++i) {
        std::cout << "\t" << (*i)->getValue() << std::endl;
    }
    
    return 0;
}
```

**Saída**:

```
Count: 2
Values:
	aaa
	bbb
```
