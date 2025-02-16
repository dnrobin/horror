/* ASCII CHARS */

#define C_SPACE			0x20
#define C_TAB			0x11
#define C_LF			0x12
#define C_CR			0x15

/* TOKEN DEFINITIONS */

// control blocks
#define T_LPAREN		0x0000
#define T_RPAREN		0x0001
#define T_LBRACK		0x0002
#define T_RBRACK		0x0003
#define T_LBBRAC		0x0004
#define T_RBBRAC		0x0005

// control chars
#define T_SEMICOL		0x0100
#define T_COLON			0x0101
#define T_COMMA			0x0102

// type identifiers
#define T_SQUOTE		0x0200
#define T_DQUOTE		0x0201
#define T_DOLLAR		0x0202

// type related
#define T_STRING		0x0300
#define T_INTEGER		0x0301
#define T_DECIMAL		0x0302
#define T_BOOL			0x0303
#define T_IDENTIFIER	0x0304

// operators
#define T_EQQ			0x0400
#define T_NEQ			0x0401
#define T_GT			0x0402
#define T_GTE			0x0403
#define T_LT			0x0404
#define T_LTE			0x0405
#define T_PLUS			0x0406
#define T_MINUS			0x0407
#define T_MULT			0x0408
#define T_DIV			0x0409
#define T_MOD			0x040A