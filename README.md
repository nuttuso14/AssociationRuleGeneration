# AssociationRuleGeneration
This program is only developed for Data Mining course homework.

We will proposed a basic idea for creating Association rules corressponding to Apriori Algorithm. 

The proposed program is just developed in order to practice the basic knowledge of data mining. there are still some conflicts if an amount of data is so huge!

## Environment Requirement
* Programing - c++ (MinGW.org GCC-6.3.0-1)
* OS - Linux(bash), Windows10

## How to complie the program ?

* Linux(Recommend)
  If you use linux to compile the program, just type **make all** in the terminal 
  ```
  $make all
  ```
* Windows
  If use Window, please follow this command below
  ```
  $ g++ main.cpp -o main
  ```

## Let run the program !
Type the following commands for both cases. 
* Linux
  ```
  $ ./main <input_file> <min_support> <min_conf>
  ```
* Windows
  ```
  $ main.exe <input_file> <min_support> <min_conf> 
  ```
  **Note that** For both minimum support and minimum confidence, please put an integer number!. For example, If the minimum support is 2 and minimum confidence is 60%, type .. 
  ```
  $ ./main input.txt 2 60
  ```   
## Sample output
  
  If the rule generation is smoothly conducted, the output terminal should be below demonstrated. 
  
  ![terminalResult](img/terminalResult.png)
