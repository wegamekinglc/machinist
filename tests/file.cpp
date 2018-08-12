//
// Created by Cheng Li on 2018/8/9.
//


#include <gtest/gtest.h>
#include <source/File.h>

using namespace File;

TEST(FileTest, TestFileList) {
    string src_dir = "D:/dev/github/machinist/data";
    string pattern = "sample*";
    vector<string> rejects(1, "*2*");
    vector<string> files = List(src_dir, pattern, rejects);

    ASSERT_EQ(files.size(), 2);
    ASSERT_EQ(files[0], "sample1.csv");
    ASSERT_EQ(files[1], "sample3.csv");
}