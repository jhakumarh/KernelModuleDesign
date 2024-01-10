# Linux Kernel Module: Jiffies and Seconds Tracker

This repository hosts two Linux kernel modules that interact with the proc filesystem to provide system information regarding time measures within the kernel.

## Project Overview

The project comprises two kernel modules:

- The `jiffies` module creates a file in `/proc` that reports the current value of the kernel's `jiffies` counter whenever it's read.
- The `seconds` module similarly creates a `/proc` file but reports the number of seconds that have elapsed since the module was loaded.

These modules are useful for understanding how kernel modules work and for exploring the Linux timekeeping mechanisms.

## Kernel Modules

- **Jiffies Module (`jiffies`)**: Upon reading `/proc/jiffies`, the module outputs the current `jiffies` count since the last boot.
- **Seconds Module (`seconds`)**: Reading `/proc/seconds` returns the seconds elapsed since the module was loaded, demonstrating calculation with `jiffies`.

## Repository Contents

- `jiffies.c`: The source code for the jiffies module.
- `jiffies.ko`: The compiled kernel module ready for insertion into the kernel.
- `Makefile`: The makefile to compile and clean the kernel modules.
- Additional `.mod.c`, `.mod.o`, `.o`, and `modules.order` files are generated during the build process and are necessary for loading the module into the kernel.

## Building and Running the Modules

To compile the modules, ensure you have the Linux kernel headers installed, then run:

```sh
make
