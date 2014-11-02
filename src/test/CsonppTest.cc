#include "gtest/gtest.h"
#include "Csonpp.h"

TEST(CsonppTest, DeSerializeToObject) {
  std::string lStr_2("{");
  CSONPP::Value lValue_2 = CSONPP::Parser::Deserialize(lStr_2);
  ASSERT_EQ(lValue_2.Type(), CSONPP::Value::ValueType::DUMMY_T);

  std::string lStr_1("{12");
  CSONPP::Value lValue_1 = CSONPP::Parser::Deserialize(lStr_1);
  ASSERT_EQ(lValue_1.Type(), CSONPP::Value::ValueType::DUMMY_T);

  std::string lStr0("");
  CSONPP::Value lValue0 = CSONPP::Parser::Deserialize(lStr0);
  ASSERT_EQ(lValue0.Type(), CSONPP::Value::ValueType::DUMMY_T);

  std::string lStr1("{}");
  CSONPP::Value lValue1 = CSONPP::Parser::Deserialize(lStr1);
  ASSERT_TRUE(lValue1.Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue1.Size(), 0);

  std::string lStr2("{\"abc\":1}");
  CSONPP::Value lValue2 = CSONPP::Parser::Deserialize(lStr2);
  ASSERT_TRUE(lValue2.Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue2.Size(), 1);
  ASSERT_EQ(lValue2["abc"].AsInteger(), 1);

  std::string lStr3("{\"abc\":1,\"def\":\"abc\"}");
  CSONPP::Value lValue3 = CSONPP::Parser::Deserialize(lStr3);
  ASSERT_TRUE(lValue3.Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue3.Size(), 2);
  ASSERT_EQ(lValue3["abc"].AsInteger(), 1);
  ASSERT_EQ(lValue3["def"].AsString(), "abc");

  std::string lStr4(" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ");
  CSONPP::Value lValue4 = CSONPP::Parser::Deserialize(lStr4);
  ASSERT_TRUE(lValue4.Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue4.Size(), 7);
  ASSERT_EQ(lValue4["hello"].AsString(), "world");
  ASSERT_TRUE(lValue4["t"].AsBool());
  ASSERT_FALSE(lValue4["f"].AsBool());
  ASSERT_TRUE(lValue4["n"].Type() == CSONPP::Value::ValueType::NULL_T);
  ASSERT_EQ(lValue4["i"].AsInteger(), 123);
  ASSERT_DOUBLE_EQ(lValue4["pi"].AsDouble(), 3.1416);
  ASSERT_EQ(lValue4["a"].Type(), CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue4["a"].Size(), 4);
  ASSERT_EQ(lValue4["a"][0].AsInteger(), 1);
  ASSERT_EQ(lValue4["a"][1].AsInteger(), 2);
  ASSERT_EQ(lValue4["a"][2].AsInteger(), 3);
  ASSERT_EQ(lValue4["a"][3].AsInteger(), 4);
}

TEST(CsonppTest, DeSerializeToArray) {
  std::string lStr1("[]");
  CSONPP::Value lValue1 = CSONPP::Parser::Deserialize(lStr1);
  ASSERT_TRUE(lValue1.Type() == CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue1.Size(), 0);

  std::string lStr2("[3.1456, 1., 2, \"ab\", { \"aaa\" : { \"123\" :   \t1.2e-5}\t}, true, false, null]");
  CSONPP::Value lValue2 = CSONPP::Parser::Deserialize(lStr2);
  ASSERT_TRUE(lValue2.Type() == CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue2.Size(), 8);
  ASSERT_DOUBLE_EQ(lValue2[0].AsDouble(), 3.1456);
  ASSERT_DOUBLE_EQ(lValue2[1].AsDouble(), 1.);
  ASSERT_EQ(lValue2[2].AsInteger(), 2);
  ASSERT_EQ(lValue2[3].AsString(), "ab");
  ASSERT_TRUE(lValue2[4].Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue2[4].Size(), 1);
  ASSERT_TRUE(lValue2[4]["aaa"].Type() == CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_DOUBLE_EQ(lValue2[4]["aaa"]["123"].AsDouble(), 0.000012);
  ASSERT_TRUE(lValue2[5].AsBool());
  ASSERT_FALSE(lValue2[6].AsBool());
  ASSERT_TRUE(lValue2[7].Type() == CSONPP::Value::ValueType::NULL_T);

  std::string lStr3("[12,false, false  , null , [12e4,32, [], \"12\"]]");
  CSONPP::Value lValue3 = CSONPP::Parser::Deserialize(lStr3);
  ASSERT_TRUE(lValue3.Type() == CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue3.Size(), 5);
  ASSERT_EQ(lValue3[0].AsInteger(), 12);
  ASSERT_FALSE(lValue3[1].AsBool());
  ASSERT_FALSE(lValue3[2].AsBool());
  ASSERT_EQ(lValue3[3].Type(), CSONPP::Value::ValueType::NULL_T);
  ASSERT_EQ(lValue3[4].Type(), CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue3[4].Size(), 4);
  ASSERT_DOUBLE_EQ(lValue3[4][0].AsDouble(), 120000);
  ASSERT_EQ(lValue3[4][1].AsInteger(), 32);
  ASSERT_EQ(lValue3[4][2].Type(), CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue3[4][2].Size(), 0);
  ASSERT_EQ(lValue3[4][3].AsString(), "12");
}

TEST(CsonppTest, DeserializeUnicodeString) {
  std::string lStr1("[3.1456, 1., 2, \"a\\u0062\", { \"a\\u5066a\" : { \"12\\uD800\\uDC00\" :   \t1.2e-2}\t}, true, false, null]");
  CSONPP::Value lValue1 = CSONPP::Parser::Deserialize(lStr1);
  ASSERT_TRUE(lValue1.Type() == CSONPP::Value::ValueType::ARRAY_T);
  ASSERT_EQ(lValue1.Size(), 8);
  ASSERT_DOUBLE_EQ(lValue1[0].AsDouble(), 3.1456);
  ASSERT_DOUBLE_EQ(lValue1[1].AsDouble(), 1.);
  ASSERT_EQ(lValue1[2].AsInteger(), 2);
  ASSERT_EQ(lValue1[3].AsString(), "ab");
  ASSERT_EQ(lValue1[4].Type(), CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue1[4].Size(), 1);
  ASSERT_EQ(lValue1[4]["a\xE5\x81\xA6\x61"].Type(), CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(lValue1[4]["a\xE5\x81\xA6\x61"]["12\xF0\x90\x80\x80"].AsDouble(), 0.012);
  ASSERT_TRUE(lValue1[5].AsBool());
  ASSERT_FALSE(lValue1[6].AsBool());
  ASSERT_EQ(lValue1[7].Type(), CSONPP::Value::ValueType::NULL_T);
}

TEST(CsonppTest, Serialize) {
  std::string lStr1 = "\"I \\uD834\\uDD1E playing with json\"";
  CSONPP::Value lValue1 = CSONPP::Parser::Deserialize(lStr1);
  ASSERT_EQ(lValue1.Type(), CSONPP::Value::ValueType::STRING_T);
  ASSERT_EQ(lValue1.AsString(), "I \xF0\x9D\x84\x9E playing with json");
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue1), lStr1);

  std::string lStr2 = "-12e-3";
  CSONPP::Value lValue2 = CSONPP::Parser::Deserialize(lStr2);
  ASSERT_EQ(lValue2.Type(), CSONPP::Value::ValueType::DOUBLE_T);
  ASSERT_DOUBLE_EQ(lValue2.AsDouble(), -0.012);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue2), "-0.0120");

  std::string lStr3 = "1234567";
  CSONPP::Value lValue3 = CSONPP::Parser::Deserialize(lStr3);
  ASSERT_EQ(lValue3.Type(), CSONPP::Value::ValueType::INTEGER_T);
  ASSERT_DOUBLE_EQ(lValue3.AsInteger(), 1234567);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue3), "1234567");

  std::string lStr4 = "-1234567.50";
  CSONPP::Value lValue4 = CSONPP::Parser::Deserialize(lStr4);
  ASSERT_EQ(lValue4.Type(), CSONPP::Value::ValueType::DOUBLE_T);
  ASSERT_DOUBLE_EQ(lValue4.AsDouble(), -1234567.50);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue4), "-1234567.50");

  std::string lStr5 = "{\"a\":   \t-1234567.50}";
  CSONPP::Value lValue5 = CSONPP::Parser::Deserialize(lStr5);
  ASSERT_EQ(lValue5.Type(), CSONPP::Value::ValueType::OBJECT_T);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue5), "{\"a\":-1234567.50}");

  std::string lStr6("[3.1456, 1., 2, \"a\\u0062\", { \"a\\u5066a\" : { \"12\\uD800\\uDC00\" :   \t1.2e-2}\t}, true, false, null]");
  CSONPP::Value lValue6 = CSONPP::Parser::Deserialize(lStr6);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue6), "[3.14560,1.0,2,\"ab\",{\"a\\u5066a\":{\"12\\uD800\\uDC00\":0.0120}},true,false,null]");

  std::string lStr7("[12,false, false  , null , [12e4,32, [], \"12\"]]");
  CSONPP::Value lValue7 = CSONPP::Parser::Deserialize(lStr7);
  std::string aa = CSONPP::Parser::Serialize(lValue7);
  ASSERT_EQ(CSONPP::Parser::Serialize(lValue7), "[12,false,false,null,[120000.0,32,[],\"12\"]]");
}

