# This project is currently NOT under active development

# Concept Point-of-Sales Program

This program is consept point-of-sales application that is built with the wxWidgets Library.
wxWidgets Library **NOT** included. You can find the download for wxWidgets at https://www.wxwidgets.org/downloads/ and compiling it at https://wiki.wxwidgets.org/Compiling_and_getting_started

# Requirements

* C++ mysql headers
* wxWidgets library

# Building

Whithin the src/ directory run make

    make

or

    make -j[# of threads to use - make uses 1 thread by default]

A sample MysqlConnection.txt will be within the src/ directory and can be modified to meet your needs in order to conect to a mysql database
