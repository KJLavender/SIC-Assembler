# SIC 組譯器

[English](README.md) | **繁體中文**

用 C 寫的 SIC（Simplified Instructional Computer）兩階段組譯器（two-pass assembler），是系統程式課程的期末專題。

## 運作方式

| 階段 | 輸入 | 輸出 |
|---|---|---|
| Pass 1 | `SICP.txt`（原始程式）、`OpTable.txt`（指令碼表） | `LocCtr.txt`（每一行加上位址計數器）、`Symbol Table.txt`（符號表）、`Program Length.txt`（程式長度） |
| Pass 2 | Pass 1 的輸出 + `OpTable.txt` | `OJ Program.txt`（目的程式：H／T／E 紀錄） |

`SICP.txt` 裡的範例是經典的 `COPY` 程式，起始位址 `1000`；產生的目的程式開頭如下：

```
H^COPY  ^001000^00107A
T^001000^1E^141033^482039^001036^281030^301015^482061^3C1003^00102A^0C1039^00102D^
```

## 檔案

| 檔案 | 內容 |
|---|---|
| `D0976935.cpp` | 組譯器原始碼（兩個階段） |
| `SICP.txt` | 輸入的 SIC 原始程式 |
| `OpTable.txt` | 助憶碼 → 指令碼對照表 |
| `LocCtr.txt` / `Symbol Table.txt` / `Program Length.txt` | Pass 1 的輸出 |
| `OJ Program.txt` | 最後的目的程式 |
| `SIC Assembler 實作(完成).pdf` | 專題報告 |

## 編譯與執行

```bash
gcc D0976935.cpp -o sic-assembler   # 或用 g++
./sic-assembler                      # 從目前目錄讀取 SICP.txt 和 OpTable.txt
```

注意：原始碼裡的註解和輸出訊息是 Big5 編碼的繁體中文。
