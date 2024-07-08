# Copyright 2024 10xEngineers

# ----------------------------------------------------------------
# RISC-V assembly program to output "Hello, World" on terminal
# ----------------------------------------------------------------

.global _start

.section .text
_start:
	# Load 1 into a0
	li a0, 1	#To output the message on stdout
	
	# Load address of message into a1
	la a1, message
	
	# Load length of message into a2
	li a2, 14	#Length of "Hello, World!\n"
	
	# Load the syscall number for write into a7
	li a7, 64	#syscall number for write
	
	# Make the syscall
	ecall
	
	# Exit the program
	li a0, 0	# Exit status
	li a7, 93	# syscall number for exit
	ecall


.section .data
message:
	.ascii "Hello, World!\n"
