#include <BuildManager.h>
#include <BuildingPlacer.h>
#include <ConstructionManager.h>
#include <ProductionManager.h>
#include <MorphManager.h>

BuildManager::BuildManager(Arbitrator::Arbitrator<BWAPI::Unit*,double>* arbitrator)
{
  this->arbitrator=arbitrator;
  this->buildingPlacer=new BuildingPlacer();
  this->constructionManager=new ConstructionManager(this->arbitrator,this->buildingPlacer);
  this->productionManager=new ProductionManager(this->arbitrator,this->buildingPlacer);
  this->morphManager=new MorphManager(this->arbitrator);
}

BuildManager::~BuildManager()
{
  delete this->buildingPlacer;
  delete this->constructionManager;
  delete this->productionManager;
  delete this->morphManager;
}

void BuildManager::update()
{
  this->constructionManager->update();
  this->productionManager->update();
  this->morphManager->update();
}

std::string BuildManager::getName() const
{
  return "Build Manager";
}

void BuildManager::onRemoveUnit(BWAPI::Unit* unit)
{
  this->constructionManager->onRemoveUnit(unit);
  this->productionManager->onRemoveUnit(unit);
  this->morphManager->onRemoveUnit(unit);
}

bool BuildManager::build(BWAPI::UnitType type)
{
  if (type==BWAPI::UnitTypes::None || type==BWAPI::UnitTypes::Unknown) return false;
  if (type.getRace()==BWAPI::Races::Zerg && type.isBuilding()==type.whatBuilds().first->isBuilding())
    return this->morphManager->morph(type);
  else
  {
    if (type.isBuilding())
      return this->constructionManager->build(type);
    else
      return this->productionManager->train(type);
  }
  return false;
}