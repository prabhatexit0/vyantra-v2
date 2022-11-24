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

also you can add `-v` flag if you want to see verbose output.
For verbose console output: 

if you've installed:
```
yantra {file_name}.ys -v
```
and if you have not installed (from project root directory):
```
./yantra.out {file_name}.ys -v
```


## How to code in **Vyantra-Assembly**?

## Specifications
Vyantra is a register based VM and supports three registers.
Three registers can be accessed in the language using `A`, `B` and `C` for first, second and third register repectively.

and you can load positive integer value by prefixing it with `#`.
### Syntax:
1. **Loading instructions into the memory:**
```
load {A | B | C} #{integer_value}
```

2. **Performing binary operations:**
Some binary mathematical and logical operations are also supported.
Binary Instructions: `add`, `sub`, `mult`, `div`, `and`, `or`, `xor`
```
{binary_instruction} {loading register} {operand register one} {operand register two}
```

3. **Jump Statements**
you can define label by prefixing a postive integer value with `:`
Like this:
```
:{int_value}
```
and to jump to he label defined, You can use this instruction.
```
jmp {int_value}
```

4. To halt a program. You can use `halt` instruction.
```
halt
```

### Sample Programs

#### Program 1:
```
!start
    load A #40
    load B #2
    add C B C
    show C
!end
```
#### Program 2:
_Warning: Infinite loop_
```
!start
    :9
    load B #40
    load C #2
    add A B C
    show A
    show B
    show C
    jmp 9
!end
```

_more to be added soon_
