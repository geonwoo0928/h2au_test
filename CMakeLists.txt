cmake_minimum_required(VERSION 3.18)
project(h2au_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. OpenCV 라이브러리 탐색 (시스템 경로 자동 탐색)
find_package(OpenCV REQUIRED)

# 2. LibTorch 경로 분기 처리 (로컬 경로 우선, 없으면 자동 다운로드)
if(DEFINED CMAKE_PREFIX_PATH OR DEFINED ENV{LIBTORCH_PATH})
    message(STATUS "지정된 LibTorch 경로를 사용합니다.")
    
    if(DEFINED ENV{LIBTORCH_PATH})
        list(APPEND CMAKE_PREFIX_PATH $ENV{LIBTORCH_PATH})
    endif()

    find_package(Torch REQUIRED)
else()
    message(STATUS "지정된 LibTorch 경로가 없어 인터넷에서 자동으로 다운로드합니다...")
    include(FetchContent)
    FetchContent_Declare(
      LibTorch
      URL https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-2.2.0%2Bcpu.zip
    )
    FetchContent_MakeAvailable(LibTorch)
    
    list(APPEND CMAKE_PREFIX_PATH ${libtorch_SOURCE_DIR})
    find_package(Torch REQUIRED)
endif()

# 3. 실행 파일 및 라이브러리 연결
add_executable(my_app main.cpp)

target_include_directories(my_app PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(my_app PRIVATE ${OpenCV_LIBS} "${TORCH_LIBRARIES}")
