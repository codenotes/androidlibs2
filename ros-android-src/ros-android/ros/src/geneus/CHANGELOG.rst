^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package geneus
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.2.4 (2015-07-08)
------------------
* [src/geneus/generate.py] bool array is list, not lisp-array
* [src/geneus/generate.py] use list for time type object
* src/geneus/generate.py fix for variable bool array case, https://github.com/jsk-ros-pkg/jsk_roseus/pull/330
* [package.xml] Now doesn't depend on python-rospkg
* Contributors: Kei Okada, Kentaro Wada

2.2.3 (2015-06-19)
------------------
* [src/geneus/geneus_main.py] Call get_pkg_map if pkg_map is None
* Contributors: Kentaro Wada

2.2.2 (2015-06-01)
------------------
* [.travis.yml] add pr2eus test
* [src/geneus/generate.py] make intern before shadow, see https://github.com/jsk-ros-pkg/jsk_roseus/issues/313
* [geneus_main.py] has_key -> in
* [geneus_main.py] generate message even if geneus is not found
* Contributors: Kei Okada, Kentaro Wada

2.2.1 (2015-04-24)
------------------
* [geneus_main.py] fix when pkg_map does not have geneus
* [geneus_main.py] Fix unexpected function resposes caused by python gabage collection algorightm
* [geneus_main.py] fix typo for warning
* [geneus_main.py] Yellow color for warnings
* Contributors: Kei Okada, Kentaro Wada

2.2.0 (2015-04-21)
------------------

* [generate.py] load roseus-add-msgs for srv too
* [geneus_main.py] add timestamp message to manifest.l

* [geneus_main.py] message loding problem https://github.com/start-jsk/2014-semi/issues/196, https://github.com/jsk-ros-pkg/jsk_roseus/issues/257

  * [geneus_main.py] gen msg/srv does not need get_pkg_map
  * [geneus_main.py] fix comment and messages
  * [geneus_main.py] use topological_order instaed of rearrange_depends
  * [geneus_main.py] use catkin as a substitute for rospkg
  * [geneus_main.py] see only run_depend in package.xml
  * [geneus_main.py] Resolve package dependencies with attention to the order

* [geneus] treat uint8[] as string like rospy https://github.com/jsk-ros-pkg/geneus/issues/14
  * [generate.py] fixed version of `#15 <https://github.com/jsk-ros-pkg/geneus/issues/15>`_ which did not pass test at  https://github.com/jsk-ros-pkg/jsk_roseus/pull/276
* [geneus_main.py] fix pakcage_dpeneds, to solve https://github.com/start-jsk/2014-semi/issues/196 issue
* [.travis.yml] use latest version of travis test
* [.travis.yml] use latest catkin for --no-jobserver option
* [.travis.yml] Add after failure
* [.gitignore] initial commit

* Contributors: Yuki Furuta Kei Okada, Kentaro Wada

2.1.2 (2015-02-25)
------------------
* [.travis.yml] remove hot-fix code
* fix not to use get_depends, which cause eerror when the package is not installed
* [package.xml] forget to add python-rospkg
* Contributors: Kei Okada

2.1.1 (2015-02-21)
------------------
* [geneus_main.py] use rospack to find build(only package have msg/src) dependency
* [.travis.yml] add test code to check work with roseus
* [src/geneus/geneus_main.py] add comments
* fix ros::load-ros-package order by dependencies
* Contributors: Kei Okada, Yuki Furuta

2.1.0 (2015-02-12)
------------------
* fix message generation for uint8(char)/int8(byte) (#4,#6)
* Contributors: Kei Okada

2.0.1 (2015-02-10)
------------------
* [scripts/gen_eus.py] set executable
* Contributors: Kei Okada

1.0.0 (2015-01-06)
------------------

0.1.0 (2014-10-02)
------------------
* rewrite everything only depends on genmsg
* Contributors: Kei Okada

