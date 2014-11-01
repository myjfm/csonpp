#include "CsonppImpl.h"

#include <assert.h>
#include <algorithm>

START_CSONPP_NS

bool Parser::Deserialize(const std::string& irCsonppString, Value& orValue) {
  ParserImpl lImpl;
  return lImpl.Deserialize(irCsonppString, orValue);
}

void Parser::Serialize(const Value& irValue, std::string& orCsonppString) {
  ParserImpl lImpl;
  lImpl.Serialize(irValue, orCsonppString);
}

void ParserImpl::Serialize(const Value& irValue, std::string& orCsonppString) const {
  switch (irValue.Type()) {
  case Value::ValueType::OBJECT_T:
    orCsonppString = hSerializeObject(irValue);
    break;
  case Value::ValueType::ARRAY_T:
    orCsonppString = hSerializeArray(irValue);
    break;
  case Value::ValueType::STRING_T:
  {
    std::string lStrValue = irValue.String();
    //orCsonppString.append(1, '\"');
    orCsonppString.append(hSerializeString(lStrValue));
    //orCsonppString.append(1, '\"');
  }
    break;
  case Value::ValueType::DOUBLE_T:
    orCsonppString = StringUtils::Number2Str(irValue.Double());
    break;
  case Value::ValueType::INT_T:
    orCsonppString = StringUtils::Number2Str(irValue.Int());
    break;
  case Value::ValueType::BOOL_T:
    orCsonppString = irValue.Bool() ? "true" : "false";
    break;
  case Value::ValueType::NULL_T:
    orCsonppString = "null";
    break;
  default:
    orCsonppString = "";
    break;
  }
}

std::string ParserImpl::hSerializeObject(const Value& irValue) const {
  std::string lResult;
  const Object& lOValue = irValue.Object();
  lResult.append(1, '{');
  size_t lSize = irValue.Size();
  size_t lCur = 0;
  for (auto lConstItr = lOValue.Begin(); lConstItr != lOValue.End(); ++lConstItr, ++lCur) {
    lResult.append(hSerializeString(lConstItr->first));
    lResult.append(1, ':');
    std::string lSubStr;
    Serialize(lConstItr->second, lSubStr);
    lResult.append(lSubStr);
    if (lCur != lSize - 1)
      lResult.append(1, ',');
  }
  lResult.append(1, '}');
  return std::move(lResult);
}

std::string ParserImpl::hSerializeArray(const Value& irValue) const {
  std::string lResult;
  const Array& lAValue = irValue.Array();
  lResult.append(1, '[');
  size_t lSize = lAValue.Size();
  for (auto i = 0; i < lSize; ++i) {
    std::string lSubStr;
    Serialize(lAValue[i], lSubStr);
    lResult.append(lSubStr);
    if (i != lSize - 1)
      lResult.append(1, ',');
  }
  lResult.append(1, ']');
  return std::move(lResult);
}

std::string ParserImpl::hSerializeString(const std::string& irUtf8String) const {
  std::string lResult;
  const char* lpChar = irUtf8String.c_str();
  lResult.append(1, '\"');
  while (*lpChar) {
    int32_t lCodePoint = StringUtils::Utf82CodePoint(lpChar);
    if (lCodePoint < 0) {
      lResult.clear();
      return std::move(lResult);
    }

    if (lCodePoint > 0x7F) {
      if (lCodePoint <= 0xFFFF) { // in Basic Multilingual Plane
        lResult.append("\\u");
        lResult.append(1, StringUtils::Int2HexChar(lCodePoint >> 12));
        lResult.append(1, StringUtils::Int2HexChar((lCodePoint >> 8) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar((lCodePoint >> 4) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar(lCodePoint & 0xF));
      } else { // in Supplementary Planes
        lCodePoint -= 0x10000;
        assert(lCodePoint <= 0xFFFFF);
        int32_t lLeadSurrogate = 0xD800 + ((lCodePoint >> 10) & 0x3FF);
        int32_t lTrailSurrogate = 0xDC00 + (lCodePoint & 0x3FF);
        lResult.append("\\u");
        lResult.append(1, StringUtils::Int2HexChar(lLeadSurrogate >> 12));
        lResult.append(1, StringUtils::Int2HexChar((lLeadSurrogate >> 8) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar((lLeadSurrogate >> 4) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar(lLeadSurrogate & 0xF));
        lResult.append("\\u");
        lResult.append(1, StringUtils::Int2HexChar(lTrailSurrogate >> 12));
        lResult.append(1, StringUtils::Int2HexChar((lTrailSurrogate >> 8) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar((lTrailSurrogate >> 4) & 0xF));
        lResult.append(1, StringUtils::Int2HexChar(lTrailSurrogate & 0xF));
      }
    } else if (lCodePoint <= 0x1F) { // control charactor
      switch (lCodePoint) {
      case '\b': lResult.append("\\b"); break;
      case '\f': lResult.append("\\f"); break;
      case '\n': lResult.append("\\n"); break;
      case '\r': lResult.append("\\r"); break;
      case '\t': lResult.append("\\t"); break;
      default:
        lResult.append("\\u00");
        lResult.append(1, StringUtils::Int2HexChar((lCodePoint >> 4) & 0xf));
        lResult.append(1, StringUtils::Int2HexChar(lCodePoint & 0xf));
        break;
      }
    } else if (lCodePoint == '\\' || lCodePoint == '\"') {
      lResult.append(1, '\\');
      lResult.append(1, lCodePoint);
    } else {
      lResult.append(1, lCodePoint);
    }
  }
  lResult.append(1, '\"');
  return lResult;
}

bool ParserImpl::Deserialize(const std::string& irCsonppString, Value& orValue) {
  auto lErrorOccured = [&orValue, this] { orValue = Value(); hReset(); return false; };

  if (irCsonppString.empty())
    return lErrorOccured();

  mpCsonppString = &irCsonppString;
  mCurPos = 0;

  if (!hParseValue(orValue))
    return lErrorOccured();
  return true;
}

bool ParserImpl::hParseValue(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  Token lToken = hGetToken();
  switch (lToken.mType) {
  case TokenType::LEFT_BRACE_TT:
    return hParseObject(orValue);
  case TokenType::LEFT_BRACKET_TT:
    return hParseArray(orValue);
  case TokenType::STRING_TT:
    orValue = Value(lToken.mValue); return true;
  case TokenType::INTEGRAL_TT: {
    bool lValid = false;
    int64_t lInteger = _UTILS_::StringUtils::Str2Number<int64_t>(lToken.mValue, &lValid);
    if (!lValid)
      return lErrorOccured();
    orValue = Value(lInteger);
  }
    return true;
  case TokenType::DOUBLE_TT: {
    // TODO
    // string to float number convertion
    bool lValid = false;
    double lDouble = _UTILS_::StringUtils::Str2Number<double>(lToken.mValue, &lValid);
    if (!lValid)
      return lErrorOccured();
    orValue = Value(lDouble);
  }
    return true;
  case TokenType::TRUE_TT:
    orValue = Value(true);
    return true;
  case TokenType::FALSE_TT:
    orValue = Value(false);
    return true;
  case TokenType::NULL_TT:
    orValue = Value(nullptr);
    return true;
  default:
    return lErrorOccured();
  }
}

bool ParserImpl::hParseObject(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  orValue = Value(Value::ValueType::OBJECT_T);
  if (!hParseMembers(orValue)) {
    hUngetNextChar();
    auto lToken = hGetToken();
    if (lToken.mType != TokenType::RIGHT_BRACE_TT)
      return lErrorOccured();
    orValue = Value(Value::ValueType::OBJECT_T);
  }
  return true;
}

bool ParserImpl::hParseMembers(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  if (!hParsePair(orValue))
    return lErrorOccured();
  auto lToken = hGetToken();
  if (lToken.mType == TokenType::COMMA_TT) {
    return hParseMembers(orValue);
  } else if (lToken.mType == TokenType::RIGHT_BRACE_TT) {
    return true;
  } else {
    return lErrorOccured();
  }
}

bool ParserImpl::hParsePair(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  auto lToken = hGetToken();
  if (lToken.mType != TokenType::STRING_TT)
    return lErrorOccured();

  Token lNextToken = hGetToken();
  if (lNextToken.mType != TokenType::COLON_TT)
    return lErrorOccured();

  Value lSubValue;
  if (!hParseValue(lSubValue))
    return lErrorOccured();
  orValue[lToken.mValue] = lSubValue;
  return true;
}

bool ParserImpl::hParseArray(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  orValue = Value(Value::ValueType::ARRAY_T);
  if (!hParseElements(orValue)) {
    hUngetNextChar();
    auto lNextToken = hGetToken();
    if (lNextToken.mType != TokenType::RIGHT_BRACKET_TT)
      return lErrorOccured();
    orValue = Value(Value::ValueType::ARRAY_T);
  }
  return true;
}

bool ParserImpl::hParseElements(Value& orValue) {
  auto lErrorOccured = [&orValue] { orValue = Value(); return false; };
  Value lSubValue;
  if (!hParseValue(lSubValue))
    return lErrorOccured();
  orValue.PushBack(lSubValue);
  auto lNextToken = hGetToken();
  if (lNextToken.mType == TokenType::RIGHT_BRACKET_TT) {
    return true;
  } else if (lNextToken.mType == TokenType::COMMA_TT) {
    return hParseElements(orValue);
  }
  return lErrorOccured();
}

int ParserImpl::hGetNextChar() {
  return (*mpCsonppString)[mCurPos++];
}

void ParserImpl::hUngetNextChar() {
  mCurPos--;
}

ParserImpl::Token ParserImpl::hGetToken() {
  Token lToken;
  DFAState lState = DFAState::START;

  auto lErrorOccured = [&lToken] {
    lToken.mValue = "";
    lToken.mType = TokenType::DUMMY_TT;
    return lToken;
  };

  bool lHaveE = false;
  bool lHavePoint = false;

  while (true) {
    int c = hGetNextChar();
    switch (lState) {
      case DFAState::START:
        if (isspace(c)) {
          break;
        } else if (isdigit(c) || c == '-') {
          lState = DFAState::IN_INTEGRAL;
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::INTEGRAL_TT;
        } else if (c == ',') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::COMMA_TT;
          return lToken;
        } else if (c == ':') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::COLON_TT;
          return lToken;
        } else if (c == '{') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::LEFT_BRACE_TT;
          return lToken;
        } else if (c == '}') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::RIGHT_BRACE_TT;
          return lToken;
        } else if (c == '[') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::LEFT_BRACKET_TT;
          return lToken;
        } else if (c == ']') {
          lToken.mValue.append(1, char(c));
          lToken.mType = TokenType::RIGHT_BRACKET_TT;
          return lToken;
        } else if (c == '\"') {
          lState = DFAState::IN_STRING;
          lToken.mType = TokenType::STRING_TT;
        } else {
          switch (c) {
            case 't':
              if (hGetNextChar() == 'r' && 
                  hGetNextChar() == 'u' && 
                  hGetNextChar() == 'e') {
                lToken.mValue.append("true");
                lToken.mType = TokenType::TRUE_TT;
              }
              return lToken;
            case 'f':
              if (hGetNextChar() == 'a' && 
                  hGetNextChar() == 'l' && 
                  hGetNextChar() == 's' && 
                  hGetNextChar() == 'e') {
                lToken.mValue.append("false");
                lToken.mType = TokenType::FALSE_TT;
              }
              return lToken;
            case 'n':
              if (hGetNextChar() == 'u' && 
                  hGetNextChar() == 'l' && 
                  hGetNextChar() == 'l') {
                lToken.mValue.append("null");
                lToken.mType = TokenType::NULL_TT;
              }
              return lToken;
            default:
              return lErrorOccured();
          }
        }
        break;
      case DFAState::IN_STRING:
        switch (c) {
          case '\"':
            return lToken;
          case '\\':
          {
            int cc = hGetNextChar();
            switch (cc) {
              case '\"': lToken.mValue.append(1, '\"'); break;
              case '\\': lToken.mValue.append(1, '\\'); break;
              case 'r': lToken.mValue.append(1, '\r'); break;
              case 'n': lToken.mValue.append(1, '\n'); break;
              case 't': lToken.mValue.append(1, '\t'); break;
              case 'b': lToken.mValue.append(1, '\b'); break;
              case 'f': lToken.mValue.append(1, '\f'); break;
              case 'u': {
                // convert unicode escapse charactor
                char32_t lCodePoint = hDecodeUnicode();
                if (lCodePoint == 0)
                  return lErrorOccured();
                lToken.mValue += StringUtils::CodePoint2Utf8(lCodePoint);
              }
                break;
              default:
                return lErrorOccured();
            }
            break;
          }
          case '\0':
            return lErrorOccured();
          default:
            lToken.mValue.append(1, char(c)); break;
        }
        break;
      case DFAState::IN_INTEGRAL:
        if (isdigit(c)) {
          lToken.mValue.append(1, char(c));
        } else if (c == 'e' || c == 'E') {
          lHaveE = true;
          lToken.mValue.append(1, char(c));
          int cc = hGetNextChar();
          if (cc == '+' || cc == '-') {
            lToken.mValue.append(1, char(cc));
          } else {
            hUngetNextChar();
          }
          lState = DFAState::IN_REAL;
          lToken.mType = TokenType::DOUBLE_TT;
        } else if (c == '.') {
          lHavePoint = true;
          lToken.mValue.append(1, char(c));
          lState = DFAState::IN_REAL;
          lToken.mType = TokenType::DOUBLE_TT;
        } else if (isspace(c)) {
          return lToken;
        } else if (c == ',' || c == ']' || c == '}') {
          hUngetNextChar();
          return lToken;
        } else if (c == '\0') {
          return lToken;
        } else {
          return lErrorOccured();
        }
        break;
      case DFAState::IN_REAL:
        if (isdigit(c)) {
          lToken.mValue.append(1, char(c));
        } else if (c == 'e' || c == 'E') {
          if (lHaveE)
            return lErrorOccured();
          lHaveE = true;
          lToken.mValue.append(1, char(c));
          int cc = hGetNextChar();
          if (cc == '+' || cc == '-') {
            lToken.mValue.append(1, char(cc));
          } else {
            hUngetNextChar();
          }
        } else if (c == '.') {
          if (lHaveE || lHavePoint)
            return lErrorOccured();
          lHavePoint = true;
          lToken.mValue.append(1, char(c));
          lState = DFAState::IN_REAL;
          lToken.mType = TokenType::DOUBLE_TT;
        }
        else if (isspace(c)) {
          return lToken;
        } else if (c == ',' || c == ']' || c == '}') {
          hUngetNextChar();
          return lToken;
        } else if (c == '\0') {
          return lToken;
        } else {
          return lErrorOccured();
        }
        break;
      default:
        break;
    }
  }
}

int32_t ParserImpl::hDecodeUnicode() {
  auto lGetFourHexDigit = [this] (int& irCode1, int& irCode2, int& irCode3, int& irCode4) {
    irCode1 = StringUtils::HexChar2Int(static_cast<char>(hGetNextChar()));
    if (irCode1 < 0) return false;
    irCode2 = StringUtils::HexChar2Int(static_cast<char>(hGetNextChar()));
    if (irCode2 < 0) return false;
    irCode3 = StringUtils::HexChar2Int(static_cast<char>(hGetNextChar()));
    if (irCode3 < 0) return false;
    irCode4 = StringUtils::HexChar2Int(static_cast<char>(hGetNextChar()));
    if (irCode4 < 0) return false;
    return true;
  };

  int lCode1, lCode2, lCode3, lCode4;
  if (!lGetFourHexDigit(lCode1, lCode2, lCode3, lCode4))
    return 0;
  auto lCodePoint1 = (lCode1 << 12) + (lCode2 << 8) + (lCode3 << 4) + lCode4;
  if (lCodePoint1 >= 0xD800 && lCodePoint1 <= 0xDBFF) {
    // surrogate pair
    if (hGetNextChar() != '\\' || hGetNextChar() != 'u')
      return 0;

    int lCode5, lCode6, lCode7, lCode8;
    if (!lGetFourHexDigit(lCode5, lCode6, lCode7, lCode8))
      return 0;
    auto lCodePoint2 = (lCode5 << 12) + (lCode6 << 8) + (lCode7 << 4) + lCode8;
    if (lCodePoint2 < 0xDC00 && lCodePoint2 > 0xDFFF)
      return 0;
    lCodePoint1 = 0x10000 + ((lCodePoint1 & 0x3ff) << 10) + (lCodePoint2 & 0x3ff);
  } else if (lCodePoint1 >= 0xDC00 && lCodePoint1 <= 0xDFFF) {
    return 0;
  }
  return lCodePoint1;
}

END_CSONPP_NS

