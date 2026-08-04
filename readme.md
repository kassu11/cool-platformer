# Install Raylib and building

- I installed Raylib `.exe` from the [Raylib main page](https://www.raylib.com/) 
    - Here is a great [YouTube tutorial](https://youtu.be/R1iN3j7mAos) to check that basic Hello world works
- Then I added `C:\raylib\w64devkit\bin` to my path enviroment variable
- The `build.sh` file is a basic translation from the **NotePad++** NppExec script
    - You can build the exe like this: `build.sh core_basic_window.c`
- The script will also print your current `gcc build command`, if you want to use that instead
- `.clangd` file makes `LSP` work for **NeoVim**


Here is a full build command:

```bash
gcc -o main.exe main.c -s -static -O3 -std=c99 -Wall -Wshadow -Wunused-parameter -I/c/raylib/raylib/src -Iexternal -DPLATFORM_DESKTOP -L. -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore
```
