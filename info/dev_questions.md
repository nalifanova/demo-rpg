# Dev questions during the learning process

**🤔1**: Is it okay to make a virtual method in one class
      but implement it in another (not inherited)?

- ~~*Assumption 01*: No, I haven't faced it before.~~
- ~~*Assumption 02*: I've no idea, need to dig in C++ classes.~~
- **Answer**: In C++, a method can only be overridden in a derived class. 


**🤔2**: How to write a constructor if you're using two inheritance?
```c++
class X: public A, public B, public C, public D
{
public:
      X(): A(arg1, arg2, arg3), B(arg4) {}
}
// Include C and D is unnecessary if there is no need to accept arguments.
```

