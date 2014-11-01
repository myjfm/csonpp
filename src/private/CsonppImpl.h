#ifndef _CSONPP_CSONPPIMPL_H_
#define _CSONPP_CSONPPIMPL_H_

#include "../Csonpp.h"

#include <map>
#include <vector>

/***************************************
 * the grammer of json:
 * object   -> {}
 *          -> { members }
 *
 * members  -> pair
 *          -> pair, members
 *
 * pair     -> string : value
 *
 * array    -> []
 *          -> [ elements ]
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

struct Token {
  enum class Type {
    DUMMY_T, 
    LEFT_BRACE_T,     // {
    RIGHT_BRACE_T,    // }
    LEFT_BRACKET_T,   // [
    RIGHT_BRACKET_T,  // ]
    COMMA_T,          // ,
    COLON_T,          // :
    STRING_T,         // "xxx"
    INTEGER_T,        // integer
    DOUBLE_T,         // -0.99e-5
    TRUE_T,           // true
    FALSE_T,          // false
    NULL_T,           // null
  };

  std::string mValue;
  Type mType;

  Token() : mType(Type::DUMMY_T) {}

  bool IsOk() {
    return mType != Type::DUMMY_T;
  }
};

class TokenizerImpl {
public:
  TokenizerImpl(const std::string* ipCsonppString) 
  : mpCsonppString(ipCsonppString), 
    mCurPos(0) {
    assert(mpCsonppString);
  }

  ~TokenizerImpl() {}

  void Reset() {
    mpCsonppString = nullptr;
    mCurPos = 0;
  }

  int GetNextChar() {
    return (*mpCsonppString)[mCurPos++];
  }

  void UngetNextChar() {
    mCurPos--;
  }

  Token GetToken();

private:
  const std::string* mpCsonppString;
  size_t mCurPos;

  int32_t hDecodeUnicode();
};

class ParserImpl {
public:
  ParserImpl() {}
  ~ParserImpl() {}

  bool Deserialize(const std::string& irCsonppString, Value& orValue);
  void Serialize(const Value& irValue, std::string& orCsonppString) const;

private:
  std::shared_ptr<TokenizerImpl> mTokenizer;

  bool hParseValue(Value& orValue);
  bool hParseObject(Value& orValue);
  bool hParseMembers(Value& orValue);
  bool hParsePair(Value& orValue);
  bool hParseArray(Value& orValue);
  bool hParseElements(Value& orValue);

  std::string hSerializeObject(const Value& irValue) const;
  std::string hSerializeArray(const Value& irValue) const;
  std::string hSerializeString(const std::string& irUtf8String) const;
};

template<class T>
T Str2Number(const std::string& irStr, bool* isValid = nullptr) {
  isValid = false;
  T res = 0;
  return res;
}

template<>
int8_t Str2Number<int8_t>(const std::string& irStr, bool* ipIsValid) {
  long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stol(irStr);
    if (lResult < INT8_MIN || lResult > INT8_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<int8_t>(lResult);
}

template<>
uint8_t Str2Number<uint8_t>(const std::string& irStr, bool* ipIsValid) {
  unsigned long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stoul(irStr);
    if (lResult > UINT8_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<uint8_t>(lResult);
}

template<>
int16_t Str2Number<int16_t>(const std::string& irStr, bool* ipIsValid) {
  long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stol(irStr);
    if (lResult < INT16_MIN || lResult > INT16_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<int16_t>(lResult);
}

template<>
uint16_t Str2Number<uint16_t>(const std::string& irStr, bool* ipIsValid) {
  unsigned long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stoul(irStr);
    if (lResult > UINT16_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<uint16_t>(lResult);
}

template<>
int32_t Str2Number<int32_t>(const std::string& irStr, bool* ipIsValid) {
  long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stol(irStr);
    if (lResult < INT32_MIN || lResult > INT32_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<int32_t>(lResult);
}

template<>
uint32_t Str2Number<uint32_t>(const std::string& irStr, bool* ipIsValid) {
  unsigned long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stoul(irStr);
    if (lResult > UINT32_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<uint32_t>(lResult);
}

template<>
int64_t Str2Number<int64_t>(const std::string& irStr, bool* ipIsValid) {
  long long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stoll(irStr);
    if (lResult < INT64_MIN || lResult > INT64_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<int64_t>(lResult);
}

template<>
uint64_t Str2Number<uint64_t>(const std::string& irStr, bool* ipIsValid) {
  unsigned long long lResult = 0;
  bool lIsValid = true;
  try {
    lResult = std::stoull(irStr);
    if (lResult > UINT64_MAX) {
      lIsValid = false;
      lResult = 0;
    }
  } catch (std::invalid_argument&) {
    lIsValid = false;
    lResult = 0;
  } catch (std::out_of_range) {
    lIsValid = false;
    lResult = 0;
  }

  if (ipIsValid) {
    *ipIsValid = lIsValid;
  }

  return static_cast<uint64_t>(lResult);
}

template<>
float Str2Number<float>(const std::string& irStr, bool* ipIsValid) {
  float lResult = 0.;
  try {
    lResult = std::stof(irStr);
  } catch (std::invalid_argument&) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  } catch (std::out_of_range) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  }

  return lResult;
}

template<>
double Str2Number<double>(const std::string& irStr, bool* ipIsValid) {
  double lResult = 0.;
  try {
    lResult = std::stod(irStr);
  } catch (std::invalid_argument&) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  } catch (std::out_of_range) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  }

  return lResult;
}

template<>
long double Str2Number<long double>(const std::string& irStr, bool* ipIsValid) {
  long double lResult = 0.;
  try {
    lResult = std::stold(irStr);
  } catch (std::invalid_argument&) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  } catch (std::out_of_range) {
    if (ipIsValid) {
      *ipIsValid = false;
    }
    lResult = 0.;
  }

  return lResult;
}

END_CSONPP_NS

#endif

