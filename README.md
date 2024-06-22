## This is my university project a tiny implementation of the AES 128bit encryption system.
# Guide to Using AES Encryption and Decryption Code

## 1. Project Structure

Ensure your project is structured as follows:

AESProject/
├── CMakeLists.txt
├── main.cpp
├── constants.h
├── key_expansion.h
├── key_expansion.cpp
├── aes_operations.h
├── aes_operations.cpp
└── utilities.h
└── utilities.cpp

## 2. CMakeLists.txt

Create a `CMakeLists.txt` file to manage the build process. This file specifies the project details and the source files to be compiled.

```cmake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AESProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(AESProject
    main.cpp
    key_expansion.cpp
    aes_operations.cpp
    utilities.cpp
)
```

## 3. Compilation and Execution

Step-by-Step Instructions:

1. Navigate to the Project Directory:

```bash
cd /path/to/AESProject
```

2. Generate Build Files:
   
```bash
cmake .
```

3. Compile the Project:

```bash
make
```

#Run the Executable:

```bash
./AESProject
```
