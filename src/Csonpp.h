#ifndef _CSONPP_CSONPP_H_
#define _CSONPP_CSONPP_H_

#include <assert.h>

#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

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
  Object() = default;
  Object(const Object& irOther) ;
  Object(Object&& irrOther);

  Object& operator=(const Object& irOther);
  Object& operator=(const Object&& irrOther);
  
  // find element matching irKey, or insert with default Value
  Value& operator[](const std::string& irKey);
  // find element matching irKey, or insert with default Value
  Value& operator[](std::string&& irrKey);

  ConstIterator CBegin() const;
  ConstIterator CEnd() const;

  ConstIterator Begin() const;
  ConstIterator End() const;

  Iterator Begin();
  Iterator End();
  
  Iterator Find(const std::string& irKey);
  ConstIterator Find(const std::string& irKey) const;
  
  void Clear();

  size_t Size() const;
  
private:
  Map mValue;
};

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
  Array() = default;

  Array(const Array& irArray) ;
  Array(Array&& irrArray);

  Array& operator=(const Array& irArray);
  Array& operator=(Array&& irrArray);
  
  // the element must exist
  Value& operator[](size_t iIndex);
  // the element must exist
  const Value& operator[](size_t iIndex) const;

  void Append(const Value& irValue);
  void Append(Value&& irrValue);

  ConstIterator CBegin() const;
  ConstIterator CEnd() const;

  ConstIterator Begin() const;

  ConstIterator End() const;

  Iterator Begin();
  Iterator End();

  Iterator Find(const Value& irValue);
  ConstIterator Find(const Value& irValue) const;

  void Clear();

  size_t Size() const;
  
private:
  Container mValue;
};

class Value {
public:
  enum class ValueType {
    DUMMY_T   = 0,  /* invalid type */
    NULL_T    = 1,  /* e.g. null */
    BOOL_T    = 2,  /* e.g. true or false */
    INTEGER_T = 3,  /* e.g. -100 */
    DOUBLE_T  = 4,  /* e.g. -1.2e-10 */
    STRING_T  = 5,  /* e.g. "abcd" */
    OBJECT_T  = 6,  /* e.g. {"a":true} */
    ARRAY_T   = 7,  /* e.g. ["a", "b"] */
  };

  friend bool operator==(const Value& irL, const Value& irR);
  friend bool operator!=(const Value& irL, const Value& irR);
  friend bool operator<(const Value& irL, const Value& irR);
  friend bool operator>(const Value& irL, const Value& irR);
  friend bool operator<=(const Value& irL, const Value& irR);
  friend bool operator>=(const Value& irL, const Value& irR);

  explicit Value(ValueType iType = ValueType::DUMMY_T);
  explicit Value(std::nullptr_t iNull);
	explicit Value(bool iValue);
	explicit Value(int8_t iValue);
	explicit Value(uint8_t iValue);
	explicit Value(int16_t iValue);
	explicit Value(uint16_t iValue);
	explicit Value(int32_t iValue);
	explicit Value(uint32_t iValue);
	explicit Value(int64_t iValue);
  // TODO
  // do not support uint64_t
#if 0
	explicit Value(uint64_t iValue);
#endif
	explicit Value(float iValue);
	explicit Value(double iValue);
	explicit Value(const std::string& irValue);
	explicit Value(std::string&& irrValue);
	explicit Value(const Object& irValue);
	explicit Value(Object&& irrValue);
	explicit Value(const Array& irValue);
	explicit Value(Array&& irrValue);

  ~Value() {}

	Value(const Value& irValue);
  Value(Value&& irrValue);

	Value& operator=(const Value& irValue);
	Value& operator=(Value&& irrValue);
	Value& operator=(bool irBool);
	Value& operator=(int8_t irInt);
	Value& operator=(uint8_t irInt);
	Value& operator=(int16_t irInt);
	Value& operator=(uint16_t irInt);
	Value& operator=(int32_t irInt);
	Value& operator=(uint32_t irInt);
	Value& operator=(int64_t irInt);
  // TODO
  // do not support uint64_t
#if 0
	Value& operator=(uint64_t irInt);
#endif
	Value& operator=(float irDouble);
	Value& operator=(double irDouble);
	Value& operator=(const std::string& irString);
	Value& operator=(std::string&& irrString);
	Value& operator=(const Object& irObject);
	Value& operator=(Object&& irrObject);
	Value& operator=(const Array& irArray);
	Value& operator=(Array&& irrArray);

  void Append(const Value& irValue);
  void Append(Value&& irrValue);
  void Append(const std::string& irKey, bool iValue);
  void Append(std::string&& irrKey, bool iValue);
  void Append(const std::string& irKey, int8_t iValue);
  void Append(std::string&& irrKey, int8_t iValue);
  void Append(const std::string& irKey, uint8_t iValue);
  void Append(std::string&& irrKey, uint8_t iValue);
  void Append(const std::string& irKey, int16_t iValue);
  void Append(std::string&& irrKey, uint16_t iValue);
  void Append(const std::string& irKey, int32_t iValue);
  void Append(std::string&& irrKey, int32_t iValue);
  void Append(const std::string& irKey, uint32_t iValue);
  void Append(std::string&& irrKey, uint32_t iValue);
  void Append(const std::string& irKey, int64_t iValue);
  void Append(std::string&& irrKey, int64_t iValue);
  // TODO
  // do not support uint64_t
#if 0
  void Append(const std::string& irKey, uint64_t iValue);
  void Append(std::string&& irrKey, uint64_t iValue);
#endif
  void Append(const std::string& irKey, float iValue);
  void Append(std::string&& irrKey, float iValue);
  void Append(const std::string& irKey, double iValue);
  void Append(std::string&& irrKey, double iValue);
  void Append(const std::string& irKey, const std::string& irValue);
  void Append(std::string&& irrKey, const std::string& irValue);
  void Append(const std::string& irKey, std::string&& irrValue);
  void Append(std::string&& irrKey, std::string&& irrValue);
  void Append(const std::string& irKey, const Object& irValue);
  void Append(std::string&& irrKey, const Object& irValue);
  void Append(const std::string& irKey, Object&& irrValue);
  void Append(std::string&& irrKey, Object&& irrValue);
  void Append(const std::string& irKey, const Array& irValue);
  void Append(std::string&& irrKey, const Array& irValue);
  void Append(const std::string& irKey, Array&& irrValue);
  void Append(std::string&& irrKey, Array&& irrValue);

	ValueType Type() const;

  size_t Size() const;

  void Clear();

  bool IsNumeric() const;
  bool IsIntegral() const;
  bool IsDouble() const;
  bool IsBool() const;
  bool IsString() const;
  bool IsObject() const;
  bool IsArray() const;

  int64_t AsInteger() const;
  double AsDouble() const;
  bool AsBool() const;
  std::string AsString() const;
  Object AsObject() const;
  Array AsArray() const;

  const int64_t& GetInteger() const;
  const double& GetDouble() const;
  const bool& GetBool() const;
  const std::string& GetString() const;
  const Object& GetObject() const;
  const Array& GetArray() const;

  Value& operator[](size_t iIndex);
  const Value& operator[](size_t iIndex) const;
  Value& operator[](const std::string& irKey);
  Value& operator[](std::string&& irrKey);
  
private:
  ValueType mType;

  union {
    bool mBool;
    int64_t mInteger;
    double mDouble;
  };
  std::string mString;
  Array mArray;
  Object mObject;
};

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

