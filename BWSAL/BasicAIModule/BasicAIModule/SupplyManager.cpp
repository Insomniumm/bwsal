#include <SupplyManager.h>

SupplyManager::SupplyManager()
{
  this->buildManager      = NULL;
  this->buildOrderManager = NULL;
  this->lastFrameCheck    = 0;
}

void SupplyManager::setBuildManager(BuildManager* buildManager)
{
  this->buildManager = buildManager;
}
void SupplyManager::setBuildOrderManager(BuildOrderManager* buildOrderManager)
{
  this->buildOrderManager = buildOrderManager;
}
void SupplyManager::update()
{
  if (BWAPI::Broodwar->getFrameCount()>lastFrameCheck+25)
  {
    int productionCapacity       = 0;
    lastFrameCheck               = BWAPI::Broodwar->getFrameCount();
    std::set<BWAPI::Unit*> units = BWAPI::Broodwar->self()->getUnits();

    for(std::set<BWAPI::Unit*>::iterator i = units.begin(); i != units.end(); i++)
      if ((*i)->getType().canProduce())
        productionCapacity += 4; //heuristic, should replace with exact calculation at some point

    if (getPlannedSupply() <= BWAPI::Broodwar->self()->supplyUsed() + productionCapacity)
    {
      this->buildOrderManager->buildAdditional(1,*BWAPI::Broodwar->self()->getRace().getSupplyProvider(),1000);
    }
  }
}

std::string SupplyManager::getName() const
{
  return "Supply Manager";
}

int SupplyManager::getPlannedSupply() const
{
  int plannedSupply=0;
  //planned supply depends on the the amount of planned supply providers times the amount of supply they provide.
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Terran_Supply_Depot)*BWAPI::UnitTypes::Terran_Supply_Depot.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Terran_Command_Center)*BWAPI::UnitTypes::Terran_Command_Center.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Protoss_Pylon)*BWAPI::UnitTypes::Protoss_Pylon.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Protoss_Nexus)*BWAPI::UnitTypes::Protoss_Nexus.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Zerg_Overlord)*BWAPI::UnitTypes::Zerg_Overlord.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Zerg_Hatchery)*BWAPI::UnitTypes::Zerg_Hatchery.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Zerg_Lair)*BWAPI::UnitTypes::Zerg_Lair.supplyProvided();
  plannedSupply+=buildOrderManager->getPlannedCount(BWAPI::UnitTypes::Zerg_Hive)*BWAPI::UnitTypes::Zerg_Hive.supplyProvided();
  return plannedSupply;
}