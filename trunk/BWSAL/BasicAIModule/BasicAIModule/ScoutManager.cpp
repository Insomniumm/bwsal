#include <ScoutManager.h>
ScoutManager::ScoutManager(Arbitrator::Arbitrator<BWAPI::Unit*,double> *arbitrator)
{
  this->arbitrator = arbitrator;
}
void ScoutManager::onOffer(std::set<BWAPI::Unit*> units)
{
  // TODO Implement
}
void ScoutManager::onRevoke(BWAPI::Unit *unit, double bid)
{
  // TODO Implement
}
void ScoutManager::update()
{
  // TODO Implement
}
std::string ScoutManager::getName() const
{
  return "Scout Manager";
}