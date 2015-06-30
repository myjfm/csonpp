#ifndef CSONPP_CSONPP_IMPL_H_
#define CSONPP_CSONPP_IMPL_H_

#include "../csonpp.h"

#include <cstdio>
#include <cstring>
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

namespace csonpp {

struct Token {
  enum class Type {
    kDummy,
    kLeftBrace,   // {
    kRightBrace,  // }
    kLeftBracket, // [
    kRightBracket,// ]
    kComma,       // ,
    kColon,       // :
    kString,      // "xxx"
    kInteger,     // integer
    kDouble,      // -0.99e-5
    kTrue,        // true
    kFalse,       // false
    kNull,        // null
  };

  std::string value_;
  Type type_;

  Token() : type_(Type::kDummy) {}

  bool IsOk() {
    return type_ != Type::kDummy;
  }
};

class TokenizerImpl {
 public:
  TokenizerImpl(const std::string* csonpp_str)
      : csonpp_str_(csonpp_str),
        cur_pos_(0) {
    assert(csonpp_str_);
  }

  ~TokenizerImpl() {
  }

  void Reset() {
    csonpp_str_ = nullptr;
    cur_pos_ = 0;
  }

  int GetNextChar() {
    return (*csonpp_str_)[cur_pos_++];
  }

  void UngetNextChar() {
    cur_pos_--;
  }

  Token GetToken();

 private:
  const std::string* csonpp_str_;
  size_t cur_pos_;

  int32_t DecodeUnicode();
};

class ParserImpl {
public:
  ParserImpl() {}
  ~ParserImpl() {}

  bool Deserialize(const std::string& csonpp_str, Value& value);
  void Serialize(const Value& value, std::string& csonpp_str) const;

private:
  std::shared_ptr<TokenizerImpl> tokenizer_;

  bool ParseValue(Value& value);
  bool ParseObject(Value& value);
  bool ParseMembers(Value& value);
  bool ParsePair(Value& value);
  bool ParseArray(Value& value);
  bool ParseElements(Value& value);

  std::string SerializeObject(const Value& value) const;
  std::string SerializeArray(const Value& value) const;
  std::string SerializeString(const std::string& utf8_str) const;
};

template<class T>
std::string Number2Str(T num) {
  return std::to_string(num);
}

template<>
std::string Number2Str<float>(float num) {
  char buf[32];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__)
  sprintf_s(buf, 32, "%#.8g", num);
#else
  std::sprintf(buf, "%#.8g", num);
#endif
  char* tail = buf + strlen(buf) - 1;
  if (*tail != '0') return buf;
  while (tail > buf && *tail == '0') {
    --tail;
  }
  char* last_nonzero = tail;
  while (tail >= buf) {
    switch (*tail) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      --tail;
      break;
    case '.':
      *(last_nonzero + 2) = '\0';
      return buf;
    }
  }
  return buf;
}

template<>
std::string Number2Str<double>(double num) {
  char buf[64];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__)
  sprintf_s(buf, 64, "%#.16g", num);
#else
  std::sprintf(buf, "%#.16g", num);
#endif
  char* tail = buf + strlen(buf) - 1;
  if (*tail != '0') return buf;
  while (tail > buf && *tail == '0') {
    --tail;
  }
  char* last_nonzero = tail;
  while (tail >= buf) {
    switch (*tail) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      --tail;
      break;
    case '.':
      *(last_nonzero + 2) = '\0';
      return buf;
    }
  }
  return buf;
}

// TODO
// do not support long double
#if 0
template<>
std::string Number2Str<long double>(long double num) {
  char buf[128];
#if defined(_MSC_VER) && defined(__STDC_SECURE_LIB__)
  sprintf_s(buf, 128, "%#.32g", num);
#else
  std::sprintf(buf, "%#.32g", num);
#endif
  char* tail = buf + strlen(buf) - 1;
  if (*tail != '0') return buf;
  while (tail > buf && *tail == '0') {
    --tail;
  }
  char* last_nonzero = tail;
  while (tail >= buf) {
    switch (*tail) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      --tail;
      break;
    case '.':
      *(last_nonzero + 2) = '\0';
      return buf;
    }
  }
  return buf;
}
#endif

template<class T>
T Str2Number(const std::string& str, bool* valid = nullptr) {
  if (valid) {
    *valid = false;
  }
  T res = 0;
  return res;
}

template<>
int8_t Str2Number<int8_t>(const std::string& str, bool* valid) {
  long result = 0;
  bool success = true;
  try {
    result = std::stol(str);
    if (result < INT8_MIN || result > INT8_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<int8_t>(result);
}

template<>
uint8_t Str2Number<uint8_t>(const std::string& str, bool* valid) {
  unsigned long result = 0;
  bool success = true;
  try {
    result = std::stoul(str);
    if (result > UINT8_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<uint8_t>(result);
}

template<>
int16_t Str2Number<int16_t>(const std::string& str, bool* valid) {
  long result = 0;
  bool success = true;
  try {
    result = std::stol(str);
    if (result < INT16_MIN || result > INT16_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<int16_t>(result);
}

template<>
uint16_t Str2Number<uint16_t>(const std::string& str, bool* valid) {
  unsigned long result = 0;
  bool success = true;
  try {
    result = std::stoul(str);
    if (result > UINT16_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<uint16_t>(result);
}

template<>
int32_t Str2Number<int32_t>(const std::string& str, bool* valid) {
  long result = 0;
  bool success = true;
  try {
    result = std::stol(str);
    if (result < INT32_MIN || result > INT32_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<int32_t>(result);
}

template<>
uint32_t Str2Number<uint32_t>(const std::string& str, bool* valid) {
  unsigned long result = 0;
  bool success = true;
  try {
    result = std::stoul(str);
    if (result > UINT32_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<uint32_t>(result);
}

template<>
int64_t Str2Number<int64_t>(const std::string& str, bool* valid) {
  long long result = 0;
  bool success = true;
  try {
    result = std::stoll(str);
    if (result < INT64_MIN || result > INT64_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<int64_t>(result);
}

template<>
uint64_t Str2Number<uint64_t>(const std::string& str, bool* valid) {
  unsigned long long result = 0;
  bool success = true;
  try {
    result = std::stoull(str);
    if (result > UINT64_MAX) {
      success = false;
      result = 0;
    }
  } catch (std::invalid_argument&) {
    success = false;
    result = 0;
  } catch (std::out_of_range) {
    success = false;
    result = 0;
  }

  if (valid) {
    *valid = success;
  }

  return static_cast<uint64_t>(result);
}

template<>
float Str2Number<float>(const std::string& str, bool* valid) {
  float result = 0.;
  bool success = true;
  try {
    result = std::stof(str);
  } catch (std::invalid_argument&) {
    success = false;
    result = 0.;
  } catch (std::out_of_range) {
    success = false;
    result = 0.;
  }

  if (valid) {
    *valid = success;
  }

  return result;
}

template<>
double Str2Number<double>(const std::string& str, bool* valid) {
  double result = 0.;
  bool success = true;
  try {
    result = std::stod(str);
  } catch (std::invalid_argument&) {
    success = false;
    result = 0.;
  } catch (std::out_of_range) {
    success = false;
    result = 0.;
  }

  if (valid) {
    *valid = success;
  }

  return result;
}

template<>
long double Str2Number<long double>(const std::string& str, bool* valid) {
  long double result = 0.;
  bool success = true;
  try {
    result = std::stold(str);
  } catch (std::invalid_argument&) {
    success = false;
    result = 0.;
  } catch (std::out_of_range) {
    success = false;
    result = 0.;
  }

  if (valid) {
    *valid = success;
  }

  return result;
}

}  // namespace csonpp

#endif  // CSONPP_CSONPP_IMPL_H_

