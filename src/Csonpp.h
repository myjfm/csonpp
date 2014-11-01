#ifndef _CSONPP_CSONPP_H_
#define _CSONPP_CSONPP_H_

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include <string>
#include <map>
#include <vector>

#define START_CSONPP_NS namespace Csonpp {
#define END_CSONPP_NS }
#define CSONPP Csonpp

START_CSONPP_NS

class Value;

class Object {
public:
  typedef std::map<std::string, Value> Map;
  typedef Map::const_iterator ConstIterator;
  typedef Map::iterator Iterator;
  
  friend bool operator==(const Object& irL, const Object& irR);
  friend bool operator!=(const Object& irL, const Object& irR);
  friend bool operator>(const Object& irL, const Object& irR);
  friend bool operator<(const Object& irL, const Object& irR);
  friend bool operator<=(const Object& irL, const Object& irR);
  friend bool operator>=(const Object& irL, const Object& irR);

public:
  Object() {}

  Object(const Object& irOther) 
  : mValue(irOther.mValue) {
  }

  Object(Object&& irvOther) 
  : mValue(std::move(irOther.mValue)) {
  }

  Object& operator=(const Object& irOther) {
    if (this != &irOther)
      mValue = irOther.mValue;
    return *this;
  }

  Object& operator=(const Object&& irOther) {
    if (this != &irOther)
      mValue = std::move(irOther.mValue);
    return *this;
  }
  
  // find element matching irKey, or insert with default Value
  Value& operator[](const std::string& irKey) {
    return mValue[irKey];
  }

  // find element matching irKey, or insert with default Value
  Value& operator[](std::string&& irKey) {
    return mValue[std::move(irKey)];
  }

  ConstIterator CBegin() const {
    return mValue.cbegin();
  }

  ConstIterator CEnd() const {
    return mVlaue.cend();
  }

  ConstIterator Begin() const {
    return mValue.begin();
  }

  ConstIterator End() const {
    return mValue.end();
  }

  Iterator Begin() {
    return mValue.begin();
  }

  Iterator End() {
    return mValue.end();
  }
  
  Iterator Find(const std::string& irKey) {
    return mValue.find(irKey);
  }

  ConstIterator Find(const std::string& irKey) const {
    return mValue.find(irKey);
  }
  
  void Clear() {
    mValue.clear();
  }
  size_t Size() const {
    return mValue.size();
  }
  
private:
  Map mValue;
};

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

class Array {
  typedef std::vector<Value> Container;
  typedef Container::const_iterator ConstIterator;
  typedef Container::iterator Iterator;
  
  friend bool operator==(const Array& irL, const Array& irR);
  friend bool operator!=(const Array& irL, const Array& irR);
  friend bool operator>(const Array& irL, const Array& irR);
  friend bool operator<(const Array& irL, const Array& irR);
  friend bool operator>=(const Array& irL, const Array& irR);
  friend bool operator<=(const Array& irL, const Array& irR);
  
public:
  Array() {}

  Array(const Array& irArray) 
  : mValue(irArray.mValue) {
  }

  Array(Array&& irArray) 
  : mValue(std::move(irArray.mValue)) {
  }

  Array& operator=(const Array& irArray) {
    if (this != &irArray)
      mValue = irArray.mValue;
    return *this;
  }

  Array& operator=(Array&& irArray) {
    if (this != &irArray)
      mValue = std::move(irArray.mValue);
    return *this;
  }
  
  // the element must exist
  Value& operator[](size_t iIndex) {
    assert(iIndex < mValue.size());
    return mValue[iIndex];
  }
  
  // the element must exist
  const Value& operator[](size_t iIndex) const {
    assert(iIndex < mValue.size());
    return mValue[iIndex];
  }

  void Append(const Value& irValue) {
    mValue.push_back(irValue);
  }

  void Append(Value&& irValue) {
    mValue.push_back(std::move(irValue));
  }

  ConstIterator CBegin() const {
    return mValue.cbegin();
  }

  ConstIterator CEnd() const {
    return mValue.cend();
  }

  ConstIterator Begin() const {
    return mValue.begin();
  }

  ConstIterator End() const {
    return mValue.end();
  }

  Iterator Begin() {
    return mValue.begin();
  }

  Iterator End() {
    return mValue.end();
  }

  Iterator Find(const Value& irValue) {
    return std::find(Begin(), End(), irValue);
  }

  ConstIterator Find(const Value& irValue) const {
    return std::find(Begin(), End(), irValue);
  }

  void Clear() {
    mValue.clear();
  }

  size_t Size() const {
    return mValue.size();
  }
  
private:
  Container mValue;
};

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

class Value {
public:
  enum class ValueType {
    DUMMY_T = 0,   /* invalid type */
    NULL_T = 1,    /* e.g. null */
    BOOL_T = 2,    /* e.g. true or false */
    DOUBLE_T = 3,  /* e.g. -10.05 */
    INT_T = 4,     /* e.g. -10 */
    STRING_T = 5,  /* e.g. "abcd" */
    ARRAY_T = 6,   /* e.g. ["a", "b"] */
    OBJECT_T = 7,  /* e.g. {"a":true} */
  };

  explicit Value(ValueType iType = ValueType::DUMMY_T) 
  : mType(iType) {
  }

  explicit Value(std::nullptr_t iNull) 
  : mType(ValueType::NULL_T) {
  }

	explicit Value(bool iValue) 
  : mType(ValueType::BOOL_T), 
    mBool(iValue) {
  }

  explicit Value(int64_t iValue) 
  : mType(ValueType::INT_T), 
    mInt(iValue) {
  }

	explicit Value(double iValue) 
  : mType(ValueType::DOUBLE_T), 
    mDouble(iValue) {
  }

	explicit Value(const char* ipValue) 
  : mType(ValueType::STRING_T), 
    mString(ipValue) {
  }

	explicit Value(const std::string& irValue) 
  : mType(ValueType::STRING_T), 
    mString(irValue) {
  }

	explicit Value(std::string&& irValue) 
  : mType(ValueType::STRING_T), 
    mString(std::move(irValue)) {
  }

	explicit Value(const Array& irValue) 
  : mType(ValueType::ARRAY_T), 
    mArray(irValue) {
  }

	explicit Value(Array&& irValue) 
  : mType(ValueType::ARRAY_T), 
    mArray(std::move(irValue)) {
  }

	explicit Value(const Object& irValue) 
  : mType(ValueType::OBJECT_T), 
    mObject(irValue) {
  }

	explicit Value(Object&& irValue) 
  : mType(ValueType::OBJECT_T), 
    mObject(std::move(irValue)) {
  }

  ~Value() {}

	Value(const Value& irValue) 
  : mType(irValue.mType) {
    switch(mType) {
    case ValueType::BOOL_T:
      mBool = irValue.mBool;
      break;
    case ValueType::INT_T:
      mInt = irValue.mInt;
      break;
    case ValueType::DOUBLE_T:
      mDouble = irValue.mDouble;
      break;
    case ValueType::STRING_T:
      mString = irValue.mString;
      break;
    case ValueType::ARRAY_T:
      mArray = irValue.mArray;
      break;
    case ValueType::OBJECT_T:
      mObject = irValue.mObject;
      break;
    default:
      break;
    }
  }
  
  Value(Value&& irValue) 
  : mType(irValue.mType) {
    switch(mType) {
    case ValueType::BOOL_T:
      mBool = irValue.mBool;
      break;
    case ValueType::INT_T:
      mInt = irValue.mInt;
      break;
    case ValueType::DOUBLE_T:
      mDouble = irValue.mDouble;
      break;
    case ValueType::STRING_T:
      mString = std::move(irValue.mString);
      break;
    case ValueType::ARRAY_T:
      mArray = std::move(irValue.mArray);
      break;
    case ValueType::OBJECT_T:
      mObject = std::move(irValue.mObject);
      break;
    default:
      break;
    }
  }

	Value& operator=(const Value& irValue) {
    if (&irValue != this) {
      mType = irValue.mType;
      switch(mType) {
      case ValueType::BOOL_T:
        mBool = irValue.mBool;
        break;
      case ValueType::INT_T:
        mInt = irValue.mInt;
        break;
      case ValueType::DOUBLE_T:
        mDouble = irValue.mDouble;
        break;
      case ValueType::STRING_T:
        mString = irValue.mString;
        break;
      case ValueType::ARRAY_T:
        mArray = irValue.mArray;
        break;
      case ValueType::OBJECT_T:
        mObject = irValue.mObject;
        break;
      default:
        break;
      }
    }

    return *this;
  }

	Value& operator=(Value&& irValue) {
    if (&irValue != this) {
      mType = irValue.mType;
      switch(mType) {
      case ValueType::BOOL_T:
        mBool = irValue.mBool;
        break;
      case ValueType::INT_T:
        mInt = irValue.mInt;
        break;
      case ValueType::DOUBLE_T:
        mDouble = irValue.mDouble;
        break;
      case ValueType::STRING_T:
        mString = std::move(irValue.mString);
        break;
      case ValueType::ARRAY_T:
        mArray = std::move(irValue.mArray);
        break;
      case ValueType::OBJECT_T:
        mObject = std::move(irValue.mObject);
        break;
      default:
        break;
      }
    }

    return *this;
  }

	Value& operator=(bool irBool) {
    mType = ValueType::BOOL_T;
    mBool = irBool;
    return *this;
  }

	Value& operator=(int64_t irInt) {
    mType = ValueType::INT_T;
    mInt = irInt;
    return *this;
  }

	Value& operator=(double irDouble) {
    mType = ValueType::DOUBLE_T;
    mDouble = irDouble;
    return *this;
  }

	Value& operator=(const std::string& irString) {
    mType = ValueType::STRING_T;
    mString = irString;
    return *this;
  }

	Value& operator=(std::string&& irString) {
    mType = ValueType::STRING_T;
    mString = std::move(irString);
    return *this;
  }

	Value& operator=(const Object& irObject) {
    mType = ValueType::OBJECT_T;
    mObject = irObject;
    return *this;
  }

	Value& operator=(Object&& irObject) {
    mType = ValueType::OBJECT_T;
    mObject = std::move(irObject);
    return *this;
  }

	Value& operator=(const Array& irArray) {
    mType = ValueType::ARRAY_T;
    mArray = irArray;
    return *this;
  }

	Value& operator=(Array&& irArray) {
    mType = ValueType::ARRAY_T;
    mArray = std::move(irArray);
    return *this;
  }

  void Append(const Value& irValue) {
    assert(mType == ValueType::ARRAY_T);
    mArray.push_back(irValue);
  }

  void Append(Value&& irValue) {
    assert(mType == ValueType::ARRAY_T);
    mArray.push_back(std::move(irValue));
  }

  void Append(const std::string& irKey, bool iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, bool iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, int64_t iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, int64_t iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, double iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, double iValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, const char* ipValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, const char* ipValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, const std::string& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, const std::string& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, std::string&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = std::move(iValue);
  }

  void Append(std::string&& irKey, std::string&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = std::move(iValue);
  }

  void Append(const std::string& irKey, const Object& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, const Object& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, Object&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = std::move(iValue);
  }

  void Append(std::string&& irKey, Object&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = std::move(iValue);
  }

  void Append(const std::string& irKey, const Array& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = iValue;
  }

  void Append(std::string&& irKey, const Array& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = iValue;
  }

  void Append(const std::string& irKey, Array&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[irKey] = std::move(iValue);
  }

  void Append(std::string&& irKey, Array&& irValue) {
    assert(mType == ValueType::OBJECT_T);
    mObject[std::move(irKey)] = std::move(iValue);
  }

  friend bool operator==(const Value& irL, const Value& irR);
  friend bool operator!=(const Value& irL, const Value& irR);
  friend bool operator<(const Value& irL, const Value& irR);
  friend bool operator>(const Value& irL, const Value& irR);
  friend bool operator<=(const Value& irL, const Value& irR);
  friend bool operator>=(const Value& irL, const Value& irR);

	ValueType Type() const {
    return mType;
  }

  size_t Size() const {
    assert(mType == ValueType::OBJECT_T || mType == ValueType::ARRAY_T);
    return (mType == ValueType::OBJECT_T) ? mObject.Size() : mArray.Size();
  }

  void Clear() {
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

  bool IsNumeric() const {
    return (mType == ValueType::DOUBLE_T || mType == ValueType::INT_T);
  }

  bool IsIntegral() const {
    return mType == ValueType::INT_T;
  }

  bool IsBool() const {
    return mType == ValueType::BOOL_T;
  }

  bool IsString() const {
    return mType == ValueType::STRING_T;
  }

  bool IsObject() const {
    return mType == ValueType::OBJECT_T;
  }

  bool IsArray() const {
    return mType == ValueType::ARRAY_T;
  }

  int64_t AsInteger() const {
    if (mType == ValueType::INT_T) {
      return mInt;
    } else if (mType == ValueType::DOUBLE_T) {
      return static_cast<int64_t>(mDouble);
    } else {
      assert(false);
    }
  }

  double AsDouble() const {
    if (mType == ValueType::INT_T) {
      return static_cast<double>(mInt);
    } else if (mType == ValueType::DOUBLE_T) {
      return mDouble;
    } else {
      assert(false);
    }
  }

  bool AsBool() const {
    assert(mType == ValueType::BOOL_T);
    return mBool;
  }

  std::string AsString() const {
    assert(mType == ValueType::STRING_T);
    return mString;
  }

  Object AsObject() const {
    assert(mType == ValueType::OBJECT_T);
    return mObject;
  }

  Array AsArray() const {
    assert(mType == ValueType::ARRAY_T);
    return mArray;
  }

  Value& operator[](size_t iIndex) {
    assert(mType == ValueType::ARRAY_T);
    assert(iIndex < mArray.size());
    return mArray[iIndex];
  }

  const Value& operator[](size_t iIndex) const {
    assert(mType == ValueType::ARRAY_T);
    assert(iIndex < mArray.size());
    return mArray[iIndex];
  }

  Value& operator[](const std::string& irKey) {
    assert(mType == ValueType::OBJECT_T);
    return mObject[irKey];
  }

  Value& operator[](std::string&& irKey) {
    assert(mType == ValueType::OBJECT_T);
    return mObject[std::move(irKey)];
  }
  
private:
  ValueType mType;

  union {
    bool mBool;
    int64_t mInt;
    double mDouble;
  };
  std::string mString;
  Array mArray;
  Object mObject;
};

bool operator==(const Value& irL, const Value& irR) {
  if (irL.mType != irR.mType && (!irL.IsNumeric() || !irR.IsNumeric()))
    return false;

  switch (irL.mType) {
  case Value::ValueType::BOOL_T:
    return irL.mBool == irR.mBool;
  case Value::ValueType::INT_T:
    if (irR.mType == Value::ValueType::DOUBLE_T) {
      return (static_cast<double>(irL.mInt) - irR.mDouble) < 1e-8;
    } else if (irR.mType == Value::ValueType::INT_T) {
      return irL.mInt == irR.mInt;
    } else {
      return false;
    }
  case Value::ValueType::DOUBLE_T:
    if (irR.mType == Value::ValueType::DOUBLE_T) {
      return (irL.mDouble - irR.mDouble) < 1e-8;
    } else if (irR.mType == Value::ValueType::INT_T) {
      return (irL.mDouble - static_cast<double>(irR.mInt)) < 1e-8;
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
    return irL.mInt < irR.mInt;
  } else if (irL.IsIntegral() && irR.IsDouble()) {
    return static_cast<double>(irL.mInt) < irR.mDouble;
  } else if (irL.IsDouble() && irR.IsIntegral()) {
    return irL.mDouble < static_cast<double>(irR.mInt);
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

class Parser {
public:
  static bool Deserialize(const std::string& irCsonppString, Value& orValue);

  static Value Deserialize(const std::string& irCsonppString) {
    Value lValue;
    Deserialize(irCsonppString, lValue);
    return lValue;
  }

  static void Serialize(const Value& irValue, std::string& orCsonppString);

  static std::string Serialize(const Value& irValue) {
    std::string lCsonppString;
    Serialize(irValue, lCsonppString);
    return lCsonppString;
  }
};

END_CSONPP_NS

#endif

