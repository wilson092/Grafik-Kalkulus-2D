#!/bin/bash
echo "🔧 Mengompilasi program..."
g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

if [ $? -eq 0 ]; then
    echo " Kompilasi berhasil"
    ./main
else
    echo " Kompilasi gagal"
fi
