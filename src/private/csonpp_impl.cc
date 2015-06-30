#include "csonpp_impl.h"

#include <assert.h>
#include <algorithm>

namespace csonpp {

Object::Object(const Object& other)
    : value_(other.value_) {
}

Object::Object(Object&& other) 
: value_(std::move(other.value_)) {
}

Object& Object::operator=(const Object& other) {
  if (this != &other)
    value_ = other.value_;
  return *this;
}

Object& Object::operator=(Object&& other) {
  if (this != &other)
    value_ = std::move(other.value_);
  return *this;
}

Value& Object::operator[](const std::string& key) {
  return value_[key];
}

Value& Object::operator[](std::string&& key) {
  return value_[std::move(key)];
}

Object::ConstIterator Object::CBegin() const {
  return value_.cbegin();
}

Object::ConstIterator Object::CEnd() const {
  return value_.cend();
}

Object::ConstIterator Object::Begin() const {
  return value_.begin();
}

Object::ConstIterator Object::End() const {
  return value_.end();
}

Object::Iterator Object::Begin() {
  return value_.begin();
}

Object::Iterator Object::End() {
  return value_.end();
}

Object::Iterator Object::Find(const std::string& key) {
  return value_.find(key);
}

Object::ConstIterator Object::Find(const std::string& key) const {
  return value_.find(key);
}

void Object::Clear() {
  value_.clear();
}
size_t Object::Size() const {
  return value_.size();
}

Array::Array(const Array& array) 
: value_(array.value_) {
}

Array::Array(Array&& array) 
: value_(std::move(array.value_)) {
}

Array& Array::operator=(const Array& array) {
  if (this != &array)
    value_ = array.value_;
  return *this;
}

Array& Array::operator=(Array&& array) {
  if (this != &array)
    value_ = std::move(array.value_);
  return *this;
}

// the element must exist
Value& Array::operator[](size_t i) {
  assert(i < value_.size());
  return value_[i];
}

// the element must exist
const Value& Array::operator[](size_t i) const {
  assert(i < value_.size());
  return value_[i];
}

void Array::Append(const Value& value) {
  value_.push_back(value);
}

void Array::Append(Value&& value) {
  value_.push_back(std::move(value));
}

Array::ConstIterator Array::CBegin() const {
  return value_.cbegin();
}

Array::ConstIterator Array::CEnd() const {
  return value_.cend();
}

Array::ConstIterator Array::Begin() const {
  return value_.begin();
}

Array::ConstIterator Array::End() const {
  return value_.end();
}

Array::Iterator Array::Begin() {
  return value_.begin();
}

Array::Iterator Array::End() {
  return value_.end();
}

Array::Iterator Array::Find(const Value& value) {
  return std::find(Begin(), End(), value);
}

Array::ConstIterator Array::Find(const Value& value) const {
  return std::find(Begin(), End(), value);
}

void Array::Clear() {
  value_.clear();
}

size_t Array::Size() const {
  return value_.size();
}

Value::Value(Type type)
    : type_(type) {
}

Value::Value(std::nullptr_t null)
    : type_(Type::kNull) {
}

Value::Value(bool value) 
: type_(Type::kBool), 
  bool_(value) {
}

Value::Value(int8_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(uint8_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(int16_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(uint16_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(int32_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(uint32_t value) 
: type_(Type::kInteger), 
  integer_(static_cast<int64_t>(value)) {
}

Value::Value(int64_t value) 
: type_(Type::kInteger), 
  integer_(value) {
}

// TODO
// do not support uint64_t
#if 0
Value::Value(uint64_t value) 
: type_(Type::kInteger), 
  integer_(value) {
}
#endif

Value::Value(float value) 
: type_(Type::kDouble), 
  double_(static_cast<double>(value)) {
}

Value::Value(double value) 
: type_(Type::kDouble), 
  double_(value) {
}

Value::Value(const std::string& value) 
: type_(Type::kString), 
  string_(value) {
}

Value::Value(std::string&& value) 
: type_(Type::kString), 
  string_(std::move(value)) {
}

Value::Value(const Object& value) 
: type_(Type::kObject), 
  object_(value) {
}

Value::Value(Object&& value) 
: type_(Type::kObject), 
  object_(std::move(value)) {
}

Value::Value(const Array& value) 
: type_(Type::kArray), 
  array_(value) {
}

Value::Value(Array&& value) 
: type_(Type::kArray), 
  array_(std::move(value)) {
}

Value::Value(const Value& value) 
: type_(value.type_) {
  switch(type_) {
  case Type::kBool:
    bool_ = value.bool_;
    break;
  case Type::kInteger:
    integer_ = value.integer_;
    break;
  case Type::kDouble:
    double_ = value.double_;
    break;
  case Type::kString:
    string_ = value.string_;
    break;
  case Type::kObject:
    object_ = value.object_;
    break;
  case Type::kArray:
    array_ = value.array_;
    break;
  default:
    break;
  }
}

Value::Value(Value&& value) 
: type_(value.type_) {
  switch(type_) {
  case Type::kBool:
    bool_ = value.bool_;
    break;
  case Type::kInteger:
    integer_ = value.integer_;
    break;
  case Type::kDouble:
    double_ = value.double_;
    break;
  case Type::kString:
    string_ = std::move(value.string_);
    break;
  case Type::kObject:
    object_ = std::move(value.object_);
    break;
  case Type::kArray:
    array_ = std::move(value.array_);
    break;
  default:
    break;
  }
}

Value& Value::operator=(const Value& value) {
  if (&value != this) {
    type_ = value.type_;
    switch(type_) {
    case Type::kBool:
      bool_ = value.bool_;
      break;
    case Type::kInteger:
      integer_ = value.integer_;
      break;
    case Type::kDouble:
      double_ = value.double_;
      break;
    case Type::kString:
      string_ = value.string_;
      break;
    case Type::kObject:
      object_ = value.object_;
      break;
    case Type::kArray:
      array_ = value.array_;
      break;
    default:
      break;
    }
  }

  return *this;
}

Value& Value::operator=(Value&& value) {
  if (&value != this) {
    type_ = value.type_;
    switch(type_) {
    case Type::kBool:
      bool_ = value.bool_;
      break;
    case Type::kInteger:
      integer_ = value.integer_;
      break;
    case Type::kDouble:
      double_ = value.double_;
      break;
    case Type::kString:
      string_ = std::move(value.string_);
      break;
    case Type::kObject:
      object_ = std::move(value.object_);
      break;
    case Type::kArray:
      array_ = std::move(value.array_);
      break;
    default:
      break;
    }
  }

  return *this;
}

Value& Value::operator=(bool value) {
  type_ = Type::kBool;
  bool_ = value;
  return *this;
}

Value& Value::operator=(int8_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(uint8_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(int16_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(uint16_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(int32_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(uint32_t value) {
  type_ = Type::kInteger;
  integer_ = static_cast<int64_t>(value);
  return *this;
}

Value& Value::operator=(int64_t value) {
  type_ = Type::kInteger;
  integer_ = value;
  return *this;
}

// TODO
// do not support uint64_t
#if 0
Value& Value::operator=(uint64_t value) {
  type_ = Type::kInteger;
  integer_ = value;
  return *this;
}
#endif

Value& Value::operator=(float value) {
  type_ = Type::kDouble;
  double_ = static_cast<double>(value);
  return *this;
}

Value& Value::operator=(double value) {
  type_ = Type::kDouble;
  double_ = value;
  return *this;
}

Value& Value::operator=(const std::string& value) {
  type_ = Type::kString;
  string_ = value;
  return *this;
}

Value& Value::operator=(std::string&& value) {
  type_ = Type::kString;
  string_ = std::move(value);
  return *this;
}

Value& Value::operator=(const Object& value) {
  type_ = Type::kObject;
  object_ = value;
  return *this;
}

Value& Value::operator=(Object&& value) {
  type_ = Type::kObject;
  object_ = std::move(value);
  return *this;
}

Value& Value::operator=(const Array& value) {
  type_ = Type::kArray;
  array_ = value;
  return *this;
}

Value& Value::operator=(Array&& value) {
  type_ = Type::kArray;
  array_ = std::move(value);
  return *this;
}

void Value::Append(const Value& value) {
  assert(type_ == Type::kArray);
  array_.Append(value);
}

void Value::Append(Value&& value) {
  assert(type_ == Type::kArray);
  array_.Append(std::move(value));
}

void Value::Append(const std::string& key, bool value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, bool value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, int8_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, int8_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, uint8_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, uint8_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, int16_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, uint16_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, int32_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, int32_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, uint32_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, uint32_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, int64_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, int64_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

// TODO
// do not support uint64_t
#if 0
void Value::Append(const std::string& key, uint64_t value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, uint64_t value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}
#endif

void Value::Append(const std::string& key, float value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, float value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, double value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, double value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, const std::string& value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, const std::string& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, std::string&& value) {
  assert(type_ == Type::kObject);
  object_[key] = std::move(value);
}

void Value::Append(std::string&& key, std::string&& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = std::move(value);
}

void Value::Append(const std::string& key, const Object& value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, const Object& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, Object&& value) {
  assert(type_ == Type::kObject);
  object_[key] = std::move(value);
}

void Value::Append(std::string&& key, Object&& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = std::move(value);
}

void Value::Append(const std::string& key, const Array& value) {
  assert(type_ == Type::kObject);
  object_[key] = value;
}

void Value::Append(std::string&& key, const Array& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = value;
}

void Value::Append(const std::string& key, Array&& value) {
  assert(type_ == Type::kObject);
  object_[key] = std::move(value);
}

void Value::Append(std::string&& key, Array&& value) {
  assert(type_ == Type::kObject);
  object_[std::move(key)] = std::move(value);
}

Value::Type Value::GetType() const {
  return type_;
}

size_t Value::Size() const {
  assert(type_ == Type::kObject || type_ == Type::kArray);
  return (type_ == Type::kObject) ? object_.Size() : array_.Size();
}

void Value::Clear() {
  switch (type_) {
  case Type::kArray:
    array_.Clear();
    return;
  case Type::kObject:
    object_.Clear();
    return;
  default:
    assert(false);
    return;
  }
}

bool Value::IsNumeric() const {
  return (type_ == Type::kDouble || type_ == Type::kInteger);
}

bool Value::IsIntegral() const {
  return type_ == Type::kInteger;
}

bool Value::IsDouble() const {
  return type_ == Type::kDouble;
}

bool Value::IsBool() const {
  return type_ == Type::kBool;
}

bool Value::IsString() const {
  return type_ == Type::kString;
}

bool Value::IsObject() const {
  return type_ == Type::kObject;
}

bool Value::IsArray() const {
  return type_ == Type::kArray;
}

int64_t Value::AsInteger() const {
  if (type_ == Type::kInteger) {
    return integer_;
  } else if (type_ == Type::kDouble) {
    return static_cast<int64_t>(double_);
  } else {
    assert(false);
  }
}

double Value::AsDouble() const {
  if (type_ == Type::kInteger) {
    return static_cast<double>(integer_);
  } else if (type_ == Type::kDouble) {
    return double_;
  } else {
    assert(false);
  }
}

bool Value::AsBool() const {
  assert(type_ == Type::kBool);
  return bool_;
}

std::string Value::AsString() const {
  assert(type_ == Type::kString);
  return string_;
}

Object Value::AsObject() const {
  assert(type_ == Type::kObject);
  return object_;
}

Array Value::AsArray() const {
  assert(type_ == Type::kArray);
  return array_;
}

const int64_t& Value::GetInteger() const {
  assert(type_ == Type::kInteger);
  return integer_;
}

const double& Value::GetDouble() const {
  assert(type_ == Type::kDouble);
  return double_;
}

const bool& Value::GetBool() const {
  assert(type_ == Type::kBool);
  return bool_;
}

const std::string& Value::GetString() const {
  assert(type_ == Type::kString);
  return string_;
}

const Object& Value::GetObject() const {
  assert(type_ == Type::kObject);
  return object_;
}

const Array& Value::GetArray() const {
  assert(type_ == Type::kArray);
  return array_;
}

Value& Value::operator[](size_t i) {
  assert(type_ == Type::kArray);
  assert(i < array_.Size());
  return array_[i];
}

const Value& Value::operator[](size_t i) const {
  assert(type_ == Type::kArray);
  assert(i < array_.Size());
  return array_[i];
}

Value& Value::operator[](const std::string& key) {
  assert(type_ == Type::kObject);
  return object_[key];
}

Value& Value::operator[](std::string&& key) {
  assert(type_ == Type::kObject);
  return object_[std::move(key)];
}
  
bool operator==(const Object& left, const Object& right) {
  return left.value_ == right.value_;
}

bool operator!=(const Object& left, const Object& right) {
  return !(left.value_ == right.value_);
}

bool operator>(const Object& left, const Object& right) {
  return left.value_ > right.value_;
}

bool operator<(const Object& left, const Object& right) {
  return left.value_ < right.value_;
}

bool operator>=(const Object& left, const Object& right) {
  return !(left.value_ < right.value_);
}

bool operator<=(const Object& left, const Object& right) {
  return !(left.value_ > right.value_);
}

bool operator==(const Array& left, const Array& right) {
  return left.value_ == right.value_;
}

bool operator!=(const Array& left, const Array& right) {
  return !(left == right);
}

bool operator>(const Array& left, const Array& right) {
  return left > right;
}

bool operator<(const Array& left, const Array& right) {
  return left < right;
}

bool operator>=(const Array& left, const Array& right) {
  return !(left < right);
}

bool operator<=(const Array& left, const Array& right) {
  return !(left > right);
}

bool operator==(const Value& left, const Value& right) {
  if (left.type_ != right.type_ && (!left.IsNumeric() || !right.IsNumeric()))
    return false;

  switch (left.type_) {
  case Value::Type::kBool:
    return left.bool_ == right.bool_;
  case Value::Type::kInteger:
    if (right.type_ == Value::Type::kDouble) {
      return (static_cast<double>(left.integer_) - right.double_) < 1e-8;
    } else if (right.type_ == Value::Type::kInteger) {
      return left.integer_ == right.integer_;
    } else {
      return false;
    }
  case Value::Type::kDouble:
    if (right.type_ == Value::Type::kDouble) {
      return (left.double_ - right.double_) < 1e-8;
    } else if (right.type_ == Value::Type::kInteger) {
      return (left.double_ - static_cast<double>(right.integer_)) < 1e-8;
    } else {
      return false;
    }
  case Value::Type::kString:
    return left.string_ == right.string_;
  case Value::Type::kObject:
    return left.object_ == right.object_;
  case Value::Type::kArray:
    return left.array_ == right.array_;
  default: // NullT or DummyT
    return true;
  }
}

bool operator!=(const Value& left, const Value& right) {
  return !(left == right);
}

bool operator<(const Value& left, const Value& right) {
  if (left.IsIntegral() && right.IsIntegral()) {
    return left.integer_ < right.integer_;
  } else if (left.IsIntegral() && right.IsDouble()) {
    return static_cast<double>(left.integer_) < right.double_;
  } else if (left.IsDouble() && right.IsIntegral()) {
    return left.double_ < static_cast<double>(right.integer_);
  } else if (left.IsDouble() && right.IsDouble()) {
    return left.double_ < right.double_;
  } else if (left.IsString() && right.IsString()) {
    return left.string_ < right.string_;
  } else if (left.IsObject() && right.IsObject()) {
    return left.object_ < right.object_;
  } else if (left.IsArray() && right.IsArray()) {
    return left.array_ < right.array_;
  } else {
    assert(false);
  }
  return false;
}

bool operator>(const Value& left, const Value& right) {
  return right < left;
}

bool operator<=(const Value& left, const Value& right) {
  return !(left > right);
}

bool operator>=(const Value& left, const Value& right) {
  return !(left < right);
}

/**
 * convert a unicode code point to a utf-8 string
 * unicode code point ranges from [U+000000, U+10FFFF],
 * utf-8 has the format:
 * 1. 0xxxxxxx    1 byte, or
 * 2. 110xxxxx 10xxxxxx 2 byte, or
 * 3. 1110xxxx 10xxxxxx 10xxxxxx 3 byte, or
 * 4. 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 4 byte
 * for more details, please refer to http://en.wikipedia.org/wiki/UTF-8
 * @param unicode_code_point the unicode code point
 * @return "" if the unicode_code_point is not a valid code point
 */
static std::string CodePoint2Utf8(int32_t unicode_code_point) {
  std::string result;
  if (unicode_code_point < 0x0 || unicode_code_point > 0x10FFFF) // invalid
    return result;
  
  if (unicode_code_point <= 0x7F) {
    result.reserve(2);
    result.append(1, static_cast<char>(unicode_code_point));
  } else if (unicode_code_point <= 0x7FF) {
    result.reserve(3);
    result.append(1, static_cast<char>(0xC0 | (unicode_code_point >> 6)));
    result.append(1, static_cast<char>(0x80 | (unicode_code_point & 0x3F)));
  } else if (unicode_code_point <= 0xFFFF) {
    result.reserve(4);
    result.append(1, static_cast<char>(0xE0 | (unicode_code_point >> 12)));
    result.append(1, static_cast<char>(0x80 | ((unicode_code_point >> 6) & 0x3F)));
    result.append(1, static_cast<char>(0x80 | (unicode_code_point & 0x3F)));
  } else if (unicode_code_point <= 0x10FFFF) {
    result.reserve(5);
    result.append(1, static_cast<char>(0xF0 | (unicode_code_point >> 18)));
    result.append(1, static_cast<char>(0x80 | ((unicode_code_point >> 12) & 0x3F)));
    result.append(1, static_cast<char>(0x80 | ((unicode_code_point >> 6) & 0x3F)));
    result.append(1, static_cast<char>(0x80 | (unicode_code_point & 0x3F)));
  }
  return result;
}

/**
 * convert a utf-8 string to unicode code point
 * If the first charactor in utf8_str <= 0x7f then it is an ascii charactor,
 * else the utf-8 string occupies more than 1 bytes.
 * @param utf8_str  the string
 * @return the converted unicode code point, -1 if error occured
 * NOTE: after the convertion, 
 * utf8_str will point to the next position right after the utf-8 string
 */
static int32_t Utf82CodePoint(const char*& utf8_str) {
  assert(utf8_str);
  if (static_cast<uint32_t>(*utf8_str) <= 0x7F) // ascii charactor
    return *utf8_str++;

  auto l1 = static_cast<uint32_t>(*utf8_str) & 0xFF;
  auto l2 = static_cast<uint32_t>(*(utf8_str + 1)) & 0xFF;
  auto l2_error = [&utf8_str] (uint32_t l) {
    if (!l) utf8_str++;
    else utf8_str += 2;
    return -1;
  };
  auto l3_error = [&utf8_str] (uint32_t l) {
    if (!l) utf8_str += 2;
    else utf8_str += 3;
    return -1;
  };
  auto l4_error = [&utf8_str] (uint32_t l) {
    if (!l) utf8_str += 3;
    else utf8_str += 4;
    return -1;
  };

  if ((l1 >> 5) == 0x06) { // first byte is 110xxxxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      utf8_str += 2;
      return ((l1 & 0x1F) << 6) | (l2 & 0x3F);
    }
    return l2_error(l2);
  }
  
  if ((l1 >> 4) == 0x0E) { // first is 1110xxxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      auto l3 = static_cast<uint32_t>(*(utf8_str + 2)) & 0xFF;
      if ((l3 >> 6) == 0x02) { // third byte is also 10xxxxxx
        utf8_str += 3;
        return ((l1 & 0x0F) << 12) | ((l2 & 0x3F) << 6) | (l3 & 0x3F);
      }
      return l3_error(l3);
    }
    return l2_error(l2);
  }
  
  if ((l1 >> 3) == 0x01E) { // first is 11110xxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      auto l3 = static_cast<uint32_t>(*(utf8_str + 2)) & 0xFF;
      if ((l3 >> 6) == 0x02) { // third byte is also 10xxxxxx
        auto l4 = static_cast<uint32_t>(*(utf8_str + 3)) & 0xFF;
        if ((l4 >> 6) == 0x02) {
          utf8_str += 4;
          return (((l1 & 0x07) << 18) | 
                  ((l2 & 0x3F) << 12) | 
                  ((l3 & 0x3F) << 6) | 
                  (l4 & 0x3F));
        }
        return l4_error(l4);
      }
      return l3_error(l3);
    }
    return l2_error(l2);
  }
  return -1;
}

bool Parser::Deserialize(const std::string& csonpp_str, Value& value) {
  ParserImpl impl;
  return impl.Deserialize(csonpp_str, value);
}

void Parser::Serialize(const Value& value, std::string& csonpp_str) {
  ParserImpl impl;
  impl.Serialize(value, csonpp_str);
}

Token TokenizerImpl::GetToken() {
  /**
   * The DFA
   * kStart + 'n'(ull)   -> END (null)
   * kStart + 'f'(alse)  -> END (false)
   * kStart + 't'(rue)   -> END (true)
   * kStart + ':'        -> END (:)
   * kStart + ','        -> END (,)
   * kStart + '['        -> END ([)
   * kStart + ']'        -> END (])
   * kStart + '{'        -> END ({)
   * kStart + '}'        -> END (})
   * kStart + '\"'       -> STRING
   * kStart + '-'        -> kNumber1
   * kStart + '[1-9]'    -> kNumber2
   * STRING + '[^"]'    -> STRING
   * STRING + '\"'      -> DONE (String)
   * kNumber1 + '[1-9]' -> kNumber2
   * kNumber1 + '0'     -> kNumber3
   * kNumber2 + '[0-9]' -> kNumber2
   * kNumber2 + '.'     -> kNumber4
   * kNumber2 + '[eE]'  -> kNumber5
   * kNumber2 + '[,}\]]'-> DONE (Integer)
   * kNumber3 + '.'     -> kNumber4
   * kNumber3 + '[,}\]]'-> DONE (Integer)
   * kNumber4 + '[0-9]' -> kNumber4
   * kNumber4 + '[eE]'  -> kNumber5
   * kNumber4 + '[,}\]]'-> DONE (Double)
   * kNumber5 + '[+-]'  -> kNumber6
   * kNumber5 + '[0-9]' -> kNumber7
   * kNumber6 + '[0-9]' -> kNumber7
   * kNumber7 + '[0-9]' -> kNumber7
   * kNumber7 + '[,}\]]'-> DONE (Double)
   */
  enum class DFAState {
    kStart, 
    kString, 
    kNumber1, 
    kNumber2, 
    kNumber3, 
    kNumber4, 
    kNumber5, 
    kNumber6, 
    kNumber7, 
  };

  Token token;
  DFAState state = DFAState::kStart;

  auto error_occured = [&token] {
    token.value_ = "";
    token.type_ = Token::Type::kDummy;
    return token;
  };

  while (true) {
    int c = GetNextChar();
    switch (state) {
    case DFAState::kStart:
      while (isspace(c)) {
        c = GetNextChar();
      }
      switch (c) {
      case ',':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kComma;
        return token;
      case ':':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kColon;
        return token;
      case '{':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kLeftBrace;
        return token;
      case '}':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kRightBrace;
        return token;
      case '[':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kLeftBracket;
        return token;
      case ']':
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kRightBracket;
        return token;
      case 't':
        if (GetNextChar() == 'r' && 
            GetNextChar() == 'u' && 
            GetNextChar() == 'e') {
          token.value_.append("true");
          token.type_ = Token::Type::kTrue;
          return token;
        } else {
          return error_occured();
        }
      case 'f':
        if (GetNextChar() == 'a' && 
            GetNextChar() == 'l' && 
            GetNextChar() == 's' && 
            GetNextChar() == 'e') {
          token.value_.append("false");
          token.type_ = Token::Type::kFalse;
          return token;
        } else {
          return error_occured();
        }
      case 'n':
        if (GetNextChar() == 'u' && 
            GetNextChar() == 'l' && 
            GetNextChar() == 'l') {
          token.value_.append("null");
          token.type_ = Token::Type::kNull;
          return token;
        } else {
          return error_occured();
        }
      case '\"':
        state = DFAState::kString;
        token.type_ = Token::Type::kString;
        break;
      case '-':
        state = DFAState::kNumber1;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kInteger;
        break;
      case '0':
        state = DFAState::kNumber3;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kInteger;
        break;
      case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        state = DFAState::kNumber2;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kInteger;
        break;
      default:
        return error_occured();
      }
      break;
    case DFAState::kString:
      switch (c) {
      case '\"': return token;
      case '\\': {
        int cc = GetNextChar();
        switch (cc) {
        case '\"': token.value_.append(1, '\"'); break;
        case '\\': token.value_.append(1, '\\'); break;
        case 'r':  token.value_.append(1, '\r'); break;
        case 'n':  token.value_.append(1, '\n'); break;
        case 't':  token.value_.append(1, '\t'); break;
        case 'b':  token.value_.append(1, '\b'); break;
        case 'f':  token.value_.append(1, '\f'); break;
        case 'u': {
          // convert unicode escapse charactor
          char32_t code_point = DecodeUnicode();
          if (code_point == 0)
            return error_occured();
          token.value_ += CodePoint2Utf8(code_point);
          break;
        }
        default: return error_occured();
        }
        break;
      }
      case '\0': return error_occured();
      default: token.value_.append(1, static_cast<char>(c)); break;
      }
      break;
    case DFAState::kNumber1:
      if (c == '0') {
        state = DFAState::kNumber3;
        token.value_.append(1, static_cast<char>(c));
      } else if (c >= '1' && c <= '9') {
        state = DFAState::kNumber2;
        token.value_.append(1, static_cast<char>(c));
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber2:
      while (isdigit(c)) {
        token.value_.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == '\0' || c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return token;
      } else if (c == 'e' || c == 'E') {
        state = DFAState::kNumber5;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kDouble;
      } else if (c == '.') {
        state = DFAState::kNumber4;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kDouble;
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber3:
      if (c == '\0' || c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return token;
      } else if (c == 'e' || c == 'E') {
        state = DFAState::kNumber5;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kDouble;
      } else if (c == '.') {
        state = DFAState::kNumber4;
        token.value_.append(1, static_cast<char>(c));
        token.type_ = Token::Type::kDouble;
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber4:
      while (isdigit(c)) {
        token.value_.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == '\0' || c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return token;
      } else if (c == 'e' || c == 'E') {
        token.value_.append(1, static_cast<char>(c));
        state = DFAState::kNumber5;
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber5:
      if (isdigit(c)) {
        token.value_.append(1, static_cast<char>(c));
        state = DFAState::kNumber7;
      } else if (c == '+' || c == '-') {
        token.value_.append(1, static_cast<char>(c));
        state = DFAState::kNumber6;
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber6:
      if (isdigit(c)) {
        token.value_.append(1, static_cast<char>(c));
        state = DFAState::kNumber7;
      } else {
        return error_occured();
      }
      break;
    case DFAState::kNumber7:
      while (isdigit(c)) {
        token.value_.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == '\0' || c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return token;
      } else {
        return error_occured();
      }
      break;
    }
  }
  return error_occured();
}

int32_t TokenizerImpl::DecodeUnicode() {
  auto hex_char_2_int = [] (char ch) -> int {
    if (ch >= '0' && ch <= '9') return ch - '0';
    else if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    else if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    return -1;
  };
  auto get_four_hex_digit = [this, hex_char_2_int] (int& code1,
                                                    int& code2,
                                                    int& code3,
                                                    int& code4) -> bool {
    code1 = hex_char_2_int(static_cast<char>(GetNextChar()));
    if (code1 < 0) return false;
    code2 = hex_char_2_int(static_cast<char>(GetNextChar()));
    if (code2 < 0) return false;
    code3 = hex_char_2_int(static_cast<char>(GetNextChar()));
    if (code3 < 0) return false;
    code4 = hex_char_2_int(static_cast<char>(GetNextChar()));
    if (code4 < 0) return false;
    return true;
  };

  int code1, code2, code3, code4;
  if (!get_four_hex_digit(code1, code2, code3, code4))
    return 0;
  auto code_point1 = (code1 << 12) + (code2 << 8) + (code3 << 4) + code4;
  if (code_point1 >= 0xD800 && code_point1 <= 0xDBFF) {
    // surrogate pair
    if (GetNextChar() != '\\' || GetNextChar() != 'u')
      return 0;

    int code5, code6, code7, code8;
    if (!get_four_hex_digit(code5, code6, code7, code8))
      return 0;
    auto code_point2 = (code5 << 12) + (code6 << 8) + (code7 << 4) + code8;
    if (code_point2 < 0xDC00 && code_point2 > 0xDFFF)
      return 0;
    code_point1 = 0x10000 + ((code_point1 & 0x3ff) << 10) + (code_point2 & 0x3ff);
  } else if (code_point1 >= 0xDC00 && code_point1 <= 0xDFFF) {
    return 0;
  }
  return code_point1;
}

void ParserImpl::Serialize(const Value& value, 
                           std::string& csonpp_str) const {
  switch (value.GetType()) {
  case Value::Type::kNull:
    csonpp_str = "null";
    break;
  case Value::Type::kBool:
    csonpp_str = value.AsBool() ? "true" : "false";
    break;
  case Value::Type::kInteger:
    csonpp_str = Number2Str<int64_t>(value.GetInteger());
    break;
  case Value::Type::kDouble:
    csonpp_str = Number2Str<double>(value.GetDouble());
    break;
  case Value::Type::kString:
    csonpp_str.append(SerializeString(value.GetString()));
    break;
  case Value::Type::kObject:
    csonpp_str = SerializeObject(value);
    break;
  case Value::Type::kArray:
    csonpp_str = SerializeArray(value);
    break;
  default:
    csonpp_str = "";
    break;
  }
}

std::string ParserImpl::SerializeObject(const Value& value) const {
  std::string result("{");
  const auto& object = value.GetObject();
  int size = value.Size();
  auto cur = 0;
  for (auto const_itr = object.Begin(); 
       const_itr != object.End(); 
       ++const_itr, ++cur) {
    result.append(SerializeString(const_itr->first));
    result.append(1, ':');
    std::string sub_str;
    Serialize(const_itr->second, sub_str);
    result.append(sub_str);
    if (cur != size - 1)
      result.append(1, ',');
  }
  result.append(1, '}');
  return result;
}

std::string ParserImpl::SerializeArray(const Value& value) const {
  std::string result("[");
  const auto& array = value.AsArray();
  int size = array.Size();
  for (auto i = 0; i < size; ++i) {
    std::string sub_str;
    Serialize(array[i], sub_str);
    result.append(sub_str);
    if (i != size - 1)
      result.append(1, ',');
  }
  result.append(1, ']');
  return result;
}

std::string ParserImpl::SerializeString(const std::string& utf8_str) const {
  auto int_2_hex_char = [] (int integer) -> char {
    if (integer >= 0 && integer < 10) return integer + '0';
    else if (integer >= 10 && integer < 16) return integer - 10 + 'A';
    return 0;                                                                   
  };

  std::string result("\"");
  result.reserve(utf8_str.size() * 2);
  const char* ch = utf8_str.c_str();
  while (*ch) {
    int32_t code_point = Utf82CodePoint(ch);
    if (code_point < 0) {
      result.clear();
      return result;
    }

    if (code_point > 0x7F) {
      if (code_point <= 0xFFFF) { // in Basic Multilingual Plane
        result.append("\\u");
        result.append(1, int_2_hex_char(code_point >> 12));
        result.append(1, int_2_hex_char((code_point >> 8) & 0xF));
        result.append(1, int_2_hex_char((code_point >> 4) & 0xF));
        result.append(1, int_2_hex_char(code_point & 0xF));
      } else { // in Supplementary Planes
        code_point -= 0x10000;
        assert(code_point <= 0xFFFFF);
        int32_t lead_surrogate = 0xD800 + ((code_point >> 10) & 0x3FF);
        int32_t trail_surrogate = 0xDC00 + (code_point & 0x3FF);
        result.append("\\u");
        result.append(1, int_2_hex_char(lead_surrogate >> 12));
        result.append(1, int_2_hex_char((lead_surrogate >> 8) & 0xF));
        result.append(1, int_2_hex_char((lead_surrogate >> 4) & 0xF));
        result.append(1, int_2_hex_char(lead_surrogate & 0xF));
        result.append("\\u");
        result.append(1, int_2_hex_char(trail_surrogate >> 12));
        result.append(1, int_2_hex_char((trail_surrogate >> 8) & 0xF));
        result.append(1, int_2_hex_char((trail_surrogate >> 4) & 0xF));
        result.append(1, int_2_hex_char(trail_surrogate & 0xF));
      }
    } else if (code_point <= 0x1F) { // control charactor
      switch (code_point) {
      case '\b': result.append("\\b"); break;
      case '\f': result.append("\\f"); break;
      case '\n': result.append("\\n"); break;
      case '\r': result.append("\\r"); break;
      case '\t': result.append("\\t"); break;
      default:
        result.append("\\u00");
        result.append(1, int_2_hex_char((code_point >> 4) & 0xf));
        result.append(1, int_2_hex_char(code_point & 0xf));
        break;
      }
    } else if (code_point == '\\' || code_point == '\"') {
      result.append(1, '\\');
      result.append(1, code_point);
    } else {
      result.append(1, code_point);
    }
  }
  result.append(1, '\"');
  return result;
}

bool ParserImpl::Deserialize(const std::string& csonpp_str, Value& value) {
  tokenizer_ = std::make_shared<TokenizerImpl>(&csonpp_str);

  auto error_occured = [&value, this] {
    value = Value();
    tokenizer_->Reset();
    return false;
  };

  if (csonpp_str.empty())
    return error_occured();

  if (!ParseValue(value))
    return error_occured();
  return true;
}

bool ParserImpl::ParseValue(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };

  Token token = tokenizer_->GetToken();
  switch (token.type_) {
  case Token::Type::kLeftBrace:
    return ParseObject(value);
  case Token::Type::kLeftBracket:
    return ParseArray(value);
  case Token::Type::kString:
    value = Value(token.value_);
    return true;
  case Token::Type::kInteger: {
    bool valid = false;
    int64_t integer = Str2Number<int64_t>(token.value_, &valid);
    if (!valid)
      return error_occured();
    value = Value(integer);
    return true;
  }
  case Token::Type::kDouble: {
    bool valid = false;
    double num = Str2Number<double>(token.value_, &valid);
    if (!valid)
      return error_occured();
    value = Value(num);
    return true;
  }
  case Token::Type::kTrue:
    value = Value(true);
    return true;
  case Token::Type::kFalse:
    value = Value(false);
    return true;
  case Token::Type::kNull:
    value = Value(nullptr);
    return true;
  default:
    return error_occured();
  }
}

bool ParserImpl::ParseObject(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };
  value = Value(Value::Type::kObject);
  if (!ParseMembers(value)) {
    tokenizer_->UngetNextChar();
    auto token = tokenizer_->GetToken();
    if (token.type_ != Token::Type::kRightBrace)
      return error_occured();
    value = Value(Value::Type::kObject);
  }
  return true;
}

bool ParserImpl::ParseMembers(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };
  if (!ParsePair(value))
    return error_occured();
  auto token = tokenizer_->GetToken();
  if (token.type_ == Token::Type::kComma) {
    return ParseMembers(value);
  } else if (token.type_ == Token::Type::kRightBrace) {
    return true;
  } else {
    return error_occured();
  }
}

bool ParserImpl::ParsePair(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };
  auto token = tokenizer_->GetToken();
  if (token.type_ != Token::Type::kString)
    return error_occured();

  auto next_token = tokenizer_->GetToken();
  if (next_token.type_ != Token::Type::kColon)
    return error_occured();

  Value sub_value;
  if (!ParseValue(sub_value))
    return error_occured();
  value[token.value_] = sub_value;
  return true;
}

bool ParserImpl::ParseArray(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };
  value = Value(Value::Type::kArray);
  if (!ParseElements(value)) {
    tokenizer_->UngetNextChar();
    auto next_token = tokenizer_->GetToken();
    if (next_token.type_ != Token::Type::kRightBracket)
      return error_occured();
    value = Value(Value::Type::kArray);
  }
  return true;
}

bool ParserImpl::ParseElements(Value& value) {
  auto error_occured = [&value] {
    value = Value();
    return false;
  };
  Value sub_value;
  if (!ParseValue(sub_value))
    return error_occured();
  value.Append(std::move(sub_value));
  auto next_token = tokenizer_->GetToken();
  if (next_token.type_ == Token::Type::kRightBracket) {
    return true;
  } else if (next_token.type_ == Token::Type::kComma) {
    return ParseElements(value);
  }
  return error_occured();
}

}  // namespace csonpp

