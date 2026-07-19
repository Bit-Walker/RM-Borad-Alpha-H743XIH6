/**
 * @file    shell_cmd_reg.c
 * @brief   letter-shell 命令集中注册
 * @author  BitWalker
 * @version 1.0.0
 * @date    2026-07-19
 *
 */

#include "../shell_port.h"


/* ---- typeof -------------------------------------------------------------- */
extern int shellTypeof(int argc, char *argv[]);

SHELL_EXPORT_CMD(
    SHELL_CMD_PERMISSION(0) |
    SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN) |
    SHELL_CMD_DISABLE_RETURN,
    typeof,
    shellTypeof,
    print sizeof of C++ data types
);

