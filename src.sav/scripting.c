// // $ G_SOUND_ID_GROANING 5

// // trigger_step_3: {
// // 	play_sound $G_SOUND_ID_GROANING$;
// // 	set_timer 300, player_turn_around();		#this is a comment line
// // 	set_timer 550, player_set_fear_level(7);
// // }


// char* p_input;
// unsigned int cpos, spos, epos;

// int load_stream(const char* filename) {}

// #define DEBUG_PRINT

// /* parsing flag names */
// #define P_PARSING_CONST_IDENTIFIER			0x0000

// /* to print debug info */
// char* _debug_string(const int id) {
// 	char* verbose[256];
	
// 	verbose[P_PARSING_CONST_IDENTIFIER] = "";
	
// 	return strings[id];
// }

// /* setting parser state flag */
// void set_state(const unsigned char state_id) {
// 	p_state[state_id] = true;
// 	#ifdef DEBUG_PRINT
// 	printf("\t--state_set (%d) : %s\n", state_id, _debug_string(state_id));
// 	#endif
// }
// /* unsetting parser state flag */
// void unset_state(const unsigned char state_id) {
// 	p_state[state_id] = false;
// 	#ifdef DEBUG_PRINT
// 	printf("\t--state_unset (%d) : %s\n", state_id, _debug_string(state_id));
// 	#endif
// }
// /* get character at input position */
// unsigned char getc() {
// 	if ( p_pos >= p_input_size ) {
// 		p_pos = p_input_size;
// 		return C_EOF;
// 	} else if ( p_pos < 0 ) {
// 		p_pos = -1;
// 		return C_BOF;
// 	}
// 	return p_input[p_pos];
// }
// /* read single token at input position */
// t_token read_token() {
	
// 	t_token t;
// 	unsigned char c = getc();
	
// 	// set default token type
// 	t.type = T_UNKNOWN;
	
// 	// skip any white space in the input
// 	while ( c == C_BOF || c == C_SPACE || c == C_TAB || c == C_LF || c == C_CR ) {
// 		p_pos++;
// 		c = getc();
// 	}
	
// 	// set token start position
// 	t.start = p_pos;
	
// 	// stop at end of file
// 	if ( c == C_EOF ) {
// 		t.type = T_EOF;
// 		return t;
// 	}
	
// 	// simple one char long tokens
// 	if ( c == "(" ) {
// 		t.type = T_LPAREN;
// 	}
// 	else if ( c == ")" ) {
// 		t.type = T_RPAREN;
// 	}
// 	else if ( c == "[" ) {
// 		t.type = T_LBRACK;
// 	}
// 	else if ( c == "]" ) {
// 		t.type = T_RBRACK;
// 	}
// 	else if ( c == "{" ) {
// 		t.type = T_LBBRAC;
// 	}
// 	else if ( c == "}" ) {
// 		t.type = T_RBBRAC;
// 	}
// 	else if ( c == ";" ) {
// 		t.type = T_SEMICOL;
// 	}
// 	else if ( c == ":" ) {
// 		t.type = T_COLON;
// 	}
// 	else if ( c == "," ) {
// 		t.type = T_COMMA;
// 	}
// 	else if ( c == "'" ) {
// 		t.type = T_SQUOTE;
// 	}
// 	else if ( c == "\"" ) {
// 		t.type = T_DQUOTE;
// 	}
// 	else if ( c == "$" ) {
// 		t.type = T_DOLLAR;
// 	}
	
// 	// check if found token
// 	if ( t.type != T_UNKNOWN ) {
// 		p_pos++;
// 		t.end = p_pos;
// 		return t;
// 	}
	
// 	// multiple character tokens
// 	while ( !is_whitespace(c) || !is_eof(c) ) {
	
// 		p_pos++;
// 		c = getc();
		
// 		if ( is_numeric(c) ) {
// 			set_state[P_PARSING_INTEGER];
// 			t.type = T_INTEGER	// default to integer type
// 				if ( c == "." )
// 					t.type = T_DECIMAL		// is a decimal number
// 		}
// 		if ( c == "." ) {
// 			if ( get_state[P_PARSING_NUMBER] ) {
// 				set_state[P_PARSING_DECIMAL_NUMBER];
// 				t.type = T_DECIMAL;
// 			}
// 			throw_error(ERROR_WRONG_TOKEN);
// 		}
		
		
// 		else if ( is_alpha(c) ) {
// 			t.type = T_IDENTIFIER	// default to itentifier type
// 			while ( ! )
// 		}
	
	
// 	else {
// 		t.type = T_UNKNOWN;
// 	}
	
// 	// read the token characters into the buffer
	
// 	else if ( c == "." ) {
// 		if ( p_state[P_PARSING_NUMBER] ) {
// 			//p_state[P_PARSING_DECIMAL_NUMBER];		// '.' are decimal points only for now
// 			t.type = T_DECIMAL;
// 		}
// 		else {
// 			t.type = T_UNKNOWN;
// 		}
// 	}

// }



// p_state[PARSE_STRING_LITERAL] = true;

// int parse_stream() {
// 	if ( c == '$' )		// define a constant
// 	{
// 		t_token id = get_token(&pos);
// 		t_token val = get_token(&pos);
	
// 		t_constant const;
	
// 		const.id = id;
// 		const.val = val;
	
// 		array_push( p_constants, const );
// 	}
// }



// t_token get_token(unsigned int* pos) {
	
// 	t_token token;
	
// 	// set token
// 	token.start_offset = *pos;
	
// 	while ( p_input[pos] != EOF || p_input[pos] != TSPACE || p_input[pos] != TTAB ) {
// 		// move up one char
// 		*pos ++;
// 	}
	
// 	// set token
// 	token.end_offset = *pos;
	
// 	// set token chars
// 	token.chars = malloc(sizeof(token.end_offset - token.start_offset + 1));
// 	token.chars = strcpy(p_input, )
	
// 	// 

// }