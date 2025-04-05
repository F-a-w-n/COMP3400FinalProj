#!/usr/bin/bash
cd "$(dirname "$0")"
g++ Power.cpp CustomerTab.cpp FootprintTab.cpp SupplyTab.cpp ExpenseTab.cpp dbuser.cpp dbtypes.cpp database.cpp -o output.exe $(wx-config --cxxflags --libs) -lsqlite3 -lcurl -lssl -lcrypto
echo
read -p "Press Enter to close..."
