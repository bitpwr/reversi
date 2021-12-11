# Reversi 20

![State](https://github.com/bitpwr/reversi/actions/workflows/push.yml/badge.svg)

A simple reversi game, used to practice:

* C++20
* Conan
* Catch 2 unit testing

## Build

```
mkdir build
cd build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MODULE_PATH=. ..
```

## Later

* GitHub actions
* VS Code dev containers
* VS Code debugging
* GUI - SDL,???
