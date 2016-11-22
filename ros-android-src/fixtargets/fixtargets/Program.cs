using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace fixtargets
{
    class Program
    {
        static IEnumerable<string> GetAllFiles(params string[] subdirs)
        {
            foreach (var sub in subdirs)
            {
                string dir = @"F:\PROJECTS\infusion\ros-android\ros\build_isolated\" + sub;
                if (Directory.Exists(dir))
                {
                    foreach (var fn in Directory.GetFiles(dir, "*.make", SearchOption.AllDirectories))
                        yield return fn;
                }
            }
        }

        static void Main(string[] args)
        {
            foreach(var fn in GetAllFiles("std_msgs", "rosgraph_msgs", "roscpp", "roscpp_tutorials"))
            {
                var lines = File.ReadAllLines(fn);
                bool found = false;
                for (int i = 0; i < lines.Length; i++)
                    if (lines[i].StartsWith("\tcatkin_generated/env_cached"))
                    {
                        lines[i] = lines[i].Replace("\tcatkin_generated/env_cached", "\tcall catkin_generated/env_cached");
                        found = true;
                    }

                if (found)
                {
                    Console.WriteLine(fn);
                    File.WriteAllLines(fn, lines);
                }
            }
        }
    }
}
