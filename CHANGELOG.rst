^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package open_karto
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* Merge pull request `#1 <https://github.com/savioke/open_karto/issues/1>`_ from liz-murphy/first_point_nan
  Removes useless best loop closure response functions in prep for upst…
* Removes useless best loop closure response functions in prep for upstream PR
* Contributors: Stephan, liz-murphy

101.1.1 (2014-10-24)
--------------------
* Update version to 101
  We'll use 100+version for the savioke version, so that it
  gets installed on our systems.
* Don't compute every linked scan
* Optimize after every linked scan
* Hooks to allow publishing the response strength of loop closure
* Alters FindValidPoints to search for the first non-nan point in the scan to use to compute the direction of rotation
* Merge pull request `#1 <https://github.com/savioke/open_karto/issues/1>`_ from pal-robotics/pal-changes
  Changes from PAL Robotics
* Fix typo in comment
* Bump minimum cmake version requirement
* Fix cppcheck warnings
* Fix newlines (dos2unix) & superfluous whitespace
* Protect functions that throw away const-ness (check dirty flag) with mutex
* Don't modify scan during loop closure check - work on a copy of it
* removed useless return to avoid cppcheck error
* Add Mapper::SetUseScanMatching
* Remove html entities from log output
* NANs cause raytracing to take forever
* Contributors: Daniel Pinyol, Jon Binney, Michael Ferguson, Paul Mathieu, Siegfried-A. Gevatter Pujals, liz-murphy

1.1.0 (2014-06-15)
------------------
* Release as a pure catkin ROS package
