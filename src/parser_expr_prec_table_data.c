#include "parser_expr_internal.h"

const int prec_table_size = 20;

// Copy-pasted from "/doc/prec_table.csv"
const char* prec_table = "\
<;>;>;>;>;>;>;>;>;>;>;>;x;>;>;<;>;>;<;>\n\
<;>;>;>;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;>;>;>;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;<;<;>;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;<;<;<;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;<;<;<;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;x;x;x;x;x;x;<;>;>;<;>;>;<;>\n\
x;>;>;>;>;>;>;>;>;>;>;>;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;<;<;<;<;<;<;<;>;>;<;>;>;<;>\n\
<;<;<;<;<;<;<;<;<;<;<;<;<;<;>;<;>;>;<;>\n\
<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;=;=;<;x\n\
>;>;>;>;>;>;>;>;>;>;>;>;>;>;>;x;>;>;x;>\n\
<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;=;=;<;x\n\
x;>;>;>;>;>;>;>;>;>;>;>;x;>;>;=;>;>;x;>\n\
<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;<;x;x;<;x\n\
";
