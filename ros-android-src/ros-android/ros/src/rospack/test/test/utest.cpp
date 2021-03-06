/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Author: Brian Gerkey */

#include <stdexcept> // for std::runtime_error
#include <string>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "rospack/rospack.h"
#include "utils.h"


TEST(rospack, reentrant)
{
  rospack::ROSPack rp;
  std::string output;
  int ret = rp.run(std::string("plugins --attrib=foo --top=precedence1 roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp.run(std::string("find roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp.run(std::string("list-names"));
  ASSERT_EQ(ret, 0);
  std::vector<std::string> output_list;
  output = rp.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  ret = rp.run(std::string("list"));
  ASSERT_EQ(ret, 0);
  output = rp.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  std::vector<std::string> path_name;
  boost::split(path_name, output_list[0], boost::is_any_of(" "));
  ASSERT_EQ((int)path_name.size(), 2);
}

TEST(rospack, multiple_rospack_objects)
{
  rospack::ROSPack rp;
  std::string output;
  int ret = rp.run(std::string("plugins --attrib=foo --top=precedence1 roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp.run(std::string("find roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp.run(std::string("list-names"));
  ASSERT_EQ(ret, 0);
  std::vector<std::string> output_list;
  output = rp.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  ret = rp.run(std::string("list"));
  ASSERT_EQ(ret, 0);
  output = rp.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  std::vector<std::string> path_name;
  boost::split(path_name, output_list[0], boost::is_any_of(" "));
  ASSERT_EQ((int)path_name.size(), 2);

  rospack::ROSPack rp2;
  ret = rp2.run(std::string("plugins --attrib=foo --top=precedence1 roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp2.run(std::string("find roslang"));
  ASSERT_EQ(ret, 0);
  ret = rp2.run(std::string("list-names"));
  ASSERT_EQ(ret, 0);
  output_list.clear();
  output = rp2.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  ret = rp2.run(std::string("list"));
  ASSERT_EQ(ret, 0);
  output = rp2.getOutput();
  boost::trim(output);
  boost::split(output_list, output, boost::is_any_of("\n"));
  ASSERT_EQ((int)output_list.size(), 4);
  path_name.clear();
  boost::split(path_name, output_list[0], boost::is_any_of(" "));
  ASSERT_EQ((int)path_name.size(), 2);
}

TEST(rospack, deduplicate_tokens)
{
  std::string input = "foo foo bar bat bar foobar batbar";
  std::string truth = "foo bar bat foobar batbar";
  std::string output;
  rospack::deduplicate_tokens(input, false, output);
  ASSERT_EQ(truth, output);
}

int main(int argc, char **argv)
{
  // Quiet some warnings
  (void)rospack::ROSPACK_NAME;
  (void)rospack::ROSSTACK_NAME;

  char buf[1024];
  std::string rr = std::string(getcwd(buf, sizeof(buf))) + "/test2";
  setenv("ROS_PACKAGE_PATH", rr.c_str(), 1);
  char path[PATH_MAX];
  if(getcwd(path,sizeof(path)))
  {
    boost::filesystem::path p(path);
    p = p.parent_path();
    std::string newpath = p.string();
    char* oldpath = getenv("PATH");
    if(oldpath)
      newpath += std::string(":") + oldpath;
    setenv("PATH", newpath.c_str(), 1);
  }

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
