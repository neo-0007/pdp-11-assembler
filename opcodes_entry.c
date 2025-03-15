#include "opcodes_entry.h"

ht_item double_op_opcodes[] = {
    {"MOV", "0001"},
    {"MOVB", "1001"},
    {"CMP", "0010"},
    {"CMPB", "1010"},
    {"BIT", "0011"},
    {"BITB", "1011"},
    {"BIC", "0100"},
    {"BICB", "1100"},
    {"BIS", "0101"},
    {"BISB", "1101"},
    {"ADD", "0110"},
    {"SUB", "1110"}
};

ht_item single_op_opcodes[] = {
    {"CLR", "0000101000"},
    {"CLRB", "1000101000"},
    {"COM", "0000101010"},
    {"COMB", "1000101010"},
    {"INC", "0000101010"},
    {"INCB", "1000101010"},
    {"DEC", "0000101011"},
    {"DECB", "1000101011"},
    {"ADC", "0000101101"},
    {"ADCB", "1000101101"},
    {"SBC", "0000101110"},
    {"SBCB", "1000101110"},
    {"TST", "0000101111"},
    {"TSTB", "1000101111"},
    {"ROR", "0000110000"},
    {"RORB", "1000110000"},
    {"ROL", "0000110001"},
    {"ROLB", "1000110001"},
    {"ASR", "0000110010"},
    {"ASRB", "1000110010"},
    {"ASL", "0000110011"},
    {"ASLB", "1000110011"}
};

ht_item branch_op_opcodes[] = {
    {"BR", "00000001"},
    {"BNE", "00000010"},
    {"BEQ", "00000011"},
    {"BGE", "00000100"},
    {"BLT", "00000101"},
    {"BGT", "00000110"},
    {"BLT", "00000111"},
    {"BPL", "10000000"},
    {"BMI", "10000001"},
    {"BHI", "10000010"},
    {"BLOS", "10000011"},
    {"BVC", "10000100"},
    {"BVS", "10000101"},
    {"BCC", "10000110"},
    {"BCS", "10000111"}
};

int insert_opcodes_to_ht(ht** so_table,ht** do_table,ht** bo_table){
    if(ht_entry_kvlist(so_table,single_op_opcodes,sizeof(single_op_opcodes)/sizeof(single_op_opcodes[0]))!=0){
        return -1;
    }
    if(ht_entry_kvlist(do_table,double_op_opcodes,sizeof(double_op_opcodes)/sizeof(double_op_opcodes[0]))!=0){
        return -1;
    }
    if(ht_entry_kvlist(bo_table,branch_op_opcodes,sizeof(branch_op_opcodes)/sizeof(branch_op_opcodes[0]))!=0){
        return -1;
    }
    return 0;
}
