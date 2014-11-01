#include "CsonppImpl.h"

#include <assert.h>
#include <algorithm>

START_CSONPP_NS

Object::Object(const Object& irOther) 
  : mValue(irOther.mValue) {
}

Object::Object(Object&& irrOther) 
: mValue(std::move(irrOther.mValue)) {
}

Object& Object::operator=(const Object& irOther) {
  if (this != &irOther)
    mValue = irOther.mValue;
  return *this;
}

Object& Object::operator=(const Object&& irrOther) {
  if (this != &irrOther)
    mValue = std::move(irrOther.mValue);
  return *this;
}

Value& Object::operator[](const std::string& irKey) {
  return mValue[irKey];
}

Value& Object::operator[](std::string&& irrKey) {
  return mValue[std::move(irrKey)];
}

Object::ConstIterator Object::CBegin() const {
  return mValue.cbegin();
}

Object::ConstIterator Object::CEnd() const {
  return mValue.cend();
}

Object::ConstIterator Object::Begin() const {
  return mValue.begin();
}

Object::ConstIterator Object::End() const {
  return mValue.end();
}

Object::Iterator Object::Begin() {
  return mValue.begin();
}

Object::Iterator Object::End() {
  return mValue.end();
}

Object::Iterator Object::Find(const std::string& irKey) {
  return mValue.find(irKey);
}

Object::ConstIterator Object::Find(const std::string& irKey) const {
  return mValue.find(irKey);
}

void Object::Clear() {
  mValue.clear();
}
size_t Object::Size() const {
  return mValue.size();
}

Array::Array(const Array& irArray) 
: mValue(irArray.mValue) {
}

Array::Array(Array&& irrArray) 
: mValue(std::move(irrArray.mValue)) {
}

Array& Array::operator=(const Array& irArray) {
  if (this != &irArray)
    mValue = irArray.mValue;
  return *this;
}

Array& Array::operator=(Array&& irrArray) {
  if (this != &irrArray)
    mValue = std::move(irrArray.mValue);
  return *this;
}

// the element must exist
Value& Array::operator[](size_t iIndex) {
  assert(iIndex < mValue.size());
  return mValue[iIndex];
}

// the element must exist
const Value& Array::operator[](size_t iIndex) const {
  assert(iIndex < mValue.size());
  return mValue[iIndex];
}

void Array::Append(const Value& irValue) {
  mValue.push_back(irValue);
}

void Array::Append(Value&& irrValue) {
  mValue.push_back(std::move(irrValue));
}

Array::ConstIterator Array::CBegin() const {
  return mValue.cbegin();
}

Array::ConstIterator Array::CEnd() const {
  return mValue.cend();
}

Array::ConstIterator Array::Begin() const {
  return mValue.begin();
}

Array::ConstIterator Array::End() const {
  return mValue.end();
}

Array::Iterator Array::Begin() {
  return mValue.begin();
}

Array::Iterator Array::End() {
  return mValue.end();
}

Array::Iterator Array::Find(const Value& irValue) {
  return std::find(Begin(), End(), irValue);
}

Array::ConstIterator Array::Find(const Value& irValue) const {
  return std::find(Begin(), End(), irValue);
}

void Array::Clear() {
  mValue.clear();
}

size_t Array::Size() const {
  return mValue.size();
}

Value::Value(ValueType iType) 
: mType(iType) {
}

Value::Value(std::nullptr_t iNull) 
: mType(ValueType::NULL_T) {
}

Value::Value(bool iValue) 
: mType(ValueType::BOOL_T), 
  mBool(iValue) {
}

Value::Value(int8_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(uint8_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(int16_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(uint16_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(int32_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(uint32_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(static_cast<int64_t>(iValue)) {
}

Value::Value(int64_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(iValue) {
}

// TODO
// do not support uint64_t
#if 0
Value::Value(uint64_t iValue) 
: mType(ValueType::INTEGER_T), 
  mInteger(iValue) {
}
#endif

Value::Value(float iValue) 
: mType(ValueType::DOUBLE_T), 
  mDouble(static_cast<double>(iValue)) {
}

Value::Value(double iValue) 
: mType(ValueType::DOUBLE_T), 
  mDouble(iValue) {
}

Value::Value(const std::string& irValue) 
: mType(ValueType::STRING_T), 
  mString(irValue) {
}

Value::Value(std::string&& irrValue) 
: mType(ValueType::STRING_T), 
  mString(std::move(irrValue)) {
}

Value::Value(const Object& irValue) 
: mType(ValueType::OBJECT_T), 
  mObject(irValue) {
}

Value::Value(Object&& irrValue) 
: mType(ValueType::OBJECT_T), 
  mObject(std::move(irrValue)) {
}

Value::Value(const Array& irValue) 
: mType(ValueType::ARRAY_T), 
  mArray(irValue) {
}

Value::Value(Array&& irrValue) 
: mType(ValueType::ARRAY_T), 
  mArray(std::move(irrValue)) {
}

Value::Value(const Value& irValue) 
: mType(irValue.mType) {
  switch(mType) {
  case ValueType::BOOL_T:
    mBool = irValue.mBool;
    break;
  case ValueType::INTEGER_T:
    mInteger = irValue.mInteger;
    break;
  case ValueType::DOUBLE_T:
    mDouble = irValue.mDouble;
    break;
  case ValueType::STRING_T:
    mString = irValue.mString;
    break;
  case ValueType::OBJECT_T:
    mObject = irValue.mObject;
    break;
  case ValueType::ARRAY_T:
    mArray = irValue.mArray;
    break;
  default:
    break;
  }
}

Value::Value(Value&& irrValue) 
: mType(irrValue.mType) {
  switch(mType) {
  case ValueType::BOOL_T:
    mBool = irrValue.mBool;
    break;
  case ValueType::INTEGER_T:
    mInteger = irrValue.mInteger;
    break;
  case ValueType::DOUBLE_T:
    mDouble = irrValue.mDouble;
    break;
  case ValueType::STRING_T:
    mString = std::move(irrValue.mString);
    break;
  case ValueType::OBJECT_T:
    mObject = std::move(irrValue.mObject);
    break;
  case ValueType::ARRAY_T:
    mArray = std::move(irrValue.mArray);
    break;
  default:
    break;
  }
}

Value& Value::operator=(const Value& irValue) {
  if (&irValue != this) {
    mType = irValue.mType;
    switch(mType) {
    case ValueType::BOOL_T:
      mBool = irValue.mBool;
      break;
    case ValueType::INTEGER_T:
      mInteger = irValue.mInteger;
      break;
    case ValueType::DOUBLE_T:
      mDouble = irValue.mDouble;
      break;
    case ValueType::STRING_T:
      mString = irValue.mString;
      break;
    case ValueType::OBJECT_T:
      mObject = irValue.mObject;
      break;
    case ValueType::ARRAY_T:
      mArray = irValue.mArray;
      break;
    default:
      break;
    }
  }

  return *this;
}

Value& Value::operator=(Value&& irrValue) {
  if (&irrValue != this) {
    mType = irrValue.mType;
    switch(mType) {
    case ValueType::BOOL_T:
      mBool = irrValue.mBool;
      break;
    case ValueType::INTEGER_T:
      mInteger = irrValue.mInteger;
      break;
    case ValueType::DOUBLE_T:
      mDouble = irrValue.mDouble;
      break;
    case ValueType::STRING_T:
      mString = std::move(irrValue.mString);
      break;
    case ValueType::OBJECT_T:
      mObject = std::move(irrValue.mObject);
      break;
    case ValueType::ARRAY_T:
      mArray = std::move(irrValue.mArray);
      break;
    default:
      break;
    }
  }

  return *this;
}

Value& Value::operator=(bool irBool) {
  mType = ValueType::BOOL_T;
  mBool = irBool;
  return *this;
}

Value& Value::operator=(int8_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(uint8_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(int16_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(uint16_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(int32_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(uint32_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = static_cast<int64_t>(irInt);
  return *this;
}

Value& Value::operator=(int64_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = irInt;
  return *this;
}

// TODO
// do not support uint64_t
#if 0
Value& Value::operator=(uint64_t irInt) {
  mType = ValueType::INTEGER_T;
  mInteger = irInt;
  return *this;
}
#endif

Value& Value::operator=(float irDouble) {
  mType = ValueType::DOUBLE_T;
  mDouble = static_cast<double>(irDouble);
  return *this;
}

Value& Value::operator=(double irDouble) {
  mType = ValueType::DOUBLE_T;
  mDouble = irDouble;
  return *this;
}

Value& Value::operator=(const std::string& irString) {
  mType = ValueType::STRING_T;
  mString = irString;
  return *this;
}

Value& Value::operator=(std::string&& irrString) {
  mType = ValueType::STRING_T;
  mString = std::move(irrString);
  return *this;
}

Value& Value::operator=(const Object& irObject) {
  mType = ValueType::OBJECT_T;
  mObject = irObject;
  return *this;
}

Value& Value::operator=(Object&& irrObject) {
  mType = ValueType::OBJECT_T;
  mObject = std::move(irrObject);
  return *this;
}

Value& Value::operator=(const Array& irArray) {
  mType = ValueType::ARRAY_T;
  mArray = irArray;
  return *this;
}

Value& Value::operator=(Array&& irrArray) {
  mType = ValueType::ARRAY_T;
  mArray = std::move(irrArray);
  return *this;
}

void Value::Append(const Value& irValue) {
  assert(mType == ValueType::ARRAY_T);
  mArray.Append(irValue);
}

void Value::Append(Value&& irrValue) {
  assert(mType == ValueType::ARRAY_T);
  mArray.Append(std::move(irrValue));
}

void Value::Append(const std::string& irKey, bool iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, bool iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, int8_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, int8_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, uint8_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, uint8_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, int16_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, uint16_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, int32_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, int32_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, uint32_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, uint32_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, int64_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, int64_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

// TODO
// do not support uint64_t
#if 0
void Value::Append(const std::string& irKey, uint64_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, uint64_t iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}
#endif

void Value::Append(const std::string& irKey, float iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, float iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, double iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = iValue;
}

void Value::Append(std::string&& irrKey, double iValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = iValue;
}

void Value::Append(const std::string& irKey, const std::string& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = irValue;
}

void Value::Append(std::string&& irrKey, const std::string& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = irValue;
}

void Value::Append(const std::string& irKey, std::string&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = std::move(irrValue);
}

void Value::Append(std::string&& irrKey, std::string&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = std::move(irrValue);
}

void Value::Append(const std::string& irKey, const Object& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = irValue;
}

void Value::Append(std::string&& irrKey, const Object& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = irValue;
}

void Value::Append(const std::string& irKey, Object&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = std::move(irrValue);
}

void Value::Append(std::string&& irrKey, Object&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = std::move(irrValue);
}

void Value::Append(const std::string& irKey, const Array& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = irValue;
}

void Value::Append(std::string&& irrKey, const Array& irValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = irValue;
}

void Value::Append(const std::string& irKey, Array&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[irKey] = std::move(irrValue);
}

void Value::Append(std::string&& irrKey, Array&& irrValue) {
  assert(mType == ValueType::OBJECT_T);
  mObject[std::move(irrKey)] = std::move(irrValue);
}

Value::ValueType Value::Type() const {
  return mType;
}

size_t Value::Size() const {
  assert(mType == ValueType::OBJECT_T || mType == ValueType::ARRAY_T);
  return (mType == ValueType::OBJECT_T) ? mObject.Size() : mArray.Size();
}

void Value::Clear() {
  switch (mType) {
  case ValueType::ARRAY_T:
    mArray.Clear();
    return;
  case ValueType::OBJECT_T:
    mObject.Clear();
    return;
  default:
    assert(false);
    return;
  }
}

bool Value::IsNumeric() const {
  return (mType == ValueType::DOUBLE_T || mType == ValueType::INTEGER_T);
}

bool Value::IsIntegral() const {
  return mType == ValueType::INTEGER_T;
}

bool Value::IsDouble() const {
  return mType == ValueType::DOUBLE_T;
}

bool Value::IsBool() const {
  return mType == ValueType::BOOL_T;
}

bool Value::IsString() const {
  return mType == ValueType::STRING_T;
}

bool Value::IsObject() const {
  return mType == ValueType::OBJECT_T;
}

bool Value::IsArray() const {
  return mType == ValueType::ARRAY_T;
}

int64_t Value::AsInteger() const {
  if (mType == ValueType::INTEGER_T) {
    return mInteger;
  } else if (mType == ValueType::DOUBLE_T) {
    return static_cast<int64_t>(mDouble);
  } else {
    assert(false);
  }
}

double Value::AsDouble() const {
  if (mType == ValueType::INTEGER_T) {
    return static_cast<double>(mInteger);
  } else if (mType == ValueType::DOUBLE_T) {
    return mDouble;
  } else {
    assert(false);
  }
}

bool Value::AsBool() const {
  assert(mType == ValueType::BOOL_T);
  return mBool;
}

std::string Value::AsString() const {
  assert(mType == ValueType::STRING_T);
  return mString;
}

Object Value::AsObject() const {
  assert(mType == ValueType::OBJECT_T);
  return mObject;
}

Array Value::AsArray() const {
  assert(mType == ValueType::ARRAY_T);
  return mArray;
}

const int64_t& Value::GetInteger() const {
  assert(mType == ValueType::INTEGER_T);
  return mInteger;
}

const double& Value::GetDouble() const {
  assert(mType == ValueType::DOUBLE_T);
  return mDouble;
}

const bool& Value::GetBool() const {
  assert(mType == ValueType::BOOL_T);
  return mBool;
}

const std::string& Value::GetString() const {
  assert(mType == ValueType::STRING_T);
  return mString;
}

const Object& Value::GetObject() const {
  assert(mType == ValueType::OBJECT_T);
  return mObject;
}

const Array& Value::GetArray() const {
  assert(mType == ValueType::ARRAY_T);
  return mArray;
}

Value& Value::operator[](size_t iIndex) {
  assert(mType == ValueType::ARRAY_T);
  assert(iIndex < mArray.Size());
  return mArray[iIndex];
}

const Value& Value::operator[](size_t iIndex) const {
  assert(mType == ValueType::ARRAY_T);
  assert(iIndex < mArray.Size());
  return mArray[iIndex];
}

Value& Value::operator[](const std::string& irKey) {
  assert(mType == ValueType::OBJECT_T);
  return mObject[irKey];
}

Value& Value::operator[](std::string&& irrKey) {
  assert(mType == ValueType::OBJECT_T);
  return mObject[std::move(irrKey)];
}
  
bool operator==(const Object& irL, const Object& irR) {
  return irL.mValue == irR.mValue;
}

bool operator!=(const Object& irL, const Object& irR) {
  return !(irL.mValue == irR.mValue);
}

bool operator>(const Object& irL, const Object& irR) {
  return irL.mValue > irR.mValue;
}

bool operator<(const Object& irL, const Object& irR) {
  return irL.mValue < irR.mValue;
}

bool operator>=(const Object& irL, const Object& irR) {
  return !(irL.mValue < irR.mValue);
}

bool operator<=(const Object& irL, const Object& irR) {
  return !(irL.mValue > irR.mValue);
}

bool operator==(const Array& irL, const Array& irR) {
  return irL.mValue == irR.mValue;
}

bool operator!=(const Array& irL, const Array& irR) {
  return !(irL == irR);
}

bool operator>(const Array& irL, const Array& irR) {
  return irL > irR;
}

bool operator<(const Array& irL, const Array& irR) {
  return irL < irR;
}

bool operator>=(const Array& irL, const Array& irR) {
  return !(irL < irR);
}

bool operator<=(const Array& irL, const Array& irR) {
  return !(irL > irR);
}

bool operator==(const Value& irL, const Value& irR) {
  if (irL.mType != irR.mType && (!irL.IsNumeric() || !irR.IsNumeric()))
    return false;

  switch (irL.mType) {
  case Value::ValueType::BOOL_T:
    return irL.mBool == irR.mBool;
  case Value::ValueType::INTEGER_T:
    if (irR.mType == Value::ValueType::DOUBLE_T) {
      return (static_cast<double>(irL.mInteger) - irR.mDouble) < 1e-8;
    } else if (irR.mType == Value::ValueType::INTEGER_T) {
      return irL.mInteger == irR.mInteger;
    } else {
      return false;
    }
  case Value::ValueType::DOUBLE_T:
    if (irR.mType == Value::ValueType::DOUBLE_T) {
      return (irL.mDouble - irR.mDouble) < 1e-8;
    } else if (irR.mType == Value::ValueType::INTEGER_T) {
      return (irL.mDouble - static_cast<double>(irR.mInteger)) < 1e-8;
    } else {
      return false;
    }
  case Value::ValueType::STRING_T:
    return irL.mString == irR.mString;
  case Value::ValueType::OBJECT_T:
    return irL.mObject == irR.mObject;
  case Value::ValueType::ARRAY_T:
    return irL.mArray == irR.mArray;
  default: // NullT or DummyT
    return true;
  }
}

bool operator!=(const Value& irL, const Value& irR) {
  return !(irL == irR);
}

bool operator<(const Value& irL, const Value& irR) {
  if (irL.IsIntegral() && irR.IsIntegral()) {
    return irL.mInteger < irR.mInteger;
  } else if (irL.IsIntegral() && irR.IsDouble()) {
    return static_cast<double>(irL.mInteger) < irR.mDouble;
  } else if (irL.IsDouble() && irR.IsIntegral()) {
    return irL.mDouble < static_cast<double>(irR.mInteger);
  } else if (irL.IsDouble() && irR.IsDouble()) {
    return irL.mDouble < irR.mDouble;
  } else if (irL.IsString() && irR.IsString()) {
    return irL.mString < irR.mString;
  } else if (irL.IsObject() && irR.IsObject()) {
    return irL.mObject < irR.mObject;
  } else if (irL.IsArray() && irR.IsArray()) {
    return irL.mArray < irR.mArray;
  } else {
    assert(false);
  }
  return false;
}

bool operator>(const Value& irL, const Value& irR) {
  return irR < irL;
}

bool operator<=(const Value& irL, const Value& irR) {
  return !(irL > irR);
}

bool operator>=(const Value& irL, const Value& irR) {
  return !(irL < irR);
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
 * @param iUnicodeCodePoint the unicode code point
 * @return "" if the iUnicodeCodePoint is not a valid codepoint
 */
static std::string CodePoint2Utf8(int32_t iUnicodeCodePoint) {
  std::string lResult;
  if (iUnicodeCodePoint < 0x0 || iUnicodeCodePoint > 0x10FFFF) // invalid
    return lResult;
  
  if (iUnicodeCodePoint <= 0x7F) {
    lResult.resize(1);
    lResult.append(1, static_cast<char>(iUnicodeCodePoint));
  } else if (iUnicodeCodePoint <= 0x7FF) {
    lResult.resize(2);
    lResult.append(1, static_cast<char>(0xC0 | (iUnicodeCodePoint >> 6)));
    lResult.append(1, static_cast<char>(0x80 | (iUnicodeCodePoint & 0x3F)));
  } else if (iUnicodeCodePoint <= 0xFFFF) {
    lResult.resize(3);
    lResult.append(1, static_cast<char>(0xE0 | (iUnicodeCodePoint >> 12)));
    lResult.append(1, static_cast<char>(0x80 | ((iUnicodeCodePoint >> 6) & 0x3F)));
    lResult.append(1, static_cast<char>(0x80 | (iUnicodeCodePoint & 0x3F)));
  } else if (iUnicodeCodePoint <= 0x10FFFF) {
    lResult.resize(4);
    lResult.append(1, static_cast<char>(0xF0 | (iUnicodeCodePoint >> 18)));
    lResult.append(1, static_cast<char>(0x80 | ((iUnicodeCodePoint >> 12) & 0x3F)));
    lResult.append(1, static_cast<char>(0x80 | ((iUnicodeCodePoint >> 6) & 0x3F)));
    lResult.append(1, static_cast<char>(0x80 | (iUnicodeCodePoint & 0x3F)));
  }
  return lResult;
}

/**
 * convert a utf-8 string to unicode code point
 * If the first charactor in ipUtf8String <= 0x7f then it is an ascii charactor,
 * else the utf-8 string occupies more than 1 bytes.
 * @param ipUtf8String  the string
 * @return the converted unicode code point, -1 if error occured
 * NOTE: after the convertion, 
 * ipUtf8String will point to the next position right after the utf-8 string
 */
static int32_t Utf82CodePoint(const char*& ipUtf8String) {
  assert(ipUtf8String);
  if (static_cast<uint32_t>(*ipUtf8String) <= 0x7F) // ascii charactor
    return *ipUtf8String++;

  auto l1 = static_cast<uint32_t>(*ipUtf8String) & 0xFF;
  auto l2 = static_cast<uint32_t>(*(ipUtf8String + 1)) & 0xFF;
  auto lL2Error = [&ipUtf8String] (uint32_t iL2) {
    if (!iL2) ipUtf8String++;
    else ipUtf8String += 2;
    return -1;
  };
  auto lL3Error = [&ipUtf8String] (uint32_t iL3) {
    if (!iL3) ipUtf8String += 2;
    else ipUtf8String += 3;
    return -1;
  };
  auto lL4Error = [&ipUtf8String] (uint32_t iL4) {
    if (!iL4) ipUtf8String += 3;
    else ipUtf8String += 4;
    return -1;
  };

  if ((l1 >> 5) == 0x06) { // first byte is 110xxxxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      ipUtf8String += 2;
      return ((l1 & 0x1F) << 6) | (l2 & 0x3F);
    }
    return lL2Error(l2);
  }
  
  if ((l1 >> 4) == 0x0E) { // first is 1110xxxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      auto l3 = static_cast<uint32_t>(*(ipUtf8String + 2)) & 0xFF;
      if ((l3 >> 6) == 0x02) { // third byte is also 10xxxxxx
        ipUtf8String += 3;
        return ((l1 & 0x0F) << 12) | ((l2 & 0x3F) << 6) | (l3 & 0x3F);
      }
      return lL3Error(l3);
    }
    return lL2Error(l2);
  }
  
  if ((l1 >> 3) == 0x01E) { // first is 11110xxx
    if ((l2 >> 6) == 0x02) { // second byte is 10xxxxxx
      auto l3 = static_cast<uint32_t>(*(ipUtf8String + 2)) & 0xFF;
      if ((l3 >> 6) == 0x02) { // third byte is also 10xxxxxx
        auto l4 = static_cast<uint32_t>(*(ipUtf8String + 3)) & 0xFF;
        if ((l4 >> 6) == 0x02) {
          ipUtf8String += 4;
          return (((l1 & 0x07) << 18) | 
                  ((l2 & 0x3F) << 12) | 
                  ((l3 & 0x3F) << 6) | 
                  (l4 & 0x3F));
        }
        return lL4Error(l4);
      }
      return lL3Error(l3);
    }
    return lL2Error(l2);
  }
  return -1;
}

bool Parser::Deserialize(const std::string& irCsonppString, Value& orValue) {
  ParserImpl lImpl;
  return lImpl.Deserialize(irCsonppString, orValue);
}

void Parser::Serialize(const Value& irValue, std::string& orCsonppString) {
  ParserImpl lImpl;
  lImpl.Serialize(irValue, orCsonppString);
}

Token TokenizerImpl::GetToken() {
  /**
   * The DFA
   * START + 'n'(ull)   -> END (null)
   * START + 'f'(alse)  -> END (false)
   * START + 't'(rue)   -> END (true)
   * START + ':'        -> END (:)
   * START + ','        -> END (,)
   * START + '['        -> END ([)
   * START + ']'        -> END (])
   * START + '{'        -> END ({)
   * START + '}'        -> END (})
   * START + '\"'       -> STRING
   * START + '-'        -> NUMBER_1
   * START + '[1-9]'    -> NUMBER_2
   * STRING + '[^"]'    -> STRING
   * STRING + '\"'      -> DONE (String)
   * NUMBER_1 + '[1-9]' -> NUMBER_2
   * NUMBER_1 + '0'     -> NUMBER_3
   * NUMBER_2 + '[0-9]' -> NUMBER_2
   * NUMBER_2 + '.'     -> NUMBER_4
   * NUMBER_2 + '[eE]'  -> NUMBER_5
   * NUMBER_2 + '[,}\]]'-> DONE (Integer)
   * NUMBER_3 + '.'     -> NUMBER_4
   * NUMBER_3 + '[,}\]]'-> DONE (Integer)
   * NUMBER_4 + '[0-9]' -> NUMBER_4
   * NUMBER_4 + '[eE]'  -> NUMBER_5
   * NUMBER_4 + '[,}\]]'-> DONE (Double)
   * NUMBER_5 + '[+-]'  -> NUMBER_6
   * NUMBER_5 + '[0-9]' -> NUMBER_7
   * NUMBER_6 + '[0-9]' -> NUMBER_7
   * NUMBER_7 + '[0-9]' -> NUMBER_7
   * NUMBER_7 + '[,}\]]'-> DONE (Double)
   */
  enum class DFAState {
    START, 
    STRING, 
    NUMBER_1, 
    NUMBER_2, 
    NUMBER_3, 
    NUMBER_4, 
    NUMBER_5, 
    NUMBER_6, 
    NUMBER_7, 
  };

  Token lToken;
  DFAState lState = DFAState::START;

  auto lErrorOccured = [&lToken] {
    lToken.mValue = "";
    lToken.mType = Token::Type::DUMMY_T;
    return lToken;
  };

  while (true) {
    int c = GetNextChar();
    switch (lState) {
    case DFAState::START:
      while (isspace(c)) {
        c = GetNextChar();
      }
      switch (c) {
      case ',':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::COMMA_T;
        return lToken;
      case ':':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::COLON_T;
        return lToken;
      case '{':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::LEFT_BRACE_T;
        return lToken;
      case '}':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::RIGHT_BRACE_T;
        return lToken;
      case '[':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::LEFT_BRACKET_T;
        return lToken;
      case ']':
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::RIGHT_BRACKET_T;
        return lToken;
      case 't':
        if (GetNextChar() == 'r' && 
            GetNextChar() == 'u' && 
            GetNextChar() == 'e') {
          lToken.mValue.append("true");
          lToken.mType = Token::Type::TRUE_T;
          return lToken;
        } else {
          return lErrorOccured();
        }
      case 'f':
        if (GetNextChar() == 'a' && 
            GetNextChar() == 'l' && 
            GetNextChar() == 's' && 
            GetNextChar() == 'e') {
          lToken.mValue.append("false");
          lToken.mType = Token::Type::FALSE_T;
          return lToken;
        } else {
          return lErrorOccured();
        }
      case 'n':
        if (GetNextChar() == 'u' && 
            GetNextChar() == 'l' && 
            GetNextChar() == 'l') {
          lToken.mValue.append("null");
          lToken.mType = Token::Type::NULL_T;
          return lToken;
        } else {
          return lErrorOccured();
        }
      case '\"':
        lState = DFAState::STRING;
        lToken.mType = Token::Type::STRING_T;
        break;
      case '-':
        lState = DFAState::NUMBER_1;
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::INTEGER_T;
        break;
      case '0':
        lState = DFAState::NUMBER_3;
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::INTEGER_T;
        break;
      case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8':
        lState = DFAState::NUMBER_2;
        lToken.mValue.append(1, static_cast<char>(c));
        lToken.mType = Token::Type::INTEGER_T;
        break;
      default:
        return lErrorOccured();
      }
      break;
    case DFAState::STRING:
      switch (c) {
      case '\"': return lToken;
      case '\\': {
        int cc = GetNextChar();
        switch (cc) {
        case '\"': lToken.mValue.append(1, '\"'); break;
        case '\\': lToken.mValue.append(1, '\\'); break;
        case 'r':  lToken.mValue.append(1, '\r'); break;
        case 'n':  lToken.mValue.append(1, '\n'); break;
        case 't':  lToken.mValue.append(1, '\t'); break;
        case 'b':  lToken.mValue.append(1, '\b'); break;
        case 'f':  lToken.mValue.append(1, '\f'); break;
        case 'u': {
          // convert unicode escapse charactor
          char32_t lCodePoint = hDecodeUnicode();
          if (lCodePoint == 0)
            return lErrorOccured();
          lToken.mValue += CodePoint2Utf8(lCodePoint);
          break;
        }
        default: return lErrorOccured();
        }
        break;
      }
      case '\0': return lErrorOccured();
      default: lToken.mValue.append(1, static_cast<char>(c)); break;
      }
      break;
    case DFAState::NUMBER_1:
      if (c == '0') {
        lState = DFAState::NUMBER_3;
        lToken.mValue.append(1, static_cast<char>(c));
      } else if (c >= '1' && c <= '9') {
        lState = DFAState::NUMBER_2;
        lToken.mValue.append(1, static_cast<char>(c));
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_2:
      while (isdigit(c)) {
        lToken.mValue.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return lToken;
      } else if (c == 'e' || c == 'E') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_5;
      } else if (c == '.') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_4;
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_3:
      if (c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return lToken;
      } else if (c == 'e' || c == 'E') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_5;
      } else if (c == '.') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_4;
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_4:
      while (isdigit(c)) {
        lToken.mValue.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return lToken;
      } else if (c == 'e' || c == 'E') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_5;
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_5:
      if (isdigit(c)) {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_7;
      } else if (c == '+' || c == '-') {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_6;
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_6:
      if (isdigit(c)) {
        lToken.mValue.append(1, static_cast<char>(c));
        lState = DFAState::NUMBER_7;
      } else {
        return lErrorOccured();
      }
      break;
    case DFAState::NUMBER_7:
      while (isdigit(c)) {
        lToken.mValue.append(1, static_cast<char>(c));
        c = GetNextChar();
      }
      if (c == ',' || c == '}' || c == ']') {
        UngetNextChar();
        return lToken;
      } else {
        return lErrorOccured();
      }
      break;
    }
  }
  return lErrorOccured();
}

int32_t TokenizerImpl::hDecodeUnicode() {
  auto lHexChar2Int = [] (char iChar) -> int {
    if (iChar >= '0' && iChar <= '9') return iChar - '0';
    else if (iChar >= 'a' && iChar <= 'f') return iChar - 'a' + 10;
    else if (iChar >= 'A' && iChar <= 'F') return iChar - 'A' + 10;
    return -1;
  };
  auto lGetFourHexDigit = [this, lHexChar2Int] (int& irCode1, 
                                                int& irCode2, 
                                                int& irCode3, 
                                                int& irCode4) -> bool {
    irCode1 = lHexChar2Int(static_cast<char>(GetNextChar()));
    if (irCode1 < 0) return false;
    irCode2 = lHexChar2Int(static_cast<char>(GetNextChar()));
    if (irCode2 < 0) return false;
    irCode3 = lHexChar2Int(static_cast<char>(GetNextChar()));
    if (irCode3 < 0) return false;
    irCode4 = lHexChar2Int(static_cast<char>(GetNextChar()));
    if (irCode4 < 0) return false;
    return true;
  };

  int lCode1, lCode2, lCode3, lCode4;
  if (!lGetFourHexDigit(lCode1, lCode2, lCode3, lCode4))
    return 0;
  auto lCodePoint1 = (lCode1 << 12) + (lCode2 << 8) + (lCode3 << 4) + lCode4;
  if (lCodePoint1 >= 0xD800 && lCodePoint1 <= 0xDBFF) {
    // surrogate pair
    if (GetNextChar() != '\\' || GetNextChar() != 'u')
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

void ParserImpl::Serialize(const Value& irValue, 
                           std::string& orCsonppString) const {
  switch (irValue.Type()) {
  case Value::ValueType::NULL_T:
    orCsonppString = "null";
    break;
  case Value::ValueType::BOOL_T:
    orCsonppString = irValue.AsBool() ? "true" : "false";
    break;
  case Value::ValueType::INTEGER_T:
    orCsonppString = std::to_string(irValue.GetInteger());
    break;
  case Value::ValueType::DOUBLE_T:
    orCsonppString = std::to_string(irValue.GetDouble());
    break;
  case Value::ValueType::STRING_T:
    orCsonppString.append(hSerializeString(irValue.GetString()));
    break;
  case Value::ValueType::OBJECT_T:
    orCsonppString = hSerializeObject(irValue);
    break;
  case Value::ValueType::ARRAY_T:
    orCsonppString = hSerializeArray(irValue);
    break;
  default:
    orCsonppString = "";
    break;
  }
}

std::string ParserImpl::hSerializeObject(const Value& irValue) const {
  std::string lResult("{");
  const auto& lObject = irValue.GetObject();
  int lSize = irValue.Size();
  auto lCur = 0;
  for (auto lConstItr = lObject.Begin(); 
       lConstItr != lObject.End(); 
       ++lConstItr, ++lCur) {
    lResult.append(hSerializeString(lConstItr->first));
    lResult.append(1, ':');
    std::string lSubStr;
    Serialize(lConstItr->second, lSubStr);
    lResult.append(lSubStr);
    if (lCur != lSize - 1)
      lResult.append(1, ',');
  }
  lResult.append(1, '}');
  return lResult;
}

std::string ParserImpl::hSerializeArray(const Value& irValue) const {
  std::string lResult("[");
  const auto& lArray = irValue.AsArray();
  int lSize = lArray.Size();
  for (auto i = 0; i < lSize; ++i) {
    std::string lSubStr;
    Serialize(lArray[i], lSubStr);
    lResult.append(lSubStr);
    if (i != lSize - 1)
      lResult.append(1, ',');
  }
  lResult.append(1, ']');
  return lResult;
}

std::string ParserImpl::hSerializeString(const std::string& irUtf8String) const {
  auto lInt2HexChar = [] (int iInt) -> char {
    if (iInt >= 0 && iInt < 10) return iInt + '0';
    else if (iInt >= 10 && iInt < 16) return iInt - 10 + 'A';
    return 0;                                                                   
  };

  std::string lResult("\"");
  lResult.resize(irUtf8String.size() * 2);
  const char* lpChar = irUtf8String.c_str();
  while (*lpChar) {
    int32_t lCodePoint = Utf82CodePoint(lpChar);
    if (lCodePoint < 0) {
      lResult.clear();
      return lResult;
    }

    if (lCodePoint > 0x7F) {
      if (lCodePoint <= 0xFFFF) { // in Basic Multilingual Plane
        lResult.append("\\u");
        lResult.append(1, lInt2HexChar(lCodePoint >> 12));
        lResult.append(1, lInt2HexChar((lCodePoint >> 8) & 0xF));
        lResult.append(1, lInt2HexChar((lCodePoint >> 4) & 0xF));
        lResult.append(1, lInt2HexChar(lCodePoint & 0xF));
      } else { // in Supplementary Planes
        lCodePoint -= 0x10000;
        assert(lCodePoint <= 0xFFFFF);
        int32_t lLeadSurrogate = 0xD800 + ((lCodePoint >> 10) & 0x3FF);
        int32_t lTrailSurrogate = 0xDC00 + (lCodePoint & 0x3FF);
        lResult.append("\\u");
        lResult.append(1, lInt2HexChar(lLeadSurrogate >> 12));
        lResult.append(1, lInt2HexChar((lLeadSurrogate >> 8) & 0xF));
        lResult.append(1, lInt2HexChar((lLeadSurrogate >> 4) & 0xF));
        lResult.append(1, lInt2HexChar(lLeadSurrogate & 0xF));
        lResult.append("\\u");
        lResult.append(1, lInt2HexChar(lTrailSurrogate >> 12));
        lResult.append(1, lInt2HexChar((lTrailSurrogate >> 8) & 0xF));
        lResult.append(1, lInt2HexChar((lTrailSurrogate >> 4) & 0xF));
        lResult.append(1, lInt2HexChar(lTrailSurrogate & 0xF));
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
        lResult.append(1, lInt2HexChar((lCodePoint >> 4) & 0xf));
        lResult.append(1, lInt2HexChar(lCodePoint & 0xf));
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
  mTokenizer = std::make_shared<TokenizerImpl>(&irCsonppString);

  auto lErrorOccured = [&orValue, this] {
    orValue = Value();
    mTokenizer->Reset();
    return false;
  };

  if (irCsonppString.empty())
    return lErrorOccured();

  if (!hParseValue(orValue))
    return lErrorOccured();
  return true;
}

bool ParserImpl::hParseValue(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };

  Token lToken = mTokenizer->GetToken();
  switch (lToken.mType) {
  case Token::Type::LEFT_BRACE_T:
    return hParseObject(orValue);
  case Token::Type::LEFT_BRACKET_T:
    return hParseArray(orValue);
  case Token::Type::STRING_T:
    orValue = Value(lToken.mValue);
    return true;
  case Token::Type::INTEGER_T: {
    bool lValid = false;
    int64_t lInteger = Str2Number<int64_t>(lToken.mValue, &lValid);
    if (!lValid)
      return lErrorOccured();
    orValue = Value(lInteger);
    return true;
  }
  case Token::Type::DOUBLE_T: {
    bool lValid = false;
    double lDouble = Str2Number<double>(lToken.mValue, &lValid);
    if (!lValid)
      return lErrorOccured();
    orValue = Value(lDouble);
    return true;
  }
  case Token::Type::TRUE_T:
    orValue = Value(true);
    return true;
  case Token::Type::FALSE_T:
    orValue = Value(false);
    return true;
  case Token::Type::NULL_T:
    orValue = Value(nullptr);
    return true;
  default:
    return lErrorOccured();
  }
}

bool ParserImpl::hParseObject(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };
  orValue = Value(Value::ValueType::OBJECT_T);
  if (!hParseMembers(orValue)) {
    mTokenizer->UngetNextChar();
    auto lToken = mTokenizer->GetToken();
    if (lToken.mType != Token::Type::RIGHT_BRACE_T)
      return lErrorOccured();
    orValue = Value(Value::ValueType::OBJECT_T);
  }
  return true;
}

bool ParserImpl::hParseMembers(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };
  if (!hParsePair(orValue))
    return lErrorOccured();
  auto lToken = mTokenizer->GetToken();
  if (lToken.mType == Token::Type::COMMA_T) {
    return hParseMembers(orValue);
  } else if (lToken.mType == Token::Type::RIGHT_BRACE_T) {
    return true;
  } else {
    return lErrorOccured();
  }
}

bool ParserImpl::hParsePair(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };
  auto lToken = mTokenizer->GetToken();
  if (lToken.mType != Token::Type::STRING_T)
    return lErrorOccured();

  auto lNextToken = mTokenizer->GetToken();
  if (lNextToken.mType != Token::Type::COLON_T)
    return lErrorOccured();

  Value lSubValue;
  if (!hParseValue(lSubValue))
    return lErrorOccured();
  orValue[lToken.mValue] = lSubValue;
  return true;
}

bool ParserImpl::hParseArray(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };
  orValue = Value(Value::ValueType::ARRAY_T);
  if (!hParseElements(orValue)) {
    mTokenizer->UngetNextChar();
    auto lNextToken = mTokenizer->GetToken();
    if (lNextToken.mType != Token::Type::RIGHT_BRACKET_T)
      return lErrorOccured();
    orValue = Value(Value::ValueType::ARRAY_T);
  }
  return true;
}

bool ParserImpl::hParseElements(Value& orValue) {
  auto lErrorOccured = [&orValue] {
    orValue = Value();
    return false;
  };
  Value lSubValue;
  if (!hParseValue(lSubValue))
    return lErrorOccured();
  orValue.Append(std::move(lSubValue));
  auto lNextToken = mTokenizer->GetToken();
  if (lNextToken.mType == Token::Type::RIGHT_BRACKET_T) {
    return true;
  } else if (lNextToken.mType == Token::Type::COMMA_T) {
    return hParseElements(orValue);
  }
  return lErrorOccured();
}

END_CSONPP_NS

