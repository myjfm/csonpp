#include "gtest/gtest.h"
#include "csonpp.h"

TEST(CsonppTest, DeSerializeToObject) {
  std::string str1("{}");
  csonpp::Value value1 = csonpp::Parser::Deserialize(str1);
  ASSERT_TRUE(value1.GetType() == csonpp::Value::Type::kObject);
  ASSERT_EQ(value1.Size(), 0);

  std::string str2("{\"abc\":1}");
  csonpp::Value value2 = csonpp::Parser::Deserialize(str2);
  ASSERT_TRUE(value2.GetType() == csonpp::Value::Type::kObject);
  ASSERT_EQ(value2.Size(), 1);
  ASSERT_EQ(value2["abc"].AsInteger(), 1);

  std::string str3("{\"abc\":1,\"def\":\"abc\"}");
  csonpp::Value value3 = csonpp::Parser::Deserialize(str3);
  ASSERT_TRUE(value3.GetType() == csonpp::Value::Type::kObject);
  ASSERT_EQ(value3.Size(), 2);
  ASSERT_EQ(value3["abc"].AsInteger(), 1);
  ASSERT_EQ(value3["def"].AsString(), "abc");

  std::string str4(" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ");
  csonpp::Value value4 = csonpp::Parser::Deserialize(str4);
  ASSERT_TRUE(value4.GetType() == csonpp::Value::Type::kObject);
  ASSERT_EQ(value4.Size(), 7);
  ASSERT_EQ(value4["hello"].AsString(), "world");
  ASSERT_TRUE(value4["t"].AsBool());
  ASSERT_FALSE(value4["f"].AsBool());
  ASSERT_TRUE(value4["n"].GetType() == csonpp::Value::Type::kNull);
  ASSERT_EQ(value4["i"].AsInteger(), 123);
  ASSERT_DOUBLE_EQ(value4["pi"].AsDouble(), 3.1416);
  ASSERT_EQ(value4["a"].GetType(), csonpp::Value::Type::kArray);
  ASSERT_EQ(value4["a"].Size(), 4);
  ASSERT_EQ(value4["a"][0].AsInteger(), 1);
  ASSERT_EQ(value4["a"][1].AsInteger(), 2);
  ASSERT_EQ(value4["a"][2].AsInteger(), 3);
  ASSERT_EQ(value4["a"][3].AsInteger(), 4);

  std::string str5("{");
  csonpp::Value value5 = csonpp::Parser::Deserialize(str5);
  ASSERT_EQ(value5.GetType(), csonpp::Value::Type::kDummy);

  std::string str6("{12");
  csonpp::Value value6 = csonpp::Parser::Deserialize(str6);
  ASSERT_EQ(value6.GetType(), csonpp::Value::Type::kDummy);

  std::string str7("");
  csonpp::Value value7 = csonpp::Parser::Deserialize(str7);
  ASSERT_EQ(value7.GetType(), csonpp::Value::Type::kDummy);
}

TEST(CsonppTest, DeSerializeToArray) {
  std::string str1("[]");
  csonpp::Value value1 = csonpp::Parser::Deserialize(str1);
  ASSERT_TRUE(value1.GetType() == csonpp::Value::Type::kArray);
  ASSERT_EQ(value1.Size(), 0);

  std::string str2("[3.1456, 1., 2, \"ab\", { \"aaa\" : { \"123\" :   \t1.2e-5}\t}, true, false, null]");
  csonpp::Value value2 = csonpp::Parser::Deserialize(str2);
  ASSERT_TRUE(value2.GetType() == csonpp::Value::Type::kArray);
  ASSERT_EQ(value2.Size(), 8);
  ASSERT_DOUBLE_EQ(value2[0].AsDouble(), 3.1456);
  ASSERT_DOUBLE_EQ(value2[1].AsDouble(), 1.);
  ASSERT_EQ(value2[2].AsInteger(), 2);
  ASSERT_EQ(value2[3].AsString(), "ab");
  ASSERT_TRUE(value2[4].GetType() == csonpp::Value::Type::kObject);
  ASSERT_EQ(value2[4].Size(), 1);
  ASSERT_TRUE(value2[4]["aaa"].GetType() == csonpp::Value::Type::kObject);
  ASSERT_DOUBLE_EQ(value2[4]["aaa"]["123"].AsDouble(), 0.000012);
  ASSERT_TRUE(value2[5].AsBool());
  ASSERT_FALSE(value2[6].AsBool());
  ASSERT_TRUE(value2[7].GetType() == csonpp::Value::Type::kNull);

  std::string str3("[12,false, false  , null , [12e4,32, [], \"12\"]]");
  csonpp::Value value3 = csonpp::Parser::Deserialize(str3);
  ASSERT_TRUE(value3.GetType() == csonpp::Value::Type::kArray);
  ASSERT_EQ(value3.Size(), 5);
  ASSERT_EQ(value3[0].AsInteger(), 12);
  ASSERT_FALSE(value3[1].AsBool());
  ASSERT_FALSE(value3[2].AsBool());
  ASSERT_EQ(value3[3].GetType(), csonpp::Value::Type::kNull);
  ASSERT_EQ(value3[4].GetType(), csonpp::Value::Type::kArray);
  ASSERT_EQ(value3[4].Size(), 4);
  ASSERT_DOUBLE_EQ(value3[4][0].AsDouble(), 120000);
  ASSERT_EQ(value3[4][1].AsInteger(), 32);
  ASSERT_EQ(value3[4][2].GetType(), csonpp::Value::Type::kArray);
  ASSERT_EQ(value3[4][2].Size(), 0);
  ASSERT_EQ(value3[4][3].AsString(), "12");
}

TEST(CsonppTest, DeserializeUnicodeString) {
  std::string str1("[3.1456, 1., 2, \"a\\u0062\", { \"a\\u5066a\" : { \"12\\uD800\\uDC00\" :   \t1.2e-2}\t}, true, false, null]");
  csonpp::Value value1 = csonpp::Parser::Deserialize(str1);
  ASSERT_TRUE(value1.GetType() == csonpp::Value::Type::kArray);
  ASSERT_EQ(value1.Size(), 8);
  ASSERT_DOUBLE_EQ(value1[0].AsDouble(), 3.1456);
  ASSERT_DOUBLE_EQ(value1[1].AsDouble(), 1.);
  ASSERT_EQ(value1[2].AsInteger(), 2);
  ASSERT_EQ(value1[3].AsString(), "ab");
  ASSERT_EQ(value1[4].GetType(), csonpp::Value::Type::kObject);
  ASSERT_EQ(value1[4].Size(), 1);
  ASSERT_EQ(value1[4]["a\xE5\x81\xA6\x61"].GetType(), csonpp::Value::Type::kObject);
  ASSERT_EQ(value1[4]["a\xE5\x81\xA6\x61"]["12\xF0\x90\x80\x80"].AsDouble(), 0.012);
  ASSERT_TRUE(value1[5].AsBool());
  ASSERT_FALSE(value1[6].AsBool());
  ASSERT_EQ(value1[7].GetType(), csonpp::Value::Type::kNull);
}

TEST(CsonppTest, Serialize) {
  std::string str1 = "\"I \\uD834\\uDD1E playing with json\"";
  csonpp::Value value1 = csonpp::Parser::Deserialize(str1);
  ASSERT_EQ(value1.GetType(), csonpp::Value::Type::kString);
  ASSERT_EQ(value1.AsString(), "I \xF0\x9D\x84\x9E playing with json");
  ASSERT_EQ(csonpp::Parser::Serialize(value1), str1);

  std::string str2 = "-12e-3";
  csonpp::Value value2 = csonpp::Parser::Deserialize(str2);
  ASSERT_EQ(value2.GetType(), csonpp::Value::Type::kDouble);
  ASSERT_DOUBLE_EQ(value2.AsDouble(), -0.012);
  ASSERT_EQ(csonpp::Parser::Serialize(value2), "-0.0120");

  std::string str3 = "1234567";
  csonpp::Value value3 = csonpp::Parser::Deserialize(str3);
  ASSERT_EQ(value3.GetType(), csonpp::Value::Type::kInteger);
  ASSERT_DOUBLE_EQ(value3.AsInteger(), 1234567);
  ASSERT_EQ(csonpp::Parser::Serialize(value3), "1234567");

  std::string str4 = "-1234567.50";
  csonpp::Value value4 = csonpp::Parser::Deserialize(str4);
  ASSERT_EQ(value4.GetType(), csonpp::Value::Type::kDouble);
  ASSERT_DOUBLE_EQ(value4.AsDouble(), -1234567.50);
  ASSERT_EQ(csonpp::Parser::Serialize(value4), "-1234567.50");

  std::string str5 = "{\"a\":   \t-1234567.50}";
  csonpp::Value value5 = csonpp::Parser::Deserialize(str5);
  ASSERT_EQ(value5.GetType(), csonpp::Value::Type::kObject);
  ASSERT_EQ(csonpp::Parser::Serialize(value5), "{\"a\":-1234567.50}");

  std::string str6("[3.1456, 1., 2, \"a\\u0062\", { \"a\\u5066a\" : { \"12\\uD800\\uDC00\" :   \t1.2e-2}\t}, true, false, null]");
  csonpp::Value value6 = csonpp::Parser::Deserialize(str6);
  ASSERT_EQ(csonpp::Parser::Serialize(value6), "[3.14560,1.0,2,\"ab\",{\"a\\u5066a\":{\"12\\uD800\\uDC00\":0.0120}},true,false,null]");

  std::string str7("[12,false, false  , null , [12e4,32, [], \"12\"]]");
  csonpp::Value value7 = csonpp::Parser::Deserialize(str7);
  std::string aa = csonpp::Parser::Serialize(value7);
  ASSERT_EQ(csonpp::Parser::Serialize(value7), "[12,false,false,null,[120000.0,32,[],\"12\"]]");
}

