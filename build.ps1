gcc *.cpp -o Game.exe -O1 -Wall -std=gnu++20 -Wno-missing-braces -I include/ -I /include/external/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lstdc++
./Game.exe