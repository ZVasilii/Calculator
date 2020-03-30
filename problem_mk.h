

#pragma once



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>




enum reg_t 
{
  A = 0, B = 1, C = 2, D = 3, RLAST = 4
};

enum 
{
	MOVI_MASK = (1<<7),
	SHIFT = 4,
	IO_CONST = 0b1100,
	SHIFT_REG = 2,
	IO_MASK = 0b11,
	REG_MASK = 0b11
};

enum opcode_t 
{
  MOVI = 0, ADD = 8, SUB = 9, MUL = 10, DIV = 11, IN = 12, OUT = 13, OPLAST
};

enum reg_flag_t
{
	ON = 1,
	OFF = 0
};

union operand_t 
{
  struct { int rd, rs; } ops;
  int rop;
  int imm;
};

struct instr_t 
{
  enum opcode_t opcode;
  union operand_t opnd;
};

struct reg_state_t
{
	///int data;
    ///char data;
	unsigned char data;
	char flag;
};


void def_arithm(unsigned char cmd, struct instr_t* instr);
void execute_instr(struct reg_state_t *reg, struct instr_t instr);
void execute_program(FILE *prog) ;
void print_instr(FILE* file, struct instr_t* instr);
void error(FILE* file, struct instr_t* instr, const char* msg);
void print_register(FILE* file, int reg);
void print_arithm(FILE* file, struct instr_t* instr, const char* msg);
void print_in_out(FILE* file, struct instr_t* instr, const char* msg);