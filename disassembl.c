#include "problem_mk.h"
extern const char* Name_Prog;


void error(FILE* file, struct instr_t* instr, const char* msg)
{
  fprintf(file, "Usage: %s <programm>\n", Name_Prog);
  fprintf(file, "%s\n", msg);
  print_instr(file, instr);
  abort();
}

void print_instr(FILE* file, struct instr_t* instr)
{
	switch (instr->opcode)
	{
		case MOVI:
		{
			fprintf(file, "MOVI ");
			fprintf(file, "%d\n", instr->opnd.imm);
			break;
		}

		case IN:
		{
			print_in_out(file, instr, "IN");
			break;
		}

		case OUT:
		{
			print_in_out(file, instr, "OUT");
			break;
		}

		case ADD:
		{
			print_arithm(file, instr, "ADD");
			break;
		}

		case MUL:
		{
			print_arithm(file, instr, "MUL");
			break;
		}

		case SUB:
		{
			print_arithm(file, instr, "SUB");
			break;
		}

		case DIV:
		{
			print_arithm(file, instr, "DIV");
			break;
		}

	}
}

void print_register(FILE* file, int reg)
{
	switch(reg)
	{
		case 0:
		{
			fprintf(file, "A");
			break;
		}

		case 1:
		{
			fprintf(file, "B");
			break;
		}

		case 2:
		{
			fprintf(file, "C");
			break;
		}

		case 3:
		{
			fprintf(file, "D");
			break;
		}
	}
}

void print_arithm(FILE* file, struct instr_t* instr, const char* msg)
{
	fprintf(file, "%s ", msg);
	print_register(file, instr->opnd.ops.rd);
	fprintf(file, ", ");
	print_register(file, instr->opnd.ops.rs);
	fprintf(file, "\n");
}

void print_in_out(FILE* file, struct instr_t* instr, const char* msg)
{
	fprintf(file, "%s ", msg);
	print_register(file, instr->opnd.ops.rd);
	fprintf(file, "\n");
}