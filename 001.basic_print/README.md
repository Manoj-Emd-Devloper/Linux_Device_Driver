.. kernel-module:: ldd
   :name: Simple Linux Kernel Module
   :relevant-api: init_module, cleanup_module, insmod, rmmod

==============================
Simple Linux Kernel Module (ldd)
==============================

Load and interact with a basic Linux kernel module (`ldd`) on a virtualized Ubuntu system using **Multipass** and **VS Code Remote SSH**.

This project is a minimal example designed to demonstrate the lifecycle of a kernel module:
**build → insert → interact → remove**.

---

📌 **Overview**
================

This module:

- Registers itself under `/proc/my_driver`
- Provides simple kernel-user interaction via a **Python** script
- Is built and tested in a **Multipass Ubuntu VM**, accessed through **VS Code Remote SSH**

---

📁 **Project Structure**
=========================

- `ldd.c` — Kernel module source file
- `user-app.py` — Python script to read from `/proc/my_driver`
- `Makefile` — Build system for compiling and cleaning the kernel module

---

🛠️ **Requirements**
======================

- Ubuntu (via Multipass or native)
- Linux kernel headers (`linux-headers-$(uname -r)`)
- `make` and `gcc`
- `python3`

---

⚙️ **Installation & Build**
=============================

.. code-block:: bash

   # Update & install build tools
   sudo apt update && sudo apt install make gcc build-essential

   # Navigate to the project directory
   cd ~/ubuntu/ldd

   # Build the kernel module
   make

---

📦 **Loading the Module**
===========================

.. code-block:: bash

   # Insert the kernel module
   sudo insmod ldd.ko

   # Verify it is loaded
   lsmod | grep ldd

   # Check recent kernel messages
   dmesg | tail

---

📂 **Interacting with the Module**
====================================

.. code-block:: bash

   # Read from the /proc interface
   cat /proc/my_driver

   # Run the Python user-space app
   python3 user-app.py

---

❌ **Removing the Module**
===========================

.. code-block:: bash

   # Remove the kernel module
   sudo rmmod ldd

   # Confirm it's removed
   lsmod | grep ldd  # Should return no output

---

🧹 **Clean the Build**
=======================

.. code-block:: bash

   make clean

---

📜 **Command History Reference**
==================================

.. code-block:: none

   cd ubuntu

   mkdir ldd

   cd ldd

   make

   sudo apt install make gcc

   make

   sudo apt install gcc-13 g++-13

   make clean

   make

   sudo dmesg -C

   sudo insmod ldd.ko

   lsmod | grep ldd

   cat /proc/my_driver

   python3 user-app.py
   
   sudo rmmod ldd.ko

---

📝 **Notes**
==============

- Run ``dmesg -C`` before inserting the module to view clean logs.
- Use ``lsmod`` to verify the module’s presence or removal.
- **Never** use `insmod` directly on `.c` files — always compile first and insert the `.ko`.

---

📖 **Further Reading**
=======================

- [Linux Kernel Module Programming Guide Video](https://youtu.be/iSiyDHobXHA?si=dnyD4LojjWRsEDPt)

---

🔒 **License**
===============

MIT (or specify your own license)

