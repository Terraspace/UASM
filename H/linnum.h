
/* internal line number information used if -Zd or -Zi is set */

struct line_num_info {
    struct line_num_info *next;
    uint_32 number; /* source line number (v2.06: changed to 32-bit */
    union {
        uint_32 offset;
        /* the next struct is set if sym is != NULL ( COFF only ) */
        struct {
            uint_32 line_number:20,
                    file:12;
        };
    };
    union {
        unsigned srcfile;
        struct asym *sym; /* used if number is 0 ( COFF only ) */
    };
};

void LinnumInit( void );
void LinnumFini( void );
void QueueDeleteLinnum( struct qdesc * );

