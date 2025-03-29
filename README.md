
# Non-rectangular matrix modifier

*This project is a product of a practical task for my algorithms and data structures course at uni*

This program processes given non-rectangular matrix. New processed matrix will contain same number of lines, which will contain only elements prior to the last max element in this line.

**Example:**

This input matrix
```txt
1 2 1 1
1 1 5 5 5 1
9
9 1
```
Will be transformed into this output matrix
```txt
1 2
1 1 5 5 5
9
9
```

This program has 2 implementations:

The first one reads input matrix from standart console input and outputs modified matrix into standart console output

Second one reads input matrix from a binary file and outputs into a binary file (for more detailed description see [Binary file organisation](#binary-file-organisation))


## Binary File Organisation

In my implementation metadata is stored first. It consists of numbers of *size_t* type: number fo lines and pairs of numbers - (number of elements - 1) and byte offset from the beginning of the file. This byte offset shows the position of the first element of given line.

After metadata all elements of *int* type are stored in one bunch

**Example:**

Initial matrix (generated by tester - see [Running Tests](#running-tests)) 

```txt
7 
1 120 8 7 
10 124 24 3 5 6 2 9 1 2 7 0 9
8 164 40 6 0 6 2 6 1 8 7
9 196 56 2 0 2 3 7 5 9 2 2
3 232 72 9 7 3
1 244 88 1
7 248 104 9 3 1 9 4 7 8
```

The first number represents the number of lines, then each new line starts with a pair: (number of elements - 1) and offset

This matrix will be written to a binary file like this

```txt
0000000 0007 0000 0000 0000 0001 0000 0000 0000
0000010 0078 0000 0000 0000 000a 0000 0000 0000
0000020 007c 0000 0000 0000 0008 0000 0000 0000
0000030 00a4 0000 0000 0000 0009 0000 0000 0000
0000040 00c4 0000 0000 0000 0003 0000 0000 0000
0000050 00e8 0000 0000 0000 0001 0000 0000 0000
0000060 00f4 0000 0000 0000 0007 0000 0000 0000
0000070 00f8 0000 0000 0000 0007 0000 0003 0000
0000080 0005 0000 0006 0000 0002 0000 0009 0000
0000090 0001 0000 0002 0000 0007 0000 0000 0000
00000a0 0009 0000 0006 0000 0000 0000 0006 0000
00000b0 0002 0000 0006 0000 0001 0000 0008 0000
00000c0 0007 0000 0002 0000 0000 0000 0002 0000
00000d0 0003 0000 0007 0000 0005 0000 0009 0000
00000e0 0002 0000 0002 0000 0009 0000 0007 0000
00000f0 0003 0000 0001 0000 0009 0000 0003 0000
0000100 0001 0000 0009 0000 0004 0000 0007 0000
0000110 0008 0000
0000114
```
## Author

[@Mephi-100-phel](https://github.com/Mephi-100-phel)


## Run Locally

Clone the project

```bash
  git clone https://github.com/Mephi-100-phel/Non-rectangular-matrix-modifier
```

Go to the project directory

```bash
cd <directory with downloaded project>
```

To run the comand line implementation

```bash
make
./main_lab/lab1.out
```

To run the binaty file implementation

```bash
make dop
./add_task/dop.out <binary file with input matrix> <output binary file>
```

*Output binary file is optional*


## Running Tests

This project provides an option to create test input for the binary matrix processor

To create a test binary file run this code:

```bash
  make tester
  ./add_task/test.out <test binary file name>
```

*You must provide a file name via first command line argument*

