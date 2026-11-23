#ifndef UASM_DWARF_H
#define UASM_DWARF_H
struct expr;
void dwarf_cfi_begin(struct dsym *proc);
void dwarf_cfi_instruction(unsigned token, const struct expr *ops);
void dwarf_cfi_epilogue(bool begin);
void dwarf_init(void);
void dwarf_body(struct dsym *proc);
void dwarf_epilogue(struct dsym *proc, unsigned first, unsigned last);
void dwarf_line(unsigned file, uint_32 line);
void dwarf_write(void);
bool dwarf_section(const struct dsym *seg);
#endif
