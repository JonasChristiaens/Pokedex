# Pokedex
For this project we were tasked to create a C++ console application that parses the given pokedex.json file and 
outputs to the console. The project was to be structured in such a way that switching between parsers was easily 
done, based on the CMake configuration. 

The project was required to support at least 2 different JSON parsers.
For this project I have chose to use ***Nlohmann*** and ***RapidJson***, because both of these parsers are big industry standards,
and their online documentation is very clear and explains a lot for those not yet knowledgeable about these 2 libraries. 

***Nlohmann*** [[1]](https://github.com/nlohmann/json) is simple and easy to use, and uses syntax that feels natural and familiar to users of Python, 
a language which I am familiar with.
***RapidJson*** [[2]](https://github.com/Tencent/rapidjson) was designed for high performance and efficiency and uses a more traditional c++ approach. It also 
provides faster parsing and serialization due to low-level optimizations


****
## How to Use
You are able to switch between the 2 installed parsers, by selecting a different CMake build [[3]](https://learn.microsoft.com/en-us/cpp/build/customize-cmake-settings?view=msvc-170).

In these 2 different builds that I have created, I add a variable in the "CMake variables and cache" section, 
which sets '*JSON_LIBRARY*' to the specific value, "nlohmann" or "rapidjson", that it needs to be for that parser. Since Nlohmann is set as the default 
option, this was only required to be done for the RapidJson build.

When running the program with one of these configurations selected, it will automatically use the specified value of 
'*JSON_LIBRARY*' for that configuration. In my **CMakeLists** file, based on this value, CMake will fetch [[4]](https://cmake.org/cmake/help/latest/module/FetchContent.html) 
the appropriate library.

It will then add the correct source files for the selected JSON Parser, and link the executable with the correct library.