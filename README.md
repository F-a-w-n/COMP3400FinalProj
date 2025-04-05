# PowerPlex Energy Tracker

## Setup Instructions (for Windows)

1. Install MSYS2 from https://www.msys2.org/
2. Open "MSYS2 UCRT64" and run:
   pacman -Syu
   pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-wxWidgets mingw-w64-ucrt-x86_64-curl mingw-w64-ucrt-x86_64-sqlite3

3. In the same terminal, run:
   cd /c/Users/YourName/Path/To/PowerPlex
   ./build.sh
   export PATH="/ucrt64/bin:$PATH"
   ./output.exe

## Optional: VSCode

- Open this folder in VSCode
- Press Ctrl+Shift+B to build
- Press Ctrl+Shift+D 
- Option: Run Powerplex APP
- In the Project Folder, the output.exe file should open

## Optional: VSCode terminal
   cd /c/Users/YourName/Path/To/PowerPlex
   ./build.sh
   export PATH="/ucrt64/bin:$PATH"
   ./output.exe

## Notes

- The program uses test.db as the sample dataset
- Run initdb.exe to reset and re-seed the database
