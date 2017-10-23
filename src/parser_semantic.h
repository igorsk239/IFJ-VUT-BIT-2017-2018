#ifndef _PARSER_SEMANTIC_H
#define _PARSER_SEMANTIC_H

#include "symbol_register.h"
#include "token.h"
#include "error.h"
#include "llist.h"

typedef enum {
    SEMANTIC_ACTION__NONE,
    SEMANTIC_ACTION__FUNCTION_DECLARATION,
    SEMANTIC_ACTION__FUNCTION_DEFINITION,
    SEMANTIC_ACTION__VARIABLE_ASSIGNMENT
} SemanticAction;

typedef enum {
    OPERATION_ADD,
    OPERATION_SUB,
    OPERATION_MULTIPLY,
    OPERATION_INT_DIVIDE,
    OPERATION_DIVIDE,

    OPERATION_LAST
} Operations;

typedef struct operation_signature_t {
    LListBaseItem base;
    Operations operation_type;
    DataType operand_1_type;
    DataType operand_2_type;
    DataType result_type;
} OperationSignature;

typedef struct parser_semantic_t {
    SymbolRegister* register_;

    ErrorReport error_report;

    SemanticAction actual_action;

    // metadata
    SymbolFunction* actual_function; // Pointer to actual function
    SymbolVariable* actual_variable; // Pointer to actual variable
    size_t argument_index;
    bool function_declared;
    SymbolVariable* temp_variable1;
    SymbolVariable* temp_variable2;
    SymbolVariable* temp_variable3;
    LList* operations_signatures[OPERATION_LAST];
} ParserSemantic;

/**
 * Constructor for parser_semantic
 *
 * @return ParserSematic*
 */
ParserSemantic* parser_semantic_init();

/**
 * @brief Destructor for parser semantic
 *
 * @param ParserSemantic** parser
 */
void parser_semantic_free(ParserSemantic** parser);

/**
 * @brief Set actual action for parser semantic. Sematic actions are scenarios. We have to keep the action.
 *
 * @param parser_semantic
 * @param actual_action
 */
void parser_semantic_set_action(ParserSemantic* parser_semantic, SemanticAction actual_action);

/**
 * @brief Sets the function name for the current scenario.
 *
 * @param parser_semantic
 * @param char* name Name of function
 * @return bool
 */
bool parser_semantic_set_function_name(ParserSemantic* parser_semantic, char* name);

/**
 * @brief Find variable in symbol variable
 *
 * @param parser_semantic
 * @param token
 * @return SymbolVariable*
 */
SymbolVariable* parser_semantic_expect_symbol_variable(ParserSemantic* parser_semantic, Token token);

/**
 * @brief Add Variable to the actual symbol table
 *
 * @param parser_semantic
 * @param name
 * @param data_type
 * @return bool
 */
SymbolVariable* parser_semantic_add_symbol_variable(ParserSemantic* parser_semantic, char* name, DataType data_type);

/**
 * @brief If the actual action is ACTUAL_ACTION__FUNCTION_DECLARATION, then set return data type for actual function,
 *        If the actual action is ACTUAL_ACTION__FUNCTION_DEFINITION, then check return data type in symbol table
 *
 * @param parser_semantic
 * @param token_type
 * @return bool
 */
bool parser_semantic_set_function_return_data_type(ParserSemantic* parser_semantic, DataType token_type);

/**
 *
 * @param parser_semantic
 * @param name
 * @param data_type
 */
bool parser_semantic_add_function_parameter(ParserSemantic* parser_semantic, char* name, DataType data_type);

/**
 *
 * @param parser_semantic
 * @return
 */
bool parser_semantic_check_count_of_function_arguments(ParserSemantic* parser_semantic);

bool parser_semantic_check_function_definitions(ParserSemantic* parser_semantic);

void parser_semantic_add_built_in_functions(ParserSemantic* parser_semantic);

// TODO doc and test
void parser_semantic_add_operation_signature(ParserSemantic* parser_semantic, Operations operation, DataType operand_1_type, DataType operand_2_type, DataType result_type);

DataType parser_semantic_resolve_implicit_data_type_conversion(ParserSemantic* parser_semantic, Operations operation_type, DataType operand_1_type, DataType operand_2_type);

// TODO doc and test
bool operands_match_data_type_combination(DataType first_operand, DataType second_operand, DataType expected_operand_data_type_1, DataType expected_operand_data_type_2);

#endif //_PARSER_SEMANTIC_H
