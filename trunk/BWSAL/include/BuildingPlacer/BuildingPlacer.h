#pragma once
#include <BWAPI.h>
#include "RectangleArray.h"
class BuildingPlacer
{
  public:
  BuildingPlacer();
  bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const;
  bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const;
  BWAPI::TilePosition getBuildLocation(BWAPI::UnitType type) const;
  BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position,BWAPI::UnitType type) const;
  void reserveTiles(BWAPI::TilePosition position, int width, int height);
  void freeTiles(BWAPI::TilePosition position, int width, int height);
  private:
  Util::RectangleArray<bool> reserveMap;
};