#!/usr/bin/env python3

import re
import sys
from pathlib import Path

HANDLE_RE = re.compile(
    r"^\s*(\w+_HandleTypeDef)\s+(h\w+)\s*;",
    re.MULTILINE)


def find_handles(main_c: Path) -> list[tuple[str, str]]:
    content = main_c.read_text(encoding="utf-8")
    return sorted(set(HANDLE_RE.findall(content)))


def generate_header(handles: list[tuple[str, str]]) -> str:
    lines = [
        "#ifndef BSP_HAL_HANDLE_H",
        "#define BSP_HAL_HANDLE_H",
        '#include "main.h"',
        "",
    ]
    
    for htype, hname in handles:
        lines.append(f"#define {hname.upper()}_ENABLED")
        lines.append(f"extern {htype} {hname};")
        lines.append("")
    lines += ["#endif //BSP_HAL_HANDLE_H", ""]
    
    return "\n".join(lines)


def main() -> int:
    root = Path(__file__).resolve().parent.parent
    main_c = root / "Core" / "Src" / "main.c"
    
    if not main_c.is_file():
        return 1
    
    (root / "BSP" / "bsp_hal_handle.h").write_text(
        generate_header(find_handles(main_c)), encoding="utf-8")
    
    return 0


if __name__ == "__main__":
    sys.exit(main())
