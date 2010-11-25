#include "MacroAIModule.h"
#include <BasicTaskExecutor.h>
#include <SpiralBuildingPlacer.h>
#include <BFSBuildingPlacer.h>
#include <UnitPump.h>
#include <TerminateIfWorkerLost.h>
#include <TerminateIfEmpty.h>
#include <BasicWorkerFinder.h>
#include <UnitCompositionProducer.h>
#include <MacroManager.h>
#include <ResourceRates.h>
#include <MacroSupplyManager.h>
#include <MacroDependencyResolver.h>
#include <InformationManager.h>
#include <BorderManager.h>
#include <MacroBaseManager.h>

using namespace BWAPI;
int drag_index = -1;
bool lastMouseClick = false;
UnitCompositionProducer* infantryProducer = NULL;
UnitCompositionProducer* vehicleProducer = NULL;
MacroAIModule::MacroAIModule()
{
}
MacroAIModule::~MacroAIModule()
{
  if (TheMacroManager != NULL)
    delete TheMacroManager;
  if (TheMacroSupplyManager != NULL)
    delete TheMacroSupplyManager;
  if (TheMacroDependencyResolver != NULL)
    delete TheMacroDependencyResolver;
  if (TheResourceRates != NULL)
    delete TheResourceRates;
  if (TheInformationManager != NULL)
    delete TheInformationManager;
  if (TheBorderManager != NULL)
    delete TheBorderManager;
  if (TheMacroBaseManager != NULL)
    delete TheMacroBaseManager;
  if (infantryProducer != NULL)
    delete infantryProducer;
  if (vehicleProducer != NULL)
    delete vehicleProducer;
}
void MacroAIModule::onStart()
{
  Broodwar->enableFlag(Flag::UserInput);
  BWTA::readMap();
  BWTA::analyze();
  MacroManager::create(&arbitrator);
  MacroSupplyManager::create();
  MacroDependencyResolver::create();
  ResourceRates::create();
  InformationManager::create();
  BorderManager::create();
  MacroBaseManager::create();

  TaskStream* ts = new TaskStream();
  TheMacroManager->taskStreams.push_back(ts);
  Unit* worker = NULL;
  for each(Unit* u in Broodwar->self()->getUnits())
  {
    if (u->getType().isResourceDepot())
      worker = u;
  }
  ts->setWorker(worker);
  ts->attach(BasicTaskExecutor::getInstance(),false);
  ts->attach(new UnitPump(Broodwar->self()->getRace().getWorker()),true);
  ts->attach(new TerminateIfWorkerLost(),true);

  if (Broodwar->self()->getRace()==Races::Terran)
  {
    infantryProducer = new UnitCompositionProducer(UnitTypes::Terran_Barracks);
    infantryProducer->setUnitWeight(UnitTypes::Terran_Marine,2.0);
    infantryProducer->setUnitWeight(UnitTypes::Terran_Medic,1.0);
    infantryProducer->setUnitWeight(UnitTypes::Terran_Firebat,0.5);

    vehicleProducer = new UnitCompositionProducer(UnitTypes::Terran_Factory);
    vehicleProducer->setUnitWeight(UnitTypes::Terran_Vulture,2.0);
    vehicleProducer->setUnitWeight(UnitTypes::Terran_Siege_Tank_Tank_Mode,1.0);
  }
  if (Broodwar->self()->getRace()==Races::Protoss)
  {
    infantryProducer = new UnitCompositionProducer(UnitTypes::Protoss_Gateway);
    infantryProducer->setUnitWeight(UnitTypes::Protoss_Dragoon,2.0);
    infantryProducer->setUnitWeight(UnitTypes::Protoss_Zealot,1.0);
  }
}
void MacroAIModule::onEnd(bool isWinner)
{
}
void MacroAIModule::onFrame()
{
  TheArbitrator->update();
  if (infantryProducer)
    infantryProducer->update();
  if (vehicleProducer)
    vehicleProducer->update();
  TheMacroSupplyManager->update();
  TheMacroDependencyResolver->update();
  TheMacroManager->update();
  TheResourceRates->update();
  TheBorderManager->update();
  TheMacroBaseManager->update();
  std::set<Unit*> units=Broodwar->self()->getUnits();
  for(std::set<Unit*>::iterator i=units.begin();i!=units.end();i++)
  {
    if (this->arbitrator.hasBid(*i))
    {
      int x=(*i)->getPosition().x();
      int y=(*i)->getPosition().y();
      std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*,double>*, double> > bids=this->arbitrator.getAllBidders(*i);
      int y_off=0;
      bool first = false;
      const char activeColor = '\x07', inactiveColor = '\x16';
      char color = activeColor;
      for(std::list< std::pair< Arbitrator::Controller<BWAPI::Unit*,double>*, double> >::iterator j=bids.begin();j!=bids.end();j++)
      {
        Broodwar->drawTextMap(x,y+y_off,"%c%s: %d",color,j->first->getShortName().c_str(),(int)j->second);
        y_off+=15;
        color = inactiveColor;
      }
    }
  }
  if (drag_index<0)
  {
    if (Broodwar->getMouseState(M_LEFT) && !lastMouseClick)
    {
      drag_index = (Broodwar->getMousePosition().y()-25)/20;
      if (drag_index<0) drag_index = 0;
    }
    if (drag_index>=(int)TheMacroManager->taskStreams.size())
      drag_index=-1;
  }
  if (drag_index>=0)
  {
    int land_index = (Broodwar->getMousePosition().y()-30)/20;
    if (land_index<0) land_index = 0;
    if (land_index>=(int)TheMacroManager->taskStreams.size())
      land_index=(int)TheMacroManager->taskStreams.size()-1;
    if (land_index!=drag_index)
    {
      std::list<TaskStream*>::iterator td=TheMacroManager->taskStreams.end();
      std::list<TaskStream*>::iterator tl=TheMacroManager->taskStreams.end();
      TaskStream* tm=NULL;
      int j=0;
      for(std::list<TaskStream*>::iterator i=TheMacroManager->taskStreams.begin();i!=TheMacroManager->taskStreams.end();i++)
      {
        if (j==drag_index)
          td=i;
        if (j==land_index)
          tl=i;
        j++;
      }
      if (td!=TheMacroManager->taskStreams.end() && tl!=TheMacroManager->taskStreams.end())
      {
        tm=*td;
        *td=*tl;
        *tl=tm;
      }
      drag_index = land_index;
    }
    if (!Broodwar->getMouseState(M_LEFT) && lastMouseClick)
    {
      drag_index=-1;
    }
  }
  lastMouseClick = Broodwar->getMouseState(M_LEFT);
}
void MacroAIModule::onSendText(std::string text)
{
  Broodwar->sendText(text.c_str());
  if (text=="hide")
  {
    TheMacroManager->taskstream_list_visible = false;
  }
  if (text=="show")
  {
    TheMacroManager->taskstream_list_visible = true;
  }
  UnitType type=UnitTypes::getUnitType(text);
  if (type!=UnitTypes::Unknown)
  {
    TaskStream* ts = new TaskStream(Task(type));
    TheMacroManager->taskStreams.push_back(ts);
    ts->attach(new BasicWorkerFinder(),true);
    ts->attach(BasicTaskExecutor::getInstance(),false);
    ts->attach(new TerminateIfEmpty(),true);
    ts->attach(BFSBuildingPlacer::getInstance(),false);
  }
  else
  {
    TechType type=TechTypes::getTechType(text);
    if (type!=TechTypes::Unknown)
    {
      TaskStream* ts = new TaskStream(Task(type));
      TheMacroManager->taskStreams.push_back(ts);
      ts->attach(new BasicWorkerFinder(),true);
      ts->attach(BasicTaskExecutor::getInstance(),false);
      ts->attach(new TerminateIfEmpty(),true);
      ts->attach(BFSBuildingPlacer::getInstance(),false);
    }
    else
    {
      UpgradeType type=UpgradeTypes::getUpgradeType(text);
      if (type!=UpgradeTypes::Unknown)
      {
        TaskStream* ts = new TaskStream(Task(type));
        TheMacroManager->taskStreams.push_back(ts);
        ts->attach(new BasicWorkerFinder(),true);
        ts->attach(BasicTaskExecutor::getInstance(),false);
        ts->attach(new TerminateIfEmpty(),true);
        ts->attach(BFSBuildingPlacer::getInstance(),false);
      }
      else
        Broodwar->printf("You typed '%s'!",text.c_str());
    }
  }
}
void MacroAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
  TheInformationManager->onUnitDiscover(unit);
}
void MacroAIModule::onUnitEvade(BWAPI::Unit* unit)
{
  TheInformationManager->onUnitEvade(unit);
}

void MacroAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
  TheArbitrator->onRemoveObject(unit);
  TheInformationManager->onUnitDestroy(unit);
  TheMacroBaseManager->onUnitDestroy(unit);
}
