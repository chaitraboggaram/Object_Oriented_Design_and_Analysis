# Object Oriented Design and Analysis Syntaxes

## Classes

**Class and object declaration**

```
class className {
    public: 
    datatype1 variableName1;
    datatype2 variableName2;
    :
    :
}

void main() {
    className objectName1, objectName2, ....;
    objectName1.variableName1;
    objectName2.variableName2;
    :
    :
}
```

**Example**
```
#include <iostream>
#include <string>
using namespace std;

class fruits{
    public:
    string name;
};

int main(){
    fruits apple, orange, pear;
    apple.name = "Apple";
    cout << apple.name << "\n";

    orange.name = "Orange";
    cout << orange.name << "\n";

    pear.name = "Pear";
    cout << pear.name << "\n";
    return 0;
}
```

**Output**
```
Apple
Orange
Pear
```


## Pointers

**Pointer initilization**
```
datatype1 *pointerName;
datatype2 varibaleName;
pointerName = &variableName;
```

**Example**
```
int myvariable = 25;
int *pointervar;
pointervar = &myvariable;
int newvar = myvariable;

cout << myvariable << endl;
cout << pointervar << endl;
cout << newvar << endl << endl;
```

**Output**
```
25
0x16fb870d8
25
```

**Pointer Reference**
- Incrementing reference or variable will increment both

```
datatype1 variableName1;
datatype1 &variableName2 = variable1;
```

**Output**
```
int i = 25;
int &ir = i;
ir = ir + 1;

cout << ir << endl;
cout << i << endl;
```