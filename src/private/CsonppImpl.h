#ifndef _CSONPP_CSONPPIMPL_H_
#define _CSONPP_CSONPPIMPL_H_

#include "../Csonpp.h"

#include <map>
#include <vector>

/***************************************
 * the grammer of json:
 * object   -> {}
            -> { members }
 *
 * members  -> pair
 *          -> pair, members
 *
 * pair     -> string : value
 *
 * array    -> []
            -> [ elements ]
 *
 * elements -> value
 *          -> value, elements
 * 
 * value    -> string
 *          -> number
 *          -> object
 *          -> array
 *          -> true
 *          -> false
 *          -> null
 **************************************/

START_CSONPP_NS

// RAII class
class ParserImpl {
public:
  ParserImpl() {
    hReset();
  }

  ~ParserImpl() {
    hReset();
  }

  bool Deserialize(const std::string& irCsonppString, Value& orValue);
  void Serialize(const Value& irValue, std::string& orCsonppString) const;

private:
  const std::string* mpCsonppString;
  size_t mCurPos;
  
  enum class DFAState {
    START, 
    IN_STRING, 
    IN_INTEGRAL, 
    IN_REAL, 
  };

  enum class TokenType {
    DUMMY_TT, 
    LEFT_BRACE_TT,    // {
    RIGHT_BRACE_TT,   // }
    LEFT_BRACKET_TT,  // [
    RIGHT_BRACKET_TT, // ]
    COMMA_TT,         // ,
    COLON_TT,         // :
    STRING_TT,        // "xxx"
    INTEGRAL_TT,      // 123
    DOUBLE_TT,        // 1.112
    TRUE_TT,          // true
    FALSE_TT,         // false
    NULL_TT,          // null
  };

  struct Token {
    std::string mValue;
    TokenType mType;

    Token() : mType(TokenType::DUMMY_TT) {}

    bool IsOk() {
      return mType != TokenType::DUMMY_TT;
    }
  };

  void hReset() {
    mpCsonppString = nullptr;
    mCurPos = 0;
  }

  // parser
  bool hParseValue(Value& orValue);
  bool hParseObject(Value& orValue);
  bool hParseMembers(Value& orValue);
  bool hParsePair(Value& orValue);
  bool hParseArray(Value& orValue);
  bool hParseElements(Value& orValue);

  // tokenizer
  int hGetNextChar();
  void hUngetNextChar();
  Token hGetToken();

  int32_t hDecodeUnicode();
  std::string hCodePoint2Utf8(int32_t iCodePoint) const;

  std::string hSerializeObject(const Value& irValue) const;
  std::string hSerializeArray(const Value& irValue) const;
  std::string hSerializeString(const std::string& irUtf8String) const;
};

END_CSONPP_NS

#endif

