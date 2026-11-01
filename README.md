# Information and Network Security Laboratory (INS Lab)

Interactive web portal and reference manual for the Information and Network Security Laboratory course under the CBCS Scheme, BMS Institute of Technology and Management (Autonomous Institute under VTU).

## Course Overview

- Course Code: INS Lab
- Department: Computer Science and Engineering
- Credits: 1 (L:T:P:S: 0:0:1:0)
- CIE Marks: 50
- SEE Marks: 50
- Examination Duration: 3 Hours

## Program Index

| Program | Title | Category | Source File | Compile Command |
|---|---|---|---|---|
| 1 | Caesar Cipher Encryption and Decryption using Security Key | Substitution Cipher | `prog1_caesar.c` | `gcc prog1_caesar.c -o prog1_caesar` |
| 2 | Polyalphabetic (Vigenere) Cipher Encryption and Decryption | Polyalphabetic Substitution | `prog2_vigenere.c` | `gcc prog2_vigenere.c -o prog2_vigenere` |
| 3 | Frequency Analysis & Brute-Force Decryption of Substitution Cipher | Cryptanalysis | `prog3_frequency_analysis.c` | `gcc prog3_frequency_analysis.c -o prog3_frequency_analysis` |
| 4 | Transposition (Columnar Permutation) Cipher Encryption and Decryption | Transposition Cipher | `prog4_transposition.c` | `gcc prog4_transposition.c -o prog4_transposition` |
| 5 | Birthday Attack Demonstration on Hash Function (Collision Detection) | Hash Collisions | `prog5_birthday_attack.c` | `gcc prog5_birthday_attack.c -o prog5_birthday_attack` |

## Lab Environment Setup

All programs in this repository are written in C and are meant to be compiled and executed on a Linux terminal (Ubuntu / WSL2 / VM) or standard GCC environment.

### 1. Install GCC Compiler

```bash
sudo apt update
sudo apt install build-essential
```

### 2. Verify Installation

```bash
gcc --version
```

### 3. Create Working Directory

```bash
mkdir ~/INS_Lab
cd ~/INS_Lab
```

### 4. General Compilation and Execution Pattern

```bash
# Compilation:
gcc <filename>.c -o <output_name>

# Execution:
./<output_name>
```

## Running the Web Portal Locally

To launch this interactive reference manual locally:

```bash
npm install
npm run dev
```

The portal will be accessible at `http://localhost:5173`.
