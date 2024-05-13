# Dev notes during learning process

## IDE suggests to use

*constexpr* indicates a value that's constant and known during compilation
*const* indicates a value that's only constant; it's not compulsory to know 
        during compilation

```c++
const     double PI1 = 3.141592; - can be initialized at compile or run time.
constexpr double PI1 = 3.141592; - shall be initialized at compile time
```

*[[nodiscard]]* means no discard value (in other word, don't use it as void)
```c++
[[nodiscard]] hptype get_initial_hp() const
```

## To get the class name from the object

```c++
class MyClass
{
    const char* name;
    MyClass()
    {
        name = __func__;
    }
}
```
