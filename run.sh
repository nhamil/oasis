if [ ! -d Build ]; then 
    mkdir Build
fi 
cd Build
cmake -G "MinGW Makefiles" .. 
mingw32-make 
./OasisApp  
read -n 1 -s -r -p "Press any key to continue..."
