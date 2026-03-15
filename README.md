Address Book Project (ABP)
Overview

The Address Book Project (ABP) is a console-based contact management system implemented in C. It allows users to store, manage, and retrieve contact details such as name, phone number, and email address.

The program uses structures, file handling, and modular programming to organize and maintain contact information. All contact data is stored in a CSV file (contact.csv), ensuring persistence even after the program terminates.

Features

Add a new contact

View all contacts

Search contact by name

Edit existing contact details

Delete a contact

Store contacts in contact.csv for persistent storage

Technologies Used

C Programming Language

Structures

File Handling (fopen, fprintf, fscanf)

Modular Programming

Makefile for build automation

Project Structure
AddressBook/
│
├── README.md
├── Makefile
│
├── main.c
├── contact.c
├── file.c
│
├── contact.h
├── file.h
│
└── contact.csv
File Description
File	Description
main.c	Contains the main function and menu-driven interface
contact.c	Functions for contact operations (add, search, edit, delete)
file.c	Handles reading and writing contacts to the CSV file
contact.h	Structure definition and function declarations
file.h	File operation function declarations
contact.csv	Stores contact records
Makefile	Automates compilation of the project
Compilation

Use the Makefile to compile the project:

make

This will generate the executable:

abp
Running the Program
./abp
Cleaning Build Files

To remove object files and executable:

make clean
Learning Outcomes

This project helps in understanding:

Implementation of structures in C

Managing persistent data using file handling

Writing modular programs

Building menu-driven console applications

Using Makefiles for automated builds

If you want, I can also give you a much better GitHub README (with badges, project preview, and sample output) so your repository looks more professional when someone opens it.
