#include <utility>

#include "gtest/gtest.h"
#include "utils/stringbycharprovider.h"

extern "C" {
#include "../src/lexer_fsm.h"
}

class LexerFSMTestFixture : public ::testing::Test {
    protected:
        LexerFSM* lexer_fsm;
        StringByCharProvider* provider = StringByCharProvider::instance();

        virtual void SetUp() {
            lexer_fsm = lexer_fsm_init(token_stream);
            provider->reset();
        }

        virtual void TearDown() {
            lexer_fsm_free(&lexer_fsm);
        }

};

TEST_F(LexerFSMTestFixture, IsFinalStateTest) {

    std::vector<LexerFSMState> final_states = {
            // FINAL STATES
            LEX_FSM__ADD, LEX_FSM__SUBTRACT, LEX_FSM__DIVIDE,
            LEX_FSM__MULTIPLY, LEX_FSM__LEFT_BRACKET, LEX_FSM__RIGHT_BRACKET,
            LEX_FSM__INTEGER_LITERAL_FINISHED, LEX_FSM__DOUBLE_FINISHED, LEX_FSM__STRING_VALUE,
            LEX_FSM__SMALLER_BIGGER,

            // Relation operators
            LEX_FSM__SMALLER, LEX_FSM__BIGGER, LEX_FSM__SMALLER_EQUAL,
            LEX_FSM__BIGGER_EQUAL, LEX_FSM__IDENTIFIER_FINISHED,
            LEX_FSM__EQUAL, LEX_FSM__SEMICOLON, LEX_FSM__COMMA,

            // Reserve words
            LEX_FSM__AS, LEX_FSM__ASC, LEX_FSM__DECLARE,
            LEX_FSM__DIM, LEX_FSM__DO, LEX_FSM__DOUBLE,
            LEX_FSM__ELSE, LEX_FSM__END, LEX_FSM__CHR,
            LEX_FSM__FUNCTION, LEX_FSM__IF, LEX_FSM__INPUT,
            LEX_FSM__INTEGER, LEX_FSM__LENGTH, LEX_FSM__LOOP,
            LEX_FSM__PRINT, LEX_FSM__RETURN, LEX_FSM__SCOPE,
            LEX_FSM__STRING, LEX_FSM__SUBSTR, LEX_FSM__THEN,
            LEX_FSM__WHILE, LEX_FSM__AND, LEX_FSM__BOOLEAN,
            LEX_FSM__CONTINUE, LEX_FSM__ELSEIF, LEX_FSM__EXIT,
            LEX_FSM__FALSE, LEX_FSM__FOR, LEX_FSM__NEXT,
            LEX_FSM__NOT, LEX_FSM__OR, LEX_FSM__SHARED,
            LEX_FSM__STATIC, LEX_FSM__TRUE,

            // Error state
            LEX_FSM__ERROR,
    };

    std::vector<LexerFSMState> non_final_states = {
            // Start state
            LEX_FSM__INIT,

            // Comments
            LEX_FSM__COMMENT_LINE, LEX_FSM__SLASH, LEX_FSM__COMMENT_BLOCK, LEX_FSM__COMMENT_BLOCK_END,


            // Sharp brackets
            LEX_FSM__LEFT_SHARP_BRACKET, LEX_FSM__RIGHT_SHARP_BRACKET,

            // Other unfinished states
            LEX_FSM__IDENTIFIER_UNFINISHED, LEX_FSM__INTEGER_LITERAL_UNFINISHED, LEX_FSM__DOUBLE_DOT,
            LEX_FSM__DOUBLE_UNFINISHED, LEX_FSM__DOUBLE_E, LEX_FSM__DOUBLE_E_UNFINISHED,

            // String unfinished states
            LEX_FSM__STRING_EXC, LEX_FSM__STRING_LOAD, LEX_FSM__STRING_SLASH,
    };

    for(const LexerFSMState state: final_states) {

        EXPECT_TRUE(
                LEXER_FSM_IS_FINAL_STATE(state)
        ) << "Error testing final state";
    }

    for(const LexerFSMState state: non_final_states) {

        EXPECT_FALSE(
                LEXER_FSM_IS_FINAL_STATE(state)
        ) << "Error testing final state";
    }


}


TEST_F(LexerFSMTestFixture, GettingIdentifierTypeTest) {

    EXPECT_EQ(
            lexer_fsm_get_identifier_state("and"),
            LEX_FSM__AND
    ) << "Error getting identifier type";

    EXPECT_EQ(
            lexer_fsm_get_identifier_state("__8zx__87"),
            LEX_FSM__IDENTIFIER_FINISHED
    ) << "Error getting identifier type";

}

TEST_F(LexerFSMTestFixture, UnknownCharacter) {
    provider->setString("@");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__ERROR
    ) << "Unknown character for lexer.";
}

TEST_F(LexerFSMTestFixture, UnknownState) {
    provider->setString("a");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_NUMERIC_CHAR),
            LEX_FSM__ERROR
    ) << "Unknown char in numeric character escape sequence.";

    EXPECT_EQ(
            lexer_fsm->lexer_error,
            LEXER_ERROR__STRING_FORMAT
    ) << "Stored string format error after invalid numeric escape sequence.";

}

TEST_F(LexerFSMTestFixture, LineComment) {
    provider->setString("'");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__COMMENT_LINE
    ) << "Quote select line comment from init state.";

    provider->setString("a");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_LINE),
            LEX_FSM__COMMENT_LINE
    ) << "All content is ignored in comment line.";

    provider->setString("'");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_LINE),
            LEX_FSM__COMMENT_LINE
    ) << "Also quote is ignored in line comment.";

    provider->setString("\n");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_LINE),
            LEX_FSM__INIT
    ) << "End of line resets line comment to init state.";
}

TEST_F(LexerFSMTestFixture, EOLTest) {

    provider->setString("\n");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__EOL
    ) << "Also quote is ignored in line comment.";

}

TEST_F(LexerFSMTestFixture, StringNumericChar) {
    provider->setString(R"(!"\114")");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__STRING_EXC
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_EXC),
            LEX_FSM__STRING_LOAD
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_LOAD),
            LEX_FSM__STRING_SLASH
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_SLASH),
            LEX_FSM__STRING_NUMERIC_CHAR
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_NUMERIC_CHAR),
            LEX_FSM__STRING_NUMERIC_CHAR
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_NUMERIC_CHAR),
            LEX_FSM__STRING_LOAD
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_LOAD),
            LEX_FSM__STRING_VALUE
    ) << "Error transition";

    EXPECT_EQ(
            lexer_fsm->stream_buffer->content[0],
            114
    ) << "Error result";

}

TEST_F(LexerFSMTestFixture, StringValue) {
    provider->setString("\n");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__STRING_LOAD),
            LEX_FSM__ERROR
    );

    EXPECT_EQ(
            lexer_fsm->lexer_error,
            LEXER_ERROR__STRING_FORMAT
    );
}

TEST_F(LexerFSMTestFixture, BlockComment) {
    provider->setString("/'");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__SLASH
    ) << "Slash is start character for comment or dividing.";
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__SLASH),
            LEX_FSM__COMMENT_BLOCK
    ) << "Quote in slash state turns state into block comment.";

    provider->setString("f/");
    for(int i = 0; i < 2; ++i) {
        EXPECT_EQ(
                lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_BLOCK),
                LEX_FSM__COMMENT_BLOCK
        ) << "All in block comment is ignored.";
    }
    provider->setString("'X'/");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_BLOCK),
            LEX_FSM__COMMENT_BLOCK_END
    ) << "Prepare for end of comment.";
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_BLOCK_END),
            LEX_FSM__COMMENT_BLOCK
    ) << "Prepared for end of comment, but broke.";
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_BLOCK),
            LEX_FSM__COMMENT_BLOCK_END
    ) << "Prepared for end of comment.";
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__COMMENT_BLOCK_END),
            LEX_FSM__INIT
    ) << "End of comment.";
}

TEST_F(LexerFSMTestFixture, MathematicOperations) {
    provider->setString("+-*/");

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__ADD_UNFINISHED
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__ADD_UNFINISHED),
            LEX_FSM__ADD
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__SUBTRACT_UNFINISHED
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__SUBTRACT_UNFINISHED),
            LEX_FSM__SUBTRACT
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__MULTIPLY_UNFINISHED
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__MULTIPLY_UNFINISHED),
            LEX_FSM__MULTIPLY
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__SLASH
    );

    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__SLASH),
            LEX_FSM__DIVIDE
    );
}

TEST_F(LexerFSMTestFixture, Identifier) {
    provider->setString("a");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__INIT),
            LEX_FSM__IDENTIFIER_UNFINISHED
    ) << "Quote select line comment from init state.";

    provider->setString("a");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__IDENTIFIER_UNFINISHED),
            LEX_FSM__IDENTIFIER_UNFINISHED
    ) << "Quote select line comment from init state.";

    provider->setString("a");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__IDENTIFIER_UNFINISHED),
            LEX_FSM__IDENTIFIER_UNFINISHED
    ) << "Quote select line comment from init state.";

    provider->setString(" ");
    EXPECT_EQ(
            lexer_fsm_next_state(lexer_fsm, LEX_FSM__IDENTIFIER_UNFINISHED),
            LEX_FSM__IDENTIFIER_FINISHED
    ) << "Quote select line comment from init state.";
}


