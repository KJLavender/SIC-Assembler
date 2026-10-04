# SIC Assembler

**English** | [繁體中文](README.zh-TW.md)

A two-pass assembler for the SIC (Simplified Instructional Computer) machine, written in C as a systems programming course project.

## How it works

| Pass | Input | Output |
|---|---|---|
| Pass 1 | `SICP.txt` (source program), `OpTable.txt` (opcode table) | `LocCtr.txt` (each line with its location counter), `Symbol Table.txt`, `Program Length.txt` |
| Pass 2 | the Pass 1 outputs + `OpTable.txt` | `OJ Program.txt` (object program: H / T / E records) |

The sample program in `SICP.txt` is the classic `COPY` program starting at address `1000`; its object program begins with:

```
H^COPY  ^001000^00107A
T^001000^1E^141033^482039^001036^281030^301015^482061^3C1003^00102A^0C1039^00102D^
```

## Files

| File | Contents |
|---|---|
| `D0976935.cpp` | Assembler source (both passes) |
| `SICP.txt` | Input SIC source program |
| `OpTable.txt` | Mnemonic → opcode table |
| `LocCtr.txt` / `Symbol Table.txt` / `Program Length.txt` | Pass 1 output |
| `OJ Program.txt` | Final object program |
| `SIC Assembler 實作(完成).pdf` | Project report (Traditional Chinese) |

## Build and run

```bash
gcc D0976935.cpp -o sic-assembler   # or g++
./sic-assembler                      # reads SICP.txt and OpTable.txt from the current directory
```

Note: the comments and console messages in the source are Big5-encoded Traditional Chinese.
