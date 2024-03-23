#include <stdio.h>
#include <stdlib.h>
#include "disasm_structs.h"
#include <assert.h>

//input example: 0x70 0xc7 0xc1 0x87
//in linux version IN possible via file

char regs_value[4] = {0};

void execute(struct instr_t instr){
    switch(instr.opcode){

    case OUT:
        printf("%d\n", regs_value[instr.opnd.rop]);
    break;

    case IN:
        int inp;
        if(scanf("%d", &inp) == 1){
            regs_value[instr.opnd.rop] = inp;
            puts("\n");
        }
        else
            perror("Invalid imm");
    break;

    case ADD:
        regs_value[instr.opnd.ops.rd] += regs_value[instr.opnd.ops.rs];
    break;

    case SUB:
        regs_value[instr.opnd.ops.rd] -= regs_value[instr.opnd.ops.rs];
    break;

    case MUL:
        regs_value[instr.opnd.ops.rd] *= regs_value[instr.opnd.ops.rs];
    break;

    case DIV:
        regs_value[instr.opnd.ops.rd] /= regs_value[instr.opnd.ops.rs];
    break;

    case MOVI:
        regs_value[3] = instr.opnd.imm;
    break;
    }
}

struct instr_t decode_comand(unsigned char cmd){
    struct instr_t instr;
    int rf1, rf2;

    // movi
    if(((cmd >> 7) & 1) == 0){
        instr.opcode = MOVI;
        instr.opnd.imm = cmd;
        return instr;
    }

    // in/out
    if(((cmd >> 6) & 1) == 1){
        //in: 110000
        //out:110001
        if((cmd>>2) == 0x31)
            instr.opcode = OUT;
        else if((cmd>>2) == 0x30)
            instr.opcode = IN;
        else{
            fprintf(stderr, "Bad inout: %x\n", (unsigned)cmd);
            abort();
        }
        rf1 = cmd & 0x3;
        instr.opnd.rop = rf1;
        return instr;
    }

    // add/sub/mul/div

    rf1 = cmd & 0x3;
    rf2 = (cmd>>2) & 0x3;
    instr.opnd.ops.rs= rf1;
    instr.opnd.ops.rd = rf2;

    switch((cmd >> 4) & 0xF){
        case 8: instr.opcode = ADD; return instr;
        case 9: instr.opcode = SUB; return instr;
        case 10: instr.opcode = MUL; return instr;
        case 11: instr.opcode = DIV; return instr;
    }
}

const char *regnames[] = {'A', 'B', 'C', 'D'};
const char *arithnames[] = {"ADD", "SUB", "MUL", "DIV"};

void print_instr(struct instr_t instr){
    switch(instr.opcode){
    case MOVI:
        printf("MOVI D %d\n", instr.opnd.imm);
    break;

    case IN:
        printf("IN %c\n", regnames[instr.opnd.rop]);
    break;

    case OUT:
        printf("OUT %c\n", regnames[instr.opnd.rop]);
    break;

    case ADD:
    case SUB:
    case MUL:
    case DIV:
        printf("%s %c, %c\n", arithnames[instr.opcode - 8],
               regnames[instr.opnd.ops.rd], regnames[instr.opnd.ops.rs]);
    break;

    default:
        fprintf(stderr, "Unsupported instruction");
        abort();
    break;
    }
}

int main(int argc, char *argv[]){
  // Проверяем, было ли передано имя файла как аргумент командной строки
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Открываем файл для чтения
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Failed to open the file.\n");
        return 1;
    }

    unsigned command;
    while (fscanf(file, "%x", &command) == 1) {
        struct instr_t instr;
        unsigned char cmd = command & 0xFF;
        assert(cmd == command);
        instr = decode_comand(cmd);
        //print_instr(instr);
        execute(instr);
    }

    fclose(file);

    return 0;
}
