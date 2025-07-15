set -e 
cmake -B build
cmake --build build
./build/test_platform_dirs