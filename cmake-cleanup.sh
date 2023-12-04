echo "Removing the following files/directories:";

if [ -d "./cmake-build-default/" ]; then
  rm -rf ./cmake-build-default;
  echo "Deleted: ./cmake-build-default";
else
  echo "Skipped: ./cmake-build-default [not found]";
fi

if [ -d "./CMakeFiles/" ]; then
  rm -rf ./CMakeFiles;
  echo "Deleted: ./CMakeFiles";
else
  echo "Skipped: ./CMakeFiles [not found]";
fi

if [ -f "cmake_install.cmake" ]; then
  rm ./cmake_install.cmake;
  echo "Deleted: ./cmake_install.cmake";
else
  echo "Skipped: ./cmake_install.cmake [not found]";
fi

if [ -f "CPackConfig.cmake" ]; then
  rm CPackConfig.cmake;
  echo "Deleted: CPackConfig.cmake";
else
  echo "Skipped: CPackConfig.cmake [not found]";
fi

if [ -f "CMakeCache.txt" ]; then
  rm CMakeCache.txt;
  echo "Deleted: CMakeCache.txt";
else
  echo "Skipped: CMakeCache.txt [not found]";
fi

if [ -f "CPackSourceConfig.cmake" ]; then
  rm CPackSourceConfig.cmake;
  echo "Deleted: CPackSourceConfig.cmake";
else
  echo "Skipped: CPackSourceConfig.cmake [not found]";
fi
