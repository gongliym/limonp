#include "StringUtil.hpp"
#include "gtest/gtest.h"
using namespace limonp;

TEST(StrFunctsTest, Test1) {
  vector<string> vec;
  string s;
  split("\t1\t3\t4\t", vec, "\t");
  ASSERT_EQ(s << vec, "[\"\", \"1\", \"3\", \"4\"]");
  s = " \t\n ni hao ad \r\n";
  ASSERT_EQ("ni hao ad", trim(s));
  ASSERT_EQ("select * from table1  limit 1;" ,string_format("select %s from %s  %s;", "*","table1","limit 1"));
  s = string_format("select %s from %s  %s;", "*","table1","limit 1");
  ASSERT_EQ("select * from table1  limit 1;" ,s);
  vec.clear();
  vec.push_back("1");
  vec.push_back("2");
  vec.push_back("3");
  s.clear();
  join(vec.begin(), vec.end(), s,",");
  ASSERT_EQ("1,2,3",s);
  s = join(vec.begin(), vec.end(), "..");
  ASSERT_EQ("1..2..3", s);
  const char* arr[] = {"2","3","5"};
  ASSERT_EQ("2,3,5", join(arr, arr + sizeof(arr)/sizeof(arr[0]), ","));
  map<string , int> mp;
  mp["key1"] =2;
  ASSERT_EQ("{key1:2}", s <<  mp);
  std::unordered_map<int,int> hmp;
  hmp[1]=2;
  ASSERT_EQ("{1:2}", s <<  hmp);
}

TEST(StrFunctsTest, Test2) {
  string s, gbks;
  ifstream ifs("../test/testdata/dict.gbk");
  ASSERT_TRUE(!!ifs);

  vector<uint16_t> uni;
  while(getline(ifs, s)) {
    gbkTrans(s, uni);
    gbkTrans(uni.begin(), uni.end(), gbks);
    ASSERT_EQ(s, gbks);
  }
}

TEST(StrFunctsTest, Test3) {
  string s, utf8;
  ifstream ifs("../test/testdata/dict.utf8");
  ASSERT_TRUE(!!ifs);

  vector<uint16_t> uni;
  while(getline(ifs, s)) {
    ASSERT_TRUE(utf8ToUnicode(s, uni));
    unicodeToUtf8(uni.begin(), uni.end(), utf8);
    ASSERT_EQ(s, utf8);
  }
}

TEST(StrFunctsTest, Test4) {
  //ASSERT_TRUE(startsWith("--help",NULL));
  ASSERT_TRUE(startsWith("--help","--"));
  ASSERT_TRUE(startsWith("--help","-"));
  ASSERT_FALSE(startsWith("--help","he"));
  ASSERT_TRUE(startsWith("help","help"));
  ASSERT_FALSE(startsWith("","help"));
  ASSERT_TRUE(startsWith("hel",""));
  ASSERT_TRUE(endsWith("hel",""));
  ASSERT_TRUE(endsWith("hel","el"));
}

TEST(StrFunctsTest, Test5) {
  const char* str = "1,2,3,4";
  vector<string> vec;
  string res;
  split(str, vec, ",");
  ASSERT_EQ("[\"1\", \"2\", \"3\", \"4\"]", res << vec);
  split("1,2,3,4,", vec, ",");
  ASSERT_EQ("[\"1\", \"2\", \"3\", \"4\"]", res << vec);
  split(str, vec, ",", 3);
  ASSERT_EQ("[\"1\", \"2\", \"3\", \"4\"]", res << vec);

  split("1", vec, ",");
  ASSERT_EQ("[\"1\"]", res << vec);

  split(str, vec, ",", 1);
  ASSERT_EQ("[\"1\", \"2,3,4\"]", res << vec);

  split("", vec, ",");
  ASSERT_EQ("[]", res << vec);
  
  split("1, 2", vec, ",");
  ASSERT_EQ("[\"1\", \"2\"]", res << vec);

  split("1==2", vec, "==");
  ASSERT_EQ("[\"1\", \"\", \"2\"]", res << vec);

  split("1,", vec, ",");
  ASSERT_EQ("[\"1\"]", res << vec);

  split(",1,", vec, ",");
  ASSERT_EQ("[\"\", \"1\"]", res << vec);

  split("1, ", vec, ",");
  ASSERT_EQ("[\"1\", \"\"]", res << vec);
}

TEST(StrFunctsTest, trim) {
  string s;
  s = "xxxyyyxx";
  ASSERT_EQ(rtrim(s, 'x'), "xxxyyy");
  ASSERT_EQ(ltrim(s, 'x'), "yyy");
  s = "xxxyyyxx";
  ASSERT_EQ(trim(s, 'x'), "yyy");
}

TEST(StrFunctsTest, getTime) {
  string s;
  getTime("%Y-%m-%d %H:%M:%S", s);
  //print(s);
}

TEST(StrFunctsTest, pathJoin) {
  const char * path1 = "/home/foo/dir";
  const char * path2 = "file";
  const char * path3 = "/home/foo/dir/";
  const char * path4 = "file";
  const char * answer = "/home/foo/dir/file";

  ASSERT_EQ(answer, pathJoin(path1, path2));
  ASSERT_EQ(answer, pathJoin(path3, path4));
}
