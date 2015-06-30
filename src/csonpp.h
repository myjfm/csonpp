#ifndef CSONPP_CSONPP_H_
#define CSONPP_CSONPP_H_

#include <assert.h>

#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

namespace csonpp {

class Value;

class Object {
 public:
  typedef std::map<std::string, Value> MapType;
  typedef MapType::const_iterator ConstIterator;
  typedef MapType::iterator Iterator;
  
  friend bool operator==(const Object& left, const Object& right);
  friend bool operator!=(const Object& left, const Object& right);
  friend bool operator>(const Object& left, const Object& right);
  friend bool operator<(const Object& left, const Object& right);
  friend bool operator<=(const Object& left, const Object& right);
  friend bool operator>=(const Object& left, const Object& right);

 public:
  Object() = default;
  Object(const Object& other);
  Object(Object&& other);

  Object& operator=(const Object& other);
  Object& operator=(Object&& other);
  
  // find element matching irKey, or insert with default Value
  Value& operator[](const std::string& key);
  // find element matching irKey, or insert with default Value
  Value& operator[](std::string&& key);

  ConstIterator CBegin() const;
  ConstIterator CEnd() const;

  ConstIterator Begin() const;
  ConstIterator End() const;

  Iterator Begin();
  Iterator End();
  
  Iterator Find(const std::string& key);
  ConstIterator Find(const std::string& key) const;
  
  void Clear();

  size_t Size() const;
  
 private:
  MapType value_;
};

class Array {
  typedef std::vector<Value> ContainerType;
  typedef ContainerType::const_iterator ConstIterator;
  typedef ContainerType::iterator Iterator;
  
  friend bool operator==(const Array& left, const Array& right);
  friend bool operator!=(const Array& left, const Array& right);
  friend bool operator>(const Array& left, const Array& right);
  friend bool operator<(const Array& left, const Array& right);
  friend bool operator>=(const Array& left, const Array& right);
  friend bool operator<=(const Array& left, const Array& right);
  
 public:
  Array() = default;

  Array(const Array& other);
  Array(Array&& other);

  Array& operator=(const Array& other);
  Array& operator=(Array&& other);
  
  // the element must exist
  Value& operator[](size_t i);
  // the element must exist
  const Value& operator[](size_t i) const;

  void Append(const Value& value);
  void Append(Value&& value);

  ConstIterator CBegin() const;
  ConstIterator CEnd() const;

  ConstIterator Begin() const;

  ConstIterator End() const;

  Iterator Begin();
  Iterator End();

  Iterator Find(const Value& value);
  ConstIterator Find(const Value& value) const;

  void Clear();

  size_t Size() const;
  
 private:
  ContainerType value_;
};

class Value {
 public:
  enum class Type {
    kDummy    = 0,  /* invalid type */
    kNull     = 1,  /* e.g. null */
    kBool     = 2,  /* e.g. true or false */
    kInteger  = 3,  /* e.g. -100 */
    kDouble   = 4,  /* e.g. -1.2e-10 */
    kString   = 5,  /* e.g. "abcd" */
    kObject   = 6,  /* e.g. {"a":true} */
    kArray    = 7,  /* e.g. ["a", "b"] */
  };

  friend bool operator==(const Value& left, const Value& right);
  friend bool operator!=(const Value& left, const Value& right);
  friend bool operator<(const Value& left, const Value& right);
  friend bool operator>(const Value& left, const Value& right);
  friend bool operator<=(const Value& left, const Value& right);
  friend bool operator>=(const Value& left, const Value& right);

  explicit Value(Type type = Type::kDummy);
  explicit Value(std::nullptr_t null);
	explicit Value(bool value);
	explicit Value(int8_t value);
	explicit Value(uint8_t value);
	explicit Value(int16_t value);
	explicit Value(uint16_t value);
	explicit Value(int32_t value);
	explicit Value(uint32_t value);
	explicit Value(int64_t value);
  // TODO
  // do not support uint64_t
#if 0
	explicit Value(uint64_t value);
#endif
	explicit Value(float value);
	explicit Value(double value);
	explicit Value(const std::string& value);
	explicit Value(std::string&& value);
	explicit Value(const Object& value);
	explicit Value(Object&& value);
	explicit Value(const Array& value);
	explicit Value(Array&& value);

  ~Value() {}

	Value(const Value& value);
  Value(Value&& value);

	Value& operator=(const Value& value);
	Value& operator=(Value&& value);
	Value& operator=(bool value);
	Value& operator=(int8_t value);
	Value& operator=(uint8_t value);
	Value& operator=(int16_t value);
	Value& operator=(uint16_t value);
	Value& operator=(int32_t value);
	Value& operator=(uint32_t value);
	Value& operator=(int64_t value);
  // TODO
  // do not support uint64_t
#if 0
	Value& operator=(uint64_t value);
#endif
	Value& operator=(float value);
	Value& operator=(double value);
	Value& operator=(const std::string& value);
	Value& operator=(std::string&& value);
	Value& operator=(const Object& value);
	Value& operator=(Object&& value);
	Value& operator=(const Array& value);
	Value& operator=(Array&& value);

  void Append(const Value& value);
  void Append(Value&& value);
  void Append(const std::string& key, bool value);
  void Append(std::string&& key, bool value);
  void Append(const std::string& key, int8_t value);
  void Append(std::string&& key, int8_t value);
  void Append(const std::string& key, uint8_t value);
  void Append(std::string&& key, uint8_t value);
  void Append(const std::string& key, int16_t value);
  void Append(std::string&& key, uint16_t value);
  void Append(const std::string& key, int32_t value);
  void Append(std::string&& key, int32_t value);
  void Append(const std::string& key, uint32_t value);
  void Append(std::string&& key, uint32_t value);
  void Append(const std::string& key, int64_t value);
  void Append(std::string&& key, int64_t value);
  // TODO
  // do not support uint64_t
#if 0
  void Append(const std::string& key, uint64_t value);
  void Append(std::string&& key, uint64_t value);
#endif
  void Append(const std::string& key, float value);
  void Append(std::string&& key, float value);
  void Append(const std::string& key, double value);
  void Append(std::string&& key, double value);
  void Append(const std::string& key, const std::string& value);
  void Append(std::string&& key, const std::string& value);
  void Append(const std::string& key, std::string&& value);
  void Append(std::string&& key, std::string&& value);
  void Append(const std::string& key, const Object& value);
  void Append(std::string&& key, const Object& value);
  void Append(const std::string& key, Object&& value);
  void Append(std::string&& key, Object&& value);
  void Append(const std::string& key, const Array& value);
  void Append(std::string&& key, const Array& value);
  void Append(const std::string& key, Array&& value);
  void Append(std::string&& key, Array&& value);

	Type GetType() const;

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

  Value& operator[](size_t i);
  const Value& operator[](size_t i) const;
  Value& operator[](const std::string& key);
  Value& operator[](std::string&& key);
  
 private:
  Type type_;

  union {
    bool bool_;
    int64_t integer_;
    double double_;
  };
  std::string string_;
  Array array_;
  Object object_;
};

class Parser {
 public:
  static bool Deserialize(const std::string& csonpp_str, Value& value);

  static Value Deserialize(const std::string& csonpp_str) {
    Value value;
    Deserialize(csonpp_str, value);
    return std::move(value);
  }

  static void Serialize(const Value& value, std::string& csonpp_str);

  static std::string Serialize(const Value& value) {
    std::string csonpp_str;
    Serialize(value, csonpp_str);
    return std::move(csonpp_str);
  }
};

}  // namespace csonpp

#endif  // CSONPP_CSONPP_H_

