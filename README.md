# VYantra V2
VYantra or Virtual Yantra is a minimalistic assembly language and a virtual machine. 'Yantra' is Sanskrit for a machine.

## But why?
Because I want to learn some shit (2).

## What all can it do?
For now, it supports some instructions using which you can load scaler values and perform mathematical and logical operations, jump statements etc. to get the answer to life universe and everything. Eventually I plan to add support for functions and more instructions to it.

## What all it can't do?
It can't solve any of the real life problems yet. Its like a little more than zygote now - not even an embryo.


## Usage

### Step 1:
git clone this repo in whatever directory you like.
```
git clone https://github.com/prabhatexit0/vyantra-v2.git
```
### Step 2:
Get into that directory and run the make command
```
cd vyantra-v2 && make
```
also optionally you can install **yantra** in you are on linux by running the following command while in project root directory
```
sudo make install
```
### Step 3:
Create a file with .ys extension and appropirate yantra language syntax (Syntax is documented below).
Then while you are in root directory of the project you can execute it like this: 
```
./yantra.out {file_name}.ys
```
and in case you've installed it, then from any directory where your file is located by doing:
```
yantra {file_name}.ys
```



