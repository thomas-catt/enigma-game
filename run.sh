

# Compile and run:

rm ./bin/window;
clear;
cmake .;
make;

echo 'Running bin/window...';
./bin/window;

# Cleaning previous CMake cache:
chmod +x ./cmake-cleanup.sh;
./cmake-cleanup.sh;