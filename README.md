# Demo RPG (with proper attention to the learning process)

## About
This is a project based on [C++ RPG Code Along](https://www.youtube.com/playlist?list=PLalVdRk2RC6pqOVxRNj5Uui7FN4r-WorM)
video on YouTube. The project code can be found over here:
[codetechandtutorials/demo_rpg](https://github.com/codetechandtutorials/demo_rpg/releases/tag/ep3)

Personally, it's a learning C++ and GameDev process, thus changes from the `main line` will be obviously implemented. :D

## Dev Notes:
I consult authoritative pillars such as the
([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html)) 
and
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) 
to ensure that the code remains readable and consistent.

### Code style

* Each row of text in your code should be at most 80 characters long.
* Use a .cpp suffix for code files and .h for interface files 
  [NL.27](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#Rl-file-suffix)
* [Names and order of includes](https://google.github.io/styleguide/cppguide.html#Names_and_Order_of_Includes)
  Related header, C system headers, C++ standard library headers, other headers
* The names of all types — classes, structs, type aliases, enums, and type
  template parameters start with a capital letter and have a capital letter
  for each new word, with no underscores: MyExcitingClass, MyExcitingEnum.
* The names of variables (including function parameters) and data members are
  snake_case. E.g.: a_struct_data_member, a_class_data_member, a_variable
* Functions and methods should also use snake_case.
* Note! While I prefer using all uppercase for constants, both guides recommend 
  using it for macros. Therefore, I'll adhere to the 
  (Google rule)[https://google.github.io/styleguide/cppguide.html#Constant_Names]
  use `const int kDaysInAWeek = 7`. It's important for me to clearly indicate 
  that it is a constant (from global perspective).
