# Language Specification
--------------------------

## Functions
	String Identifier starting with @
	will have function body indented
	will have access to lexical scope

## Identifiers ? Optional
	idk if I should add these or not?

## Instructions
	Memory: Load 
	Mathematical: Add, Sub, Mult, Div
	Logical: And, Or, Xor
	Misc: jmp

## Registers 
	A, B, C

## Scaler Values
	Numeric Literals starting with #



### Sample Program:
```
!start
	jmp label
	@func: 
		load A #100
		load B #200
		add A B
		halt
	end @func
	call func
	:label
	load A #99	
	halt
!end
```

### MVP Program:
```
!start
	jmp label
	load B 10
	load C 20
	add A B C
	:label
	load A 99	
	halt
!end
```

