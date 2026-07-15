#!/usr/bin/env python3
"""
将 Core/Src/main.c 中的 HAL 句柄定义同步到 bsp_hal_handle.h
"""

import re
import sys
from pathlib import Path

# 匹配 HAL 句柄定义
_HANDLE_RE = re.compile(
    r"^\s*(\w+_HandleTypeDef)\s+(h\w+)\s*;",
    re.MULTILINE,
)


def find_handles(main_c: Path) -> list[tuple[str, str]]:
    """扫描 main.c 中的 HAL 句柄定义，返回排序后的 (类型, 名称) 列表。"""
    content = main_c.read_text(encoding="utf-8")
    handles = _HANDLE_RE.findall(content)
    return sorted(set(handles), key=lambda kv: (kv[0], kv[1]))


def generate_header(handles: list[tuple[str, str]]) -> str:
    """生成 bsp_hal_handle.h 的内容。"""
    lines = [
        "#ifndef BSP_HAL_HANDLE_H",
        "#define BSP_HAL_HANDLE_H",
        '#include "main.h"',
        "",
    ]
    prev_type = None
    for htype, hname in handles:
        if htype != prev_type:
            if prev_type is not None:
                lines.append("")
            prev_type = htype
        lines.append(f"extern {htype} {hname};")
    lines += ["", "#endif //BSP_HAL_HANDLE_H", ""]
    return "\n".join(lines)


def main() -> int:
    project_root = Path(__file__).resolve().parent.parent
    main_c = project_root / "Core" / "Src" / "main.c"
    header_path = project_root / "BSP" / "bsp_hal_handle.h"

    handles = find_handles(main_c)

    if not handles:
        print("WARNING: no HAL handle definitions found in main.c — header will be empty!")

    header_path.write_text(generate_header(handles), encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())