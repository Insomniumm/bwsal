#include <UnitGroup.h>
using namespace BWAPI;
using namespace std;

UnitGroup UnitGroup::operator+(const UnitGroup& other) const
{
  UnitGroup result=*this;
  for(set<Unit*>::const_iterator i=other.begin();i!=other.end();i++)
  {
    result.insert(*i);
  }
  return result;
}
UnitGroup UnitGroup::operator*(const UnitGroup& other) const
{
  UnitGroup result=*this;
  set<Unit*>::iterator i2;
  for(set<Unit*>::iterator i=result.begin();i!=result.end();i=i2)
  {
    i2=i;
    i2++;
    if (other.find(*i)==other.end())
      result.erase(*i);
  }
  return result;
}
UnitGroup UnitGroup::operator^(const UnitGroup& other) const
{
  UnitGroup result=*this;
  set<Unit*>::const_iterator i2;
  for(set<Unit*>::const_iterator i=other.begin();i!=other.end();i=i2)
  {
    i2=i;
    i2++;
    if (result.find(*i)==result.end())
      result.insert(*i);
    else
      result.erase(*i);
  }
  return result;
}
UnitGroup UnitGroup::operator-(const UnitGroup& other) const
{
  UnitGroup result=*this;
  for(set<Unit*>::const_iterator i=other.begin();i!=other.end();i++)
  {
    result.erase(*i);
  }
  return result;
}

bool UnitGroup::attackMove(Position position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->attackMove(position);
  }
  return retval;
}
bool UnitGroup::attackUnit(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->attackUnit(target);
  }
  return retval;
}
bool UnitGroup::rightClick(Position position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->rightClick(position);
  }
  return retval;
}
bool UnitGroup::rightClick(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->rightClick(target);
  }
  return retval;
}
bool UnitGroup::train(UnitType type)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->train(type);
  }
  return retval;
}
bool UnitGroup::build(TilePosition position, UnitType type)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->build(position,type);
  }
  return retval;
}
bool UnitGroup::buildAddon(UnitType type)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->buildAddon(type);
  }
  return retval;
}
bool UnitGroup::research(TechType tech)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->research(tech);
  }
  return retval;
}
bool UnitGroup::upgrade(UpgradeType upgrade)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->upgrade(upgrade);
  }
  return retval;
}
bool UnitGroup::stop()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->stop();
  }
  return retval;
}
bool UnitGroup::holdPosition()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->holdPosition();
  }
  return retval;
}
bool UnitGroup::patrol(Position position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->patrol(position);
  }
  return retval;
}
bool UnitGroup::follow(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->follow(target);
  }
  return retval;
}
bool UnitGroup::setRallyPosition(Position target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->setRallyPosition(target);
  }
  return retval;
}
bool UnitGroup::setRallyUnit(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->setRallyUnit(target);
  }
  return retval;
}
bool UnitGroup::repair(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->repair(target);
  }
  return retval;
}
bool UnitGroup::morph(UnitType type)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->morph(type);
  }
  return retval;
}
bool UnitGroup::burrow()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->burrow();
  }
  return retval;
}
bool UnitGroup::unburrow()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->unburrow();
  }
  return retval;
}
bool UnitGroup::siege()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->siege();
  }
  return retval;
}
bool UnitGroup::unsiege()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->unsiege();
  }
  return retval;
}
bool UnitGroup::cloak()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cloak();
  }
  return retval;
}
bool UnitGroup::decloak()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->decloak();
  }
  return retval;
}
bool UnitGroup::lift()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->lift();
  }
  return retval;
}
bool UnitGroup::land(TilePosition position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->land(position);
  }
  return retval;
}
bool UnitGroup::load(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->load(target);
  }
  return retval;
}
bool UnitGroup::unload(Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->unload(target);
  }
  return retval;
}
bool UnitGroup::unloadAll()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->unloadAll();
  }
  return retval;
}
bool UnitGroup::unloadAll(Position position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->unloadAll(position);
  }
  return retval;
}
bool UnitGroup::cancelConstruction()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelConstruction();
  }
  return retval;
}
bool UnitGroup::haltConstruction()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->haltConstruction();
  }
  return retval;
}
bool UnitGroup::cancelMorph()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelMorph();
  }
  return retval;
}
bool UnitGroup::cancelTrain()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelTrain();
  }
  return retval;
}
bool UnitGroup::cancelTrain(int slot)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelTrain(slot);
  }
  return retval;
}
bool UnitGroup::cancelAddon()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelAddon();
  }
  return retval;
}
bool UnitGroup::cancelResearch()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelResearch();
  }
  return retval;
}
bool UnitGroup::cancelUpgrade()
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->cancelUpgrade();
  }
  return retval;
}
bool UnitGroup::useTech(TechType tech)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->useTech(tech);
  }
  return retval;
}
bool UnitGroup::useTech(TechType tech, Position position)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->useTech(tech,position);
  }
  return retval;
}
bool UnitGroup::useTech(TechType tech, Unit* target)
{
  bool retval=true;
  for(set<Unit*>::iterator i=this->begin();i!=this->end();i++)
  {
    retval = retval && (*i)->useTech(tech,target);
  }
  return retval;
}