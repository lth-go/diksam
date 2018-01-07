#include <locale.h>
#include <stdio.h>
#include "DKC.h"
#include "DVM.h"
#include "MEM.h"

int main(int argc, char **argv) {
    DKC_Compiler *compiler;
    FILE *fp;
    DVM_Executable *exe;
    DVM_VirtualMachine *dvm;

    if (argc < 2) {
        fprintf(stderr, "usage:%s filename arg1, arg2, ...", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    setlocale(LC_CTYPE, "");
    // 编译器
    compiler = DKC_create_compiler();
    // 生成字节码
    exe = DKC_compile(compiler, fp);
    // 虚拟机
    dvm = DVM_create_virtual_machine();
    DVM_add_executable(dvm, exe);
    // 虚拟机执行字节码
    DVM_execute(dvm);

    // 退出
    DKC_dispose_compiler(compiler);
    DVM_dispose_virtual_machine(dvm);

    MEM_check_all_blocks();
    MEM_dump_blocks(stdout);

    return 0;
}
