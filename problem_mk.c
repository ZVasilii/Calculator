
#include "problem_mk.h"
const char* Name_Prog;



int main(int argc, char* argv[]) 
{
  FILE *prog;
  
  Name_Prog =  argv[0];
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <programm>\n", Name_Prog);
    abort();
  }
  
  prog = fopen(argv[1], "r");
  if (NULL == prog) {
    fprintf(stderr, "Usage: %s <programm>\n", Name_Prog);
    fprintf(stderr, "Where file with programm shall exist\n");
    abort();
  }
  
  execute_program(prog);
  
  fclose(prog);
}



void def_arithm(unsigned char cmd, struct instr_t* instr)
{
	instr->opcode = cmd >> SHIFT;
	instr->opnd.ops.rd = (cmd >>  SHIFT_REG) & REG_MASK;
	instr->opnd.ops.rs = cmd & REG_MASK;
}

void execute_instr(struct reg_state_t *reg, struct instr_t instr)
{
  int d = 0;
  switch (instr.opcode)
  {
  	case MOVI:
  	{
      reg[D].data = instr.opnd.imm;
      reg[D].flag = ON;
      break;
  	}

  	case IN:
  	{
  		scanf("%d", &d);
  		reg[instr.opnd.rop].flag = ON;
      reg[instr.opnd.rop].data = d & 0xFF;
  		break;
  	}

  	case OUT:
  	{
  		if ((reg[instr.opnd.rop].flag) == ON)
  		  printf("%d\n", reg[instr.opnd.rop].data);
  		else 
  		error(stderr, &instr, "ERROR! Operation with non-initialized register: \n");
  		break;
  	}

  	case ADD:
  	{
  		if (((reg[instr.opnd.ops.rd].flag) == ON) && ((reg[instr.opnd.ops.rs].flag) == ON))
  		  reg[instr.opnd.ops.rd].data += reg[instr.opnd.ops.rs].data;
  		else 
  		{
  			error(stderr, &instr, "ERROR! Operation with non-initialized register: \n");
  		}
  		break;
  	}

  	case SUB:
  	{
  		if (((reg[instr.opnd.ops.rd].flag) == ON) && ((reg[instr.opnd.ops.rs].flag) == ON))
  		  reg[instr.opnd.ops.rd].data -= reg[instr.opnd.ops.rs].data;
  		else 
  		{
  			error(stderr, &instr, "ERROR! Operation with non-initialized register: \n");
  		}
  		break;
  	}

  	case MUL:
  	{
  		if (((reg[instr.opnd.ops.rd].flag) == ON) && ((reg[instr.opnd.ops.rs].flag) == ON))
  		  reg[instr.opnd.ops.rd].data *= reg[instr.opnd.ops.rs].data;
  		else 
  		{
  			error(stderr, &instr, "ERROR! Operation with non-initialized register: \n");
  		}
  		break;
  	}

  	case DIV:
  	{
  		if (((reg[instr.opnd.ops.rd].flag) == ON) && ((reg[instr.opnd.ops.rs].flag) == ON) && ((reg[instr.opnd.ops.rs].data) != 0))
  		  reg[instr.opnd.ops.rd].data /= reg[instr.opnd.ops.rs].data;
  		else  if ((reg[instr.opnd.ops.rs].data) == 0)
  			error(stderr, &instr, "ERROR! Division by zero: \n");
  		else 
  			error(stderr, &instr, "ERROR! Operation with non-initialized register: \n");

  		break;
  	}

  	default:
  	{
      error(stderr, &instr, "ERROR! Something went wrong \n");
  	}


  }
}

struct instr_t decode_instr(unsigned char cmd) 
{
  struct instr_t instr;

  if (!(cmd & MOVI_MASK))
  {
  	instr.opcode = MOVI;
  	instr.opnd.imm = cmd;
  } 
  else if ((cmd >> SHIFT) == IO_CONST)
  {
  	if ((cmd >> SHIFT_REG) & IO_MASK)
  	{
  		instr.opcode = OUT;
  		instr.opnd.rop = cmd & IO_MASK;
  	}
  	else
  	{
  		instr.opcode = IN;
  		instr.opnd.rop = cmd & IO_MASK;
  	}
  }
  else if (((cmd >> SHIFT) == ADD) || ((cmd >> SHIFT) == DIV) || ((cmd >> SHIFT) == MUL)  || ((cmd >> SHIFT) == SUB))
  	def_arithm(cmd, &instr);
  else 
  	{
  		fprintf(stderr, "Usage: %s <programm>\n", Name_Prog);
  		fprintf(stderr, "Wrong syntax at command 0x%x\n", cmd);
        abort();
  	}
  	
  return instr;
}

void execute_program(FILE *prog) 
{
  unsigned command;
  struct reg_state_t regs[RLAST];
  int i = 0;
  for (i = 0; i < RLAST; i++)
  	regs[i].flag = OFF;
  
  while (fscanf(prog, "%x", &command) == 1) 
  {
    struct instr_t instr;
    unsigned char cmd = command & 0xff;    
    assert(cmd == command);
    instr = decode_instr(cmd);

    #ifdef PRINT
    print_instr(stdout, &instr);
    #endif

    execute_instr(regs, instr);
  }
}


